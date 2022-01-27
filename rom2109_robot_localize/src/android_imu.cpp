/*******************************************************************************
 *                    ROM ROBOTICS Co,.Ltd ( Myanmar )    					   *
 *		(ɔ) COPYLEFT 2021 | www.romrobots.com | (+95) 9-259-288-229            *
 *******************************************************************************/ 
#include <ros/ros.h>
#include <sensor_msgs/Imu.h>

sensor_msgs::Imu imu_;

void imuCallback( const sensor_msgs::Imu& imu)
{
    imu_.orientation = imu.orientation;
    imu_.orientation_covariance = imu.orientation_covariance;
    imu_.angular_velocity = imu.angular_velocity;
    imu_.angular_velocity_covariance = imu.angular_velocity_covariance;
    imu_.linear_acceleration = imu.linear_acceleration;
    imu_.linear_acceleration_covariance = imu.linear_acceleration_covariance;
    imu_.header.stamp = imu.header.stamp;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "androidimu2IMU");
    ros::NodeHandle nh_;
    ros::Publisher imu_pub = nh_.advertise<sensor_msgs::Imu>("/androidimu", 50);
    ros::Subscriber imu_sub = nh_.subscribe("/android/imu", 50, imuCallback);

    imu_.header.frame_id="imu";
    ros::Rate r(10);

    while(ros::ok())
    {
        imu_pub.publish(imu_);
        ros::spinOnce();
        r.sleep();
    }
   
    
    return 0;
}
