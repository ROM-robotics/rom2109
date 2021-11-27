#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>

float normalize_angle(float angle)
{
    float res = angle;
    while(res > 3.1416)
    {
        res -= 2.0 * 3.1416;
    }
    while(res < -3.1416)
    {
        res += 2.0 * 3.1416;
    }
    return res;
}

float degree_to_radian(float angle)
{
    return (angle*(3.1415/180.0));
}

int main(int argc, char** argv)
{
        if(argc != 3) { 
        std::cout<<" Error!"<<std::endl;
        std::cout<<" [ Usage: ]"<<std::endl;
        std::cout<<"    rosrun rom2109_controller rotate [+,- r/s] [+degree]"<<std::endl<<std::endl;
        std::cout<<"    example: rosrun rom2109_controller rotate 1.0 90"<<std::endl;
        return -1; 
    }
    float vel = atof(argv[1]);
    float dis = atof(argv[2]);
    //ROS_INFO_STREAM("vel"<< vel << " , dis"<< dis);
    ros::init(argc, argv, "forward");
    ros::NodeHandle n;
    ros::NodeHandle nh_private_("~");
    ros::Publisher pub=n.advertise<geometry_msgs::Twist>("/cmd_vel",50);
    tf::TransformListener listener;
    tf::StampedTransform transform;
    int rate = 20;
    ros::Rate r(rate);

    float angular_velocity = vel;  // rs

    geometry_msgs::Twist move_cmd;
    move_cmd.linear.x = 0.0;
    move_cmd.angular.z = angular_velocity;

    ros::Duration(1).sleep();

    double angular_scale = 0.0;
    nh_private_.getParam("angular_scale", angular_scale);

        
    float goal_angel = degree_to_radian(dis) * angular_scale;               // pi/2
    float angular_tolarance=0.0175;                         // 1 degree
    
    try
    {
        listener.waitForTransform("odom","base_link", ros::Time(0), ros::Duration(1.0));
        //ROS_INFO("waitForTransform");
    }
    catch(tf::LookupException e)
    {
        ROS_INFO_STREAM("Cannot wait tf between /odom and /baselink. Error= "<< e.what()<<"\n");
    }

    try
    {
        listener.lookupTransform("odom","base_link", ros::Time(0), transform);
        //ROS_INFO("first lookupTransform");
    }
    catch(tf::TransformException e)
    {
        ROS_INFO_STREAM("Cannot get tf between /odom and /baselink. Error= "<< e.what()<<"\n");
    } 

    tf::Matrix3x3 m(transform.getRotation());
    double roll, pitch, yaw;
    m.getRPY(roll, pitch, yaw);
    double last_angle = yaw;
    double turn_angle = 0;

    while( abs(turn_angle) < abs(goal_angel) )
    {
        ROS_INFO("moving ..");
        pub.publish(move_cmd);
        r.sleep();

        try
        {
            listener.lookupTransform("odom","base_link", ros::Time(0), transform);
            //ROS_INFO(" lookupTransform in while loop");
        }
        catch(tf::TransformException e)
        {
            ROS_INFO_STREAM("Cannot get tf between /odom and /baselink. Error= "<< e.what()<<"\n");
        } 
        tf::Matrix3x3 m(transform.getRotation());
        m.getRPY(roll,pitch,yaw);
        double rotation = yaw;
        ROS_INFO_STREAM("current Yaw"<< yaw);
        double delta_angle = normalize_angle(rotation- last_angle);
        turn_angle += delta_angle;
        last_angle = rotation;
}
        
   
    // stop
    pub.publish(geometry_msgs::Twist());
    ros::Duration(1).sleep();   
    ROS_INFO("NODE will shutdown!");
    ros::shutdown();
    return 0;
}

