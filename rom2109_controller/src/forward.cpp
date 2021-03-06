#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>

float OneRPM = 0.0036;                           // pololu can run 1 rpm.
float min_velocity = OneRPM * 5.0;               // ms
float accelaration_percent = 45.0;
float speed_decrease_percent = (100.0-accelaration_percent)/100.0;
float speed_increase_percent = accelaration_percent/100.0;

float cm_to_meter(float cm);

int main(int argc, char** argv)
{
    if(argc != 3) { 
        std::cout<<"ERROR!"<<std::endl;
        std::cout<<"[ Usage: ]"<<std::endl;
        std::cout<<"    rosrun rom2109_controller forward [+m/s] [+cm]"<<std::endl<<std::endl;
        std::cout<<"    example: rosrun rom2109_controller forward 0.2 100"<<std::endl;
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
    float linear_velocity = abs(vel);                                // ms
    
    geometry_msgs::Twist move_cmd;
    move_cmd.linear.x = 0.0;                                   // for smooth
    
    ros::Rate r(rate);

    ros::Duration(1).sleep();
    move_cmd.linear.x += min_velocity;

    double linear_scale = 0.0;
    nh_private_.getParam("linear_scale", linear_scale);
    
    float goal_distance = cm_to_meter(dis) * linear_scale;    // meter

        try     {   listener.waitForTransform("odom","base_link", ros::Time(0), ros::Duration(1.0));            }
        catch(tf::LookupException e)    
                {   ROS_INFO_STREAM("Cannot wait tf between /odom and /baselink. Error= "<< e.what()<<"\n");    }

        try     {   listener.lookupTransform("odom","base_link", ros::Time(0), transform);                      }
        catch(tf::TransformException e)
                {   ROS_INFO_STREAM("Cannot get tf between /odom and /baselink. Error= "<< e.what()<<"\n");     } 

    float x_start = transform.getOrigin().x();
    float y_start = transform.getOrigin().y();
    float distance = 0;
    
    while(distance < goal_distance)
    { //-----------------------------------------------------------------------------------------------------------------
        if( distance < (goal_distance*speed_increase_percent) ) 
        {
            move_cmd.linear.x += OneRPM;
            if( move_cmd.linear.x > linear_velocity) { move_cmd.linear.x = linear_velocity; }
            
        }
        else if( distance > ( goal_distance*speed_decrease_percent ) )
        {
            move_cmd.linear.x -= OneRPM;
            if( move_cmd.linear.x < min_velocity) { move_cmd.linear.x = min_velocity; }
        }
        // else {
        //     move_cmd.linear.x = linear_velocity;
        // }
        pub.publish(move_cmd);
        r.sleep();

        try
        {
            listener.lookupTransform("odom","base_link", ros::Time(0), transform);
        }
        catch(tf::TransformException e)
        {
            ROS_INFO_STREAM("Cannot get tf between /odom and /baselink. Error= "<< e.what()<<"\n");
        } 

        distance = sqrt(pow(transform.getOrigin().x() - x_start, 2) + pow(transform.getOrigin().y() - y_start, 2) );

     
    } //-----------------------------------------------------------------------------------------------------------------
        
   
    // stop
    for( int i=0;i<20;i++)
    {
        move_cmd.linear.x = 0.0;
        pub.publish(move_cmd);
        r.sleep();
    }
    
    ros::Duration(1).sleep();   

    ros::shutdown();
    return 0;
}

float cm_to_meter(float cm)
{
    return (cm/100.0);
}
