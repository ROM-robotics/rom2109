/*******************************************************************************
 *                    ROM ROBOTICS Co,.Ltd ( Myanmar )    					   *
 *		(ɔ) COPYLEFT 2021 | www.romrobots.com | (+95) 9-259-288-229            *
 *******************************************************************************/ 
#include <string>
#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include "serial/serial.h"
#include <geometry_msgs/Twist.h>

#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/TransformStamped.h>

#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

#include <rom_motor_msgs/rpm_monitor.h>
  
//#define RPM_MONITOR 1

#ifdef RPM_MONITOR
        char right_actual = 'A';
        char right_desire = 'B';
        char left_actual  = 'C';
        char left_desire  = 'D';

        int r_actual = 0;
        int r_desire = 0;
        int l_actual = 0;
        int l_desire = 0;
#endif

bool publish_tf = true;

uint32_t baud = 115200;
const std::string port = "/home/mr_robot/robotController";
uint32_t inter_byte_timeout = 0, read_timeout = 1, read_timeout_mul = 1, write_timeout = 0, write_timeout_mul = 0;
serial::Timeout timeout_(inter_byte_timeout, read_timeout, read_timeout_mul, write_timeout, write_timeout_mul);
int receive_Byte_Size = 32;

int loop_rate = 20;
float_t lin_x = 0.0;
float_t ang_z = 0.0;
std::string reset_ = "1.0";
bool reset_mcu = true;

double x_pos = 0.0;
double y_pos = 0.0;
double theta = 0.0;
ros::Time current_time;

void twistCallback( const geometry_msgs::Twist& robot_velocity)
{
    lin_x = robot_velocity.linear.x;
    ang_z = robot_velocity.angular.z;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "serial_driver");
    ros::NodeHandle nh_;
    ros::NodeHandle nh_priv("~");
    ros::Publisher odom_pub = nh_.advertise<nav_msgs::Odometry>("/odom", 50);
    tf::TransformBroadcaster broadcaster;
    ros::Subscriber sub = nh_.subscribe("/cmd_vel", 50, twistCallback);
    serial::Serial mySerial( port, baud, timeout_,
    serial::eightbits, serial::parity_none, serial::stopbits_one, serial::flowcontrol_none );
    ros::Rate r(loop_rate);
    //ros::param::get("/publish_odom_baselink_tf", publish_tf );
    nh_priv.getParam("publish_odom_baselink_tf", publish_tf);



    #ifdef RPM_MONITOR
        ros::Publisher rpm_pub = nh_.advertise<rom_motor_msgs::rpm_monitor>("/all_rpms", 50);
        rom_motor_msgs::rpm_monitor rpm_monitor;
    #endif

    char base_link[] = "base_link";
    char odom[] = "odom";
    nav_msgs::Odometry odom_msg;
        odom_msg.header.frame_id = odom;
        odom_msg.child_frame_id  = base_link;
        odom_msg.pose.pose.position.z  = 0.0;
        odom_msg.twist.twist.linear.y  = 0.0;
        odom_msg.twist.twist.linear.z  = 0.0;
        odom_msg.twist.twist.angular.x = 0.0;
        odom_msg.twist.twist.angular.y = 0.0;

    geometry_msgs::TransformStamped t;
        t.header.frame_id = odom;
        t.child_frame_id  = base_link;
        t.transform.translation.z = 0.0;

    if( !mySerial.isOpen() ) { mySerial.open(); }

        while (ros::ok())
        { 
            // ----------------------------------------------------------- start serial read
            if( mySerial.waitReadable() )
            {   
                std::string read_buffer = mySerial.readline(receive_Byte_Size, "\r"); mySerial.flushInput(); // 32 not sure.check firmware
                float x_pos = 0.0, y_pos = 0.0, theta = 0.0;
                std::size_t position_x = read_buffer.find("x");
                std::size_t position_y = read_buffer.find("y");
                std::size_t position_t = read_buffer.find("t");

                #ifdef RPM_MONITOR
                std::size_t position_ra = read_buffer.find(right_actual);
                std::size_t position_rd = read_buffer.find(right_desire);
                std::size_t position_la = read_buffer.find(left_actual);
                std::size_t position_ld = read_buffer.find(left_desire);
                #endif

                std::string x_pos_str = read_buffer.substr(0, position_x);
                std::string y_pos_str = read_buffer.substr(position_x+1, position_y);
                std::string theta_str = read_buffer.substr(position_y+1, position_t);

                #ifdef RPM_MONITOR
                std::string right_act = read_buffer.substr(position_t+1, position_ra);
                std::string right_des = read_buffer.substr(position_ra+1, position_rd);
                std::string left_act  = read_buffer.substr(position_rd+1, position_la);
                std::string left_des  = read_buffer.substr(position_la+1, position_ld);
                #endif

                x_pos = strtof(x_pos_str.c_str(), NULL);
                y_pos = strtof(y_pos_str.c_str(), NULL);
                theta = strtof(theta_str.c_str(), NULL);
                
                #ifdef RPM_MONITOR
                r_actual = stoi(right_act, NULL);
                r_desire = stoi(right_des, NULL);
                l_actual = stoi(left_act, NULL);
                l_desire = stoi(left_des, NULL);

                rpm_monitor.actual_left = l_actual;
                rpm_monitor.actual_right= r_actual;
                rpm_monitor.desire_left = l_desire;
                rpm_monitor.desire_right= r_desire;
                
                #endif

                geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(theta);
                double q0, q1, q2, q3;
                q0 = odom_quat.w; q1 = odom_quat.x; q2 = odom_quat.y; q3 = odom_quat.z;
                double d = sqrt(q0*q0+q1*q1+q2*q2+q3*q3); // it might be unsafe when d=0;

                current_time = ros::Time::now();

                t.header.stamp = current_time;
                t.transform.translation.x = x_pos;
                t.transform.translation.y = y_pos;
                t.transform.rotation.w = q0/d;
                t.transform.rotation.x = q1/d;
                t.transform.rotation.y = q2/d;
                t.transform.rotation.z = q3/d;

                if(publish_tf)
                {
                    broadcaster.sendTransform(t);
                }
            
                odom_msg.header.stamp = current_time;
                odom_msg.pose.pose.position.x = x_pos;
                odom_msg.pose.pose.position.y = y_pos;
                odom_msg.pose.pose.orientation.w = q0/d;
                odom_msg.pose.pose.orientation.x = q1/d;
                odom_msg.pose.pose.orientation.y = q2/d;
                odom_msg.pose.pose.orientation.z = q3/d;
                // can add velocity part
                odom_msg.twist.twist.linear.x = lin_x;
                odom_msg.twist.twist.angular.z = ang_z;
                //ROS_INFO_STREAM("x: "<< x_pos << ", y: "<< y_pos << ", theta: "<< theta);
            }
            // ----------------------------------------------------------- start serial write
            std::string to_mcu;
            //if(transmit) 
            //{
                int linX_len = snprintf( NULL, 0, "%.4f", lin_x);
                char* linX = (char*)malloc( linX_len+1 );
                snprintf( linX, linX_len+1, "%f", lin_x);

                int angZ_len = snprintf( NULL, 0, "%.4f", ang_z);
                char* angZ = (char*)malloc( angZ_len+1 );
                snprintf( angZ, angZ_len+1, "%f", ang_z);

                //-----------------------------------transmit = false;
                mySerial.write(linX); mySerial.write(" ");
                mySerial.write(angZ); mySerial.write(" ");
                
                if(reset_mcu) { mySerial.write(reset_); mySerial.write(" "); reset_mcu=false; }
                else { mySerial.write("0.0"); mySerial.write(" "); }

                free(linX); free(angZ);
            //}else {
            //    to_mcu = "0.00 0.00";
            //    mySerial.write(to_mcu);
            //}
            // ----------------------------------------------------------- end serial write

            #ifdef RPM_MONITOR
                rpm_pub.publish(rpm_monitor);
            #endif

            odom_pub.publish(odom_msg);
            ros::spinOnce();
            r.sleep();
        }
   
    mySerial.close();
    return 0;
}
