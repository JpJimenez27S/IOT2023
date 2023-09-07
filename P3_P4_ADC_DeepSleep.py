# This file is executed on every boot (including wake-boot from deepsleep)
#import esp
#esp.osdebug(None)
#import webrepl
#webrepl.start()
from machine import deepsleep
from machine import Pin
from machine import RTC
from machine import ADC
from time import sleep
import time
from math import sqrt

pin = Pin(34)
adc = ADC(pin)
adc.atten(ADC.ATTN_11DB)

rtc = RTC()
rtcData=rtc.memory()

if len(rtcData)==0: 
    rtcData=b'\x00'


val1=rtcData[0]


if rtcData[0]==0:
    rtcData=b'\x01'
else:
    rtcData=b'\x00'
        
rtc.memory(rtcData) # this command writes writedata into the RTC memory

n = 3585
val2 = 0

#inicio = time.ticks_ms()

for i in range(n):
    val1 = adc.read()
    val2 = val2 + 3.3*val1/4095

val3 = val2/n

#fin = time.ticks_ms()
#print(fin-inicio) 

print('Voltage: ',val3)

sleep(1)
print('Im awake, but Im going to sleep')
#sleep for 1 second (1000 milliseconds)
#deepsleep(1000)