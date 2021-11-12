/*******************************************************************************
 *                    ROM ROBOTICS Co,.Ltd ( Myanmar )    					   *
 *		(ɔ) COPYLEFT 2021 | www.romrobots.com | (+95) 9-259-288-229            *
 *******************************************************************************/ 
#include <string>
#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <rom_motor_msgs/actual_rpm.h>
#include <rom_motor_msgs/rpm.h>
#include "serial/serial.h"

uint32_t baud = 115200;
const std::string port = "/dev/ttyUSB0";
uint32_t inter_byte_timeout = 0, read_timeout = 1, read_timeout_mul = 1, write_timeout = 0, write_timeout_mul = 0;
serial::Timeout timeout_(inter_byte_timeout, read_timeout, read_timeout_mul, write_timeout, write_timeout_mul);

int loop_rate = 20;
int16_t desire_right = 0;
int16_t desire_left  = 0;
bool transmit = false;

void desireCallback( const rom_motor_msgs::rpm& msg)
{
    desire_right = msg.desire_rpm_right;
    desire_left  = msg.desire_rpm_left;
    transmit = true;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "serial_driver");
    ros::NodeHandle nh_;
    ros::Publisher pub = nh_.advertise<rom_motor_msgs::actual_rpm>("/actual_rpm", 1000);
    ros::Subscriber sub = nh_.subscribe("/desire_rpm", 50, desireCallback);
    ros::Rate r(loop_rate);

    rom_motor_msgs::actual_rpm act;
    
    serial::Serial mySerial( port, baud, timeout_,
    serial::eightbits, serial::parity_none, serial::stopbits_one, serial::flowcontrol_none );
    if(! mySerial.isOpen() ) { mySerial.open(); }

        while (ros::ok())
        {   
            // read
            if( mySerial.waitReadable() )
            {   
                std::string read_buffer = mySerial.readline(10, "\r"); mySerial.flushInput();
                int left_ = 0, right_ =0;
                std::size_t r_pos = read_buffer.find("r");
                std::size_t l_pos = read_buffer.find("l");
                std::string r_rpm = read_buffer.substr(0, r_pos);
                std::string l_rpm = read_buffer.substr(r_pos+1, l_pos);
                std::stringstream left(l_rpm);
                std::stringstream right(r_rpm);
                left  >> left_;
                right >> right_;
                act.actual_right = right_;
                act.actual_left  = left_;
                //ROS_INFO_STREAM(" you : "<< you);
            }
            // write
            std::string to_mcu;
            if(transmit) // actual data is not zero
            {
                to_mcu = "m"+std::to_string(desire_right)+"rm"+std::to_string(desire_left)+"l";         // check \r\n ?
                transmit = false;
            }else {
                to_mcu = "m0rm0l";
            }
            mySerial.write(to_mcu);
            
            pub.publish(act); 
            ros::spinOnce();
            r.sleep();
        }
   
    mySerial.close();
    return 0;
}
