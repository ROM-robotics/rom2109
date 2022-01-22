#!/usr/bin/env python3
import rospy, tf, tf2_ros, geometry_msgs.msg, sensor_msgs.msg

def callback(data, args):
	bc = tf2_ros.TransformBroadcaster()
	bc2= tf2_ros.TransformBroadcaster()
 
	t = geometry_msgs.msg.TransformStamped()
	t2= geometry_msgs.msg.TransformStamped()
 
	t.header.stamp = rospy.Time.now()
	t.header.frame_id = Parent
	t.child_frame_id = Child
	t.transform.translation.x = 0
	t.transform.translation.y = 0
	t.transform.translation.z = 0.1
	t.transform.rotation = data.orientation
 
	t2.header.stamp= rospy.Time.now()
	t2.header.frame_id= 'base_link'
	t2.child_frame_id= 'imu'
	t2.transform.translation.x = 0
	t2.transform.translation.y = 0
	t2.transform.translation.z = 0.1
	t2.transform.rotation.x = 0
	t2.transform.rotation.y = 0
	t2.transform.rotation.z = 0
	t2.transform.rotation.w = 1
 
	bc.sendTransform(t)
	bc2.sendTransform(t2)
	# bc.sendTransform((data.pose.pose.position.x, data.pose.pose.position.y, 0) , (data.pose.pose.orientation.x, data.pose.pose.orientation.y, data.pose.pose.orientation.z, data.pose.pose.orientation.w), rospy.Time.now(), args[1], args[0])

if __name__ == "__main__":
	rospy.init_node("odomtransformer")
	Parent = "odom"
	Child  = "base_link"
	rospy.Subscriber("/android/imu", sensor_msgs.msg.Imu, callback, [Parent, Child])
	rospy.spin()