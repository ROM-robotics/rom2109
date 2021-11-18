#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include <sstream>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "forward");
    ros::NodeHandle n;
    ros::Publisher pub=n.advertise<geometry_msgs::Twist>("/cmd_vel",50);

    int rate = 20;
    float linear_velocity = 0.1; // ms
    float goal_distance = 1.0;   // meter
    float time_duration;
    int ticks;
    time_duration = goal_distance/linear_velocity; // 5s
    ticks = rate*time_duration;

    geometry_msgs::Twist move_cmd;
    move_cmd.linear.x = linear_velocity * -1.0;
    
    ros::Rate r(rate);

    for(int i=0;i<ticks;i++)
    {
        pub.publish(move_cmd);
        r.sleep();
    }
    
    move_cmd.linear.x = 0.0;
    pub.publish(move_cmd);
    ros::Duration(1).sleep();   

    ros::shutdown();
    return 0;
}

