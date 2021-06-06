import RPi.GPIO as GPIO
from time import sleep
import getch

ena=12
in1=17
in2=27
in3=6
in4=5
enb=13

GPIO.setmode(GPIO.BCM)
GPIO.setup(ena,GPIO.OUT)
GPIO.setup(in1,GPIO.OUT) #sag +
GPIO.setup(in2,GPIO.OUT) #sag -
GPIO.setup(in3,GPIO.OUT) #sol +
GPIO.setup(in4,GPIO.OUT) #sol -
GPIO.setup(enb,GPIO.OUT)

GPIO.output(in1, GPIO.LOW)
GPIO.output(in2, GPIO.LOW)
GPIO.output(in3, GPIO.LOW)
GPIO.output(in4, GPIO.LOW)

p1=GPIO.PWM(ena,20000)
p2=GPIO.PWM(enb,20000)

#p1.start(80)
#p2.start(90)

def forward():
    print("moving forward")
    GPIO.output(in1,GPIO.LOW)
    GPIO.output(in2,GPIO.HIGH)#right forward
    GPIO.output(in3,GPIO.HIGH)#left forward
    GPIO.output(in4,GPIO.LOW)

def backward():
    print("moving backward")
    GPIO.output(in1,GPIO.HIGH)
    GPIO.output(in2,GPIO.LOW)
    GPIO.output(in3,GPIO.LOW)
    GPIO.output(in4,GPIO.HIGH)
    
def turn_right():
    print("turning right")
    GPIO.output(in1,GPIO.HIGH)
    GPIO.output(in2,GPIO.LOW)
    GPIO.output(in3,GPIO.HIGH)
    GPIO.output(in4,GPIO.LOW)
    
def turn_left():
    print("turning left")
    GPIO.output(in1,GPIO.LOW)
    GPIO.output(in2,GPIO.HIGH)
    GPIO.output(in3,GPIO.LOW)
    GPIO.output(in4,GPIO.HIGH)

def stop():
    print("stopped")
    GPIO.output(in1,GPIO.LOW)
    GPIO.output(in2,GPIO.LOW)
    GPIO.output(in3,GPIO.LOW)
    GPIO.output(in4,GPIO.LOW)

def decide():
    while(1):
        x= getch.getch()
        #x=raw_input()

        if x=='w':
            forward()
            sleep(45)
            stop()

        elif x=='s':
            stop()

        elif x=='d':
            turn_right()
            sleep(45)
            stop()

        elif x=='d':
            turn_right()
            sleep(45)
            stop()

        elif x=='a':
            turn_left()
            sleep(45)
            stop()

        elif x=='x':
            backward()
            sleep(45)
            stop()

        elif x=='e':
            print("process has finished")
            break

#if __name__ == "__main__":
    #decide()
    #print("\n")
    #print("The default speed & direction of motor is LOW & Forward.....")
    #print("w-forward d-turn right a-turn left s-stop x-backward l-low m-medium h-high e-exit")