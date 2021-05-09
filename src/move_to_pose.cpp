#include <ros/ros.h>
#include <tf/tf.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <math.h>
#include <iostream>

nav_msgs::Odometry odom_pos_feedback;
double reference_pose[3]={10,0,0};

double roll_feedback, pitch_feedback, yaw_feedback, yaw_reference;

double x_error,y_error,yaw_error;

void counterCallback(const nav_msgs::Odometry::ConstPtr& msg) {
	//ROS_INFO("%s", msg->header.frame_id.c_str());
	//ROS_INFO("%f", msg->twist.twist.linear.x); 
	ROS_INFO("Current Pose: x:%f m, y:%f m, z:%f m", msg->pose.pose.position.x, msg->pose.pose.position.y, msg->pose.pose.position.z);
	odom_pos_feedback.pose= msg->pose;

	x_error=reference_pose[0]-msg->pose.pose.position.x;
	y_error=reference_pose[1]-msg->pose.pose.position.y;
	yaw_reference=atan(x_error/y_error);

    tf::Quaternion q(msg->pose.pose.orientation.x,msg->pose.pose.orientation.y,msg->pose.pose.orientation.z,msg->pose.pose.orientation.w);

    tf::Matrix3x3 m(q);
    m.getRPY(roll_feedback, pitch_feedback, yaw_feedback);
    ROS_INFO("yaw angle: %f",yaw_feedback);

    yaw_error=yaw_reference-yaw_feedback;


}

int main(int argc, char** argv) {
	ros::init(argc, argv, "move_to_pose_node");
	ros::NodeHandle nh;
	ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
	ros::Subscriber sub = nh.subscribe("odom", 1, counterCallback);
	ros::Rate loop_rate(2);
	geometry_msgs::Twist vel;
	double Kp;
	std::cout<<"Enter the gain value of yaw\n";
	std::cin>>Kp;


	while (ros::ok()) {
		vel.linear.x = 0.35*x_error;
		//vel.linear.x = 0.2;
		vel.angular.z = Kp*yaw_error;
		pub.publish(vel);
		ROS_INFO("Velocity: x:%f m/s, w:%f rad/s", vel.linear.x, vel.angular.z);
		ros::spinOnce();
		loop_rate.sleep();
	} 
return 0; 
}