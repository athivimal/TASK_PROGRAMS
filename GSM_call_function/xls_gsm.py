import serial
import RPi.GPIO as GPIO
import time,sys
from pygame import mixer
import numpy as np
import pandas as pd

serialport = serial.Serial("/dev/ttyUSB0", baudrate=115200, timeout=3.0)
print(serialport.name)
mixer.init()
mixer.music.load('/home/covailab/Downloads/16699745754616pwu56hm-voicemaker.in-speech.mp3')
csv_path='/home/covailab/Desktop/py code/number.csv'
df_1= pd.read_csv(csv_path)
print(df_1)
df_1=df_1.fillna('')
df_x=df_1['numbers'].to_list()
def att():
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
    time.sleep(5)
for i in range(len(df_x)):
    print(i)
    x="% s" % df_x[i]
    y = bytes(x, 'utf-8')
    serialport.write(b'ATD'+y+b';\r')
    print("Dialing.......")
    time.sleep(5)
    att()
time.sleep(7)
serialport.write(b'ATH\r')
