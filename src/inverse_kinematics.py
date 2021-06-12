#! /usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
def limit_duty(duty):
	print duty
	if abs(duty)>100:
		print("Duty is regulated")
		duty=duty/abs(duty)*100
	else:
		print("Duty is OK")
		duty=duty
	return duty

def callback(msg):
	global right_motor_duty, left_motor_duty
	wheel_track=1
	right_motor_duty=(msg.linear.x+wheel_track*msg.angular.z)*100
	left_motor_duty=(msg.linear.x-wheel_track*msg.angular.z)*100
	print("right_motor_duty",right_motor_duty)
	print("left_motor_duty",left_motor_duty)
	right_motor_duty=limit_duty(right_motor_duty)
	left_motor_duty=limit_duty(left_motor_duty)
	print("right_motor_duty",right_motor_duty)
	print("left_motor_duty",left_motor_duty)


print("Subscribing the /cmd_vel topic...")
rospy.init_node('inv_kinematics_node')
sub = rospy.Subscriber('/cmd_vel', Twist, callback)
rospy.spin()