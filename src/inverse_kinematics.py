#! /usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
from gpio_configuration import *

def limit_duty(duty):
	if abs(duty)>100:
		duty=duty/abs(duty)*100
	else:
		duty=duty
	return duty

def callback(msg):
	global right_motor_duty, left_motor_duty
	wheel_track=1
	right_motor_duty=(msg.linear.x+wheel_track*msg.angular.z)*100
	left_motor_duty=(msg.linear.x-wheel_track*msg.angular.z)*140
	right_motor_duty=limit_duty(right_motor_duty)
	left_motor_duty=limit_duty(left_motor_duty)
	print("right_motor_duty:",right_motor_duty)
	print("left_motor_duty:",left_motor_duty)
	if(right_motor_duty>0 and left_motor_duty>0):
		forward()
	elif(right_motor_duty>0 and left_motor_duty<0):
		turn_left()
	elif(right_motor_duty<0 and left_motor_duty>0):
		turn_right()
	elif(right_motor_duty<0 and left_motor_duty<0):
		backward()
	elif(right_motor_duty==0 and left_motor_duty==0):
		stop()
	p1.start(abs(right_motor_duty))
	p2.start(abs(left_motor_duty))


print("Subscribing the /cmd_vel topic...")
rospy.init_node('inv_kinematics_node')
sub = rospy.Subscriber('/cmd_vel', Twist, callback)
rospy.spin()