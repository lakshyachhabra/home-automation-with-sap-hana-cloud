import serial
import RPi.GPIO as GPIO
import time
import urllib2
import json
from pushetta import Pushetta
ser=serial.Serial('/dev/ttyACM0', 9600)
u=1

def sendNotification(token, channel, message):
       API_KEY=token
       #req = urllib2.Request('http://api.pushetta.com/api/pushes/{0)/')
       CHANNEL_NAME=channel
       p=Pushetta(API_KEY)
       p.pushMessage(CHANNEL_NAME,"Warning Gas leakage is there")
       print  "how r "
      # req.add_header('Content-Type', 'application/json')
       #req.add_header('Authorization', 'Token {0}'.format(token))
       u=0

while u:
        if ser.readline()!=None:
            sendNotification("3179689af0bd10e58abbd5b066bfaa8ddc9b9f20", "Gas Leakage", "gas leaked")
             
