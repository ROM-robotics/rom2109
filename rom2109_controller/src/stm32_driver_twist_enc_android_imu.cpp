/*******************************************************************************
 *                    ROM ROBOTICS Co,.Ltd ( Myanmar )    					   *
 *		(ɔ) COPYLEFT 2021 | www.romrobots.com | (+95) 9-259-288-229            *
 *******************************************************************************/ 
#include <string>
#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include "serial/serial.h"
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Imu.h>

#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/TransformStamped.h>

#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

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

double orient_covariance[9] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
geometry_msgs::Quaternion orientation{};

void twistCallback( const geometry_msgs::Twist& robot_velocity)
{
    lin_x = robot_velocity.linear.x;
    ang_z = robot_velocity.angular.z;
}
void IMUCallback( const sensor_msgs::Imu& imu)
{
   
   std::copy(std::begin(imu.orientation_covariance), std::end(imu.orientation_covariance), std::begin(orient_covariance));
   orientation = imu.orientation;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "serial_driver");
    ros::NodeHandle nh_;
    ros::NodeHandle nh_priv;
    ros::Publisher odom_pub = nh_.advertise<nav_msgs::Odometry>("/odom", 50);
    tf::TransformBroadcaster broadcaster;
    ros::Subscriber sub = nh_.subscribe("/cmd_vel", 50, twistCallback);
    ros::Subscriber android_subscriber = nh_.subscribe("/android/imu", 50, IMUCallback);

    serial::Serial mySerial( port, baud, timeout_,
    serial::eightbits, serial::parity_none, serial::stopbits_one, serial::flowcontrol_none );
    
    ros::Rate r(loop_rate);

    char base_link[] = "base_link";
    char odom[] = "odom";
    nav_msgs::Odometry odom_msg;
        odom_msg.header.frame_id = odom;
        odom_msg.child_frame_id = base_link;
        // position part
        odom_msg.pose.pose.position.z = 0.0;
        // velocity part
        odom_msg.twist.twist.linear.y = 0.0;
        odom_msg.twist.twist.linear.z = 0.0;
        odom_msg.twist.twist.angular.x = 0.0;
        odom_msg.twist.twist.angular.y = 0.0;

    geometry_msgs::TransformStamped t;
        t.header.frame_id = odom;
        t.child_frame_id = base_link;
        t.transform.translation.z = 0.0;

    if(! mySerial.isOpen() ) { mySerial.open(); }

        while (ros::ok())
        {   
            current_time = ros::Time::now();
            // ---------------------------------------------------------- start serial read
            if( mySerial.waitReadable() )
            {   
                std::string read_buffer = mySerial.readline(receive_Byte_Size, "\r"); mySerial.flushInput(); // 32 not sure.check firmware
                float x_pos = 0.0, y_pos = 0.0, theta = 0.0;
                std::size_t position_x = read_buffer.find("x");
                std::size_t position_y = read_buffer.find("y");
                std::size_t position_t = read_buffer.find("t");

                std::string x_pos_str = read_buffer.substr(0, position_x);
                std::string y_pos_str = read_buffer.substr(position_x+1, position_y);
                std::string theta_str = read_buffer.substr(position_y+1, position_t);

                x_pos = strtof(x_pos_str.c_str(), NULL);
                y_pos = strtof(y_pos_str.c_str(), NULL);
                theta = strtof(theta_str.c_str(), NULL);
            
                t.transform.translation.x = x_pos;
                t.transform.translation.y = y_pos;
                t.transform.rotation = orientation;
                t.header.stamp = current_time;
                
                broadcaster.sendTransform(t);
                
                odom_msg.header.stamp = current_time;
                odom_msg.pose.pose.position.x = x_pos;
                odom_msg.pose.pose.position.y = y_pos;
                odom_msg.pose.pose.orientation = orientation;
                // can add velocity part
                odom_msg.twist.twist.linear.x = 0;
                odom_msg.twist.twist.angular.z = 0;
                //ROS_INFO_STREAM("x: "<< x_pos << ", y: "<< y_pos << ", theta: "<< theta);
            }
            // ----------------------------------------------------------- start serial write
            std::string to_mcu;

                int linX_len = snprintf( NULL, 0, "%.4f", lin_x);
                char* linX = (char*)malloc( linX_len+1 );
                snprintf( linX, linX_len+1, "%f", lin_x);

                int angZ_len = snprintf( NULL, 0, "%.4f", ang_z);
                char* angZ = (char*)malloc( angZ_len+1 );
                snprintf( angZ, angZ_len+1, "%f", ang_z);
                
                mySerial.write(" ");
                mySerial.write(angZ);
                mySerial.write(" ");
                if(reset_mcu) { mySerial.write(reset_); mySerial.write(" "); reset_mcu=false; }
                free(linX); free(angZ);
            // ----------------------------------------------------------- end serial write

            odom_pub.publish(odom_msg);
            ros::spinOnce();
            r.sleep();
        }
   
    mySerial.close();
    return 0;
}
