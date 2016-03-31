import RPi.GPIO as GPIO
import time
import urllib2
import json
from pushetta import Pushetta
u=1
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(11, GPIO.IN)         #Read output from PIR motion sensor
GPIO.setup(3, GPIO.OUT)         #LED output pin

def sendNotification(token, channel, message):
       API_KEY=token
       #req = urllib2.Request('http://api.pushetta.com/api/pushes/{0)/')
       CHANNEL_NAME=channel
       p=Pushetta(API_KEY)
       p.pushMessage(CHANNEL_NAME,"Somone is there in ur house")
       print  "how r "
      # req.add_header('Content-Type', 'application/json')
       #req.add_header('Authorization', 'Token {0}'.format(token))
       u
      # response = urllib2.urlopen(req, json.dumps(data))
        
while u:
       #i=GPIO.input(11)
       input_state =GPIO.input(11)
       if input_state==True:                 #When output from motion sensor is LOW
            # print "No intruders",i
            # GPIO.output(3, 0)  #Tur OFF LED
            # time.sleep(0.1)
     #  elif i==1:               #When output from motion sensor is HIGH
             GPIO.output(3, 1)
             print "Intruder detected"
             sendNotification("3179689af0bd10e58abbd5b066bfaa8ddc9b9f20", "Theft", "motionnn detected")
              #Turn ON LED
             print  "how r "
             time.sleep(2)
             GPIO.output(3, 0)
             time.sleep(2)
             u=0
             
