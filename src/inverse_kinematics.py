#! /usr/bin/env python
import rospy
from geometry_msgs.msg import Twist

def callback(msg):
	global right_motor_duty, left_motor_duty
	wheel_track=0.106
	right_motor_duty=(msg.linear.x+wheel_track/2*msg.angular.z)*100
	left_motor_duty=(msg.linear.x-wheel_track/2*msg.angular.z)*100
	print("right_motor_duty",right_motor_duty)
	print("left_motor_duty",left_motor_duty)

rospy.init_node('inv_kinematics_node')
sub = rospy.Subscriber('/cmd_vel', Twist, callback)
rospy.spin()