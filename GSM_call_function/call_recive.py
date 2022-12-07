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
time.sleep(5)
for x in range(60):
    serialport.write(b'AT+CLCC\r')
    a = serialport.read(60)
    time.sleep(0.2)
    print(a)
    if (a[11]==75):
        print("call disconnected...")
        serialport.write(b'ATH\r')
        break
    elif (a[21]==48):
        print("call connected...")
        mixer.music.play()
        break
    elif (a[21]==51):
        print("Ringing...")
time.sleep(7)
serialport.write(b'ATH\r')
