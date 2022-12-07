import serial
import RPi.GPIO as GPIO
import time,sys
from pygame import mixer

serialport = serial.Serial("/dev/ttyUSB0", baudrate=115200, timeout=3.0)
print(serialport.name)
mixer.init()
mixer.music.load('/home/covailab/Downloads/16699745754616pwu56hm-voicemaker.in-speech.mp3')
serialport.write(b'ATD8883528139;\r')
print("Dialing.......")
time.sleep(10)
mixer.music.play()
time.sleep(10)
serialport.write(b'ATH\r')