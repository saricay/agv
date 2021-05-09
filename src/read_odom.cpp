#include <ros/ros.h> 
#include <tf/tf.h>
#include <nav_msgs/Odometry.h>

nav_msgs::Odometry odom_pos_feedback;
double reference_pose[3]={10,0,0};
double roll, pitch, yaw;

void counterCallback(const nav_msgs::Odometry::ConstPtr& msg) {
	//ROS_INFO("%s", msg->header.frame_id.c_str());
	//ROS_INFO("%f", msg->twist.twist.linear.x); 
	ROS_INFO("x:%f, y:%f, z:%f", msg->pose.pose.position.x, msg->pose.pose.position.y, msg->pose.pose.position.z);

	odom_pos_feedback.pose= msg->pose;

    tf::Quaternion q(msg->pose.pose.orientation.x,msg->pose.pose.orientation.y,msg->pose.pose.orientation.z,msg->pose.pose.orientation.w);

    tf::Matrix3x3 m(q);
    m.getRPY(roll, pitch, yaw);
    ROS_INFO("yaw angle: %f",yaw);
} 

int main(int argc, char** argv) {
	ros::init(argc, argv, "odom_sub_node"); 
	ros::NodeHandle nh; 
	ros::Subscriber sub = nh.subscribe("odom", 2, counterCallback); 
	ros::spin(); 
	return 0;
}