#include <ros/ros.h>
#include <tf/tf.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <math.h>
#include <iostream>
#define PI 3.14159265

nav_msgs::Odometry odom_pos_feedback;
double reference_pose[3];

double roll_feedback, pitch_feedback, yaw_feedback, yaw_reference;

double x_error,y_error,yaw_error, dist_error;

double w_control,v_control;

void counterCallback(const nav_msgs::Odometry::ConstPtr& msg) {
	//ROS_INFO("%s", msg->header.frame_id.c_str());
	//ROS_INFO("%f", msg->twist.twist.linear.x); 
	ROS_INFO("Current Pose: x:%f m, y:%f m, z:%f m", msg->pose.pose.position.x, msg->pose.pose.position.y, msg->pose.pose.position.z);
	odom_pos_feedback.pose= msg->pose;

	x_error=reference_pose[0]-msg->pose.pose.position.x;
	y_error=reference_pose[1]-msg->pose.pose.position.y;
	dist_error=pow(x_error,2)+pow(y_error,2);
	dist_error=sqrt(dist_error);

	if(x_error<0 && y_error<0){
		yaw_reference=atan(y_error/x_error)-PI;
	}
	else if(x_error<0 && y_error>=0){
		yaw_reference=atan(y_error/x_error)+PI;
	}
	else{
		yaw_reference=atan(y_error/x_error);
	}
    tf::Quaternion q(msg->pose.pose.orientation.x,msg->pose.pose.orientation.y,msg->pose.pose.orientation.z,msg->pose.pose.orientation.w);

    tf::Matrix3x3 m(q);
    m.getRPY(roll_feedback, pitch_feedback, yaw_feedback);

    yaw_error=yaw_reference-yaw_feedback;
    if(yaw_error>PI){
    	yaw_error=2*PI-yaw_error;
    }
    else if(yaw_error<-PI){
    	yaw_error=2*PI+yaw_error;
    }

    ROS_INFO("yaw angle: %f yaw_error: %f",yaw_feedback, yaw_error);

}

int main(int argc, char** argv) {
	ros::init(argc, argv, "move_to_pose_node");
	ros::NodeHandle nh;
	ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
	ros::Subscriber sub = nh.subscribe("odom", 1, counterCallback);
	ros::Rate loop_rate(2);
	geometry_msgs::Twist vel;
	double Kp;

	std::cout<<"Enter the desired position\n"<<"x:";
	std::cin>>reference_pose[0];
	std::cout<<"Enter the desired position\n"<<"y:";
	std::cin>>reference_pose[1];
	//std::cout<<"Desired yaw:"<<yaw_reference<<"Current yaw:"<<yaw_feedback<<"\n";
	//std::cout<<"Enter the gain value of linear velocity controller\n";
	//std::cin>>Kp;


	while (ros::ok()) {
		v_control=0.4*dist_error;
		w_control=0.75*yaw_error;
		if (abs(v_control)>1){v_control=v_control/abs(v_control);}
		else{v_control=v_control;}
		if (abs(w_control)>1){w_control=w_control/abs(w_control);}
		else{w_control=w_control;}

		if (abs(dist_error)>0.1 && abs(yaw_error)>0.05){
			vel.linear.x = v_control;
			vel.angular.z = w_control;}

		else if (abs(dist_error)>0.1 && abs(yaw_error)<0.05){
			vel.linear.x = v_control;
			vel.angular.z = 0.0;}
		else{
			vel.linear.x = 0.0;
			vel.angular.z = 0.0;}

		pub.publish(vel);
		ROS_INFO("Velocity: x:%f m/s, w:%f rad/s\n", vel.linear.x, vel.angular.z);
		ros::spinOnce();
		loop_rate.sleep();
	} 
return 0; 
}