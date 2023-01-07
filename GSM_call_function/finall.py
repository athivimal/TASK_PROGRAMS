import serial
import RPi.GPIO as GPIO
import time,sys
from pygame import mixer
import numpy as np
import pandas as pd

serialport = serial.Serial("/dev/ttyUSB0", baudrate=115200, timeout=3.0)
mixer.init()
mixer.music.load('/home/covailab/Downloads/16699745754616pwu56hm-voicemaker.in-speech.mp3')
csv_path='/home/covailab/Desktop/GSM_call_function/number.csv'
df_1= pd.read_csv(csv_path)
print(df_1)
df_1=df_1.fillna('')
df_x=df_1['numbers'].to_list()
df_y=df_1['msg'].to_list()
def sr():
    b=b''
    for x in range(60):
        a = serialport.read()
        b=b+a
        if (b[-1]==10):
            break
    if (len(b)!=12):
        for i in range(11-len(b)):
            b=b+b' '
    return b
def status():
    while(1):
        serialport.write(b'AT+CPAS\r')
        c=sr()
        #print(c)
        if (c[7]==48):
            print("call disconnected...")
            serialport.write(b'ATH\r')
            break
        elif (c[7]==52):
            print("call connected...")
            mixer.music.play()
            print("playing audio...")
            break
        elif (c[7]==51):
            print("Ringing...")
    time.sleep(7)
    serialport.write(b'ATH\r')
    print("call disconnected...")
    time.sleep(5)
def msg():
    for i in range(len(df_x)):
        print(i)
        serialport = serial.Serial("/dev/ttyUSB0", baudrate=115200, timeout=3.0)
        x="% s" % df_x[i]
        z="% s" % df_y[i]
        y = bytes(x, 'utf-8')
        w = bytes(z, 'utf-8')
        serialport.write(b'AT+CMGF=1\r')
        time.sleep(1)
        serialport.write(b'AT+CMGS="+91'+y+b'"\r')
        time.sleep(1)
        serialport.write(w)
        time.sleep(2)
        serialport.write(str.encode(chr(26)))
        time.sleep(5)
        print("messaging.......")
        serialport.close()
def call():
    for i in range(len(df_x)):
        print(i)
        serialport = serial.Serial("/dev/ttyUSB0", baudrate=115200, timeout=3.0)
        x="% s" % df_x[i]
        y = bytes(x, 'utf-8')
        serialport.write(b'ATD'+y+b';\r')
        print("Dialing.......")
        time.sleep(5)
        status()
        serialport.close()
    time.sleep(7)
msg()
call()