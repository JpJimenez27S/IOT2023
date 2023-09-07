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
from math import sqrt

def MedirVprom(n):
    val2 = 0;
    for i in range(n):
        val1 = adc.read()
        val2 = val2 + 3.3*val1/4095

    val3 = val2/n
    return val3;

def MedirIrms(n,S):
    val2 = 0
    Vprom = MedirVprom(n)
    for i in range(n-1):
        val1 = adc.read()
        vn = (3.3*val1/4095)
        val2 = val2 + ((vn - Vprom) ** 2)
    
    val3 = (1/S)*sqrt(val2/n)
    return val3;
    
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
S = 0.066

Vprom = MedirVprom(n)
print(Vprom)
Irms = MedirIrms(n,S)
print(Irms)
PAPP =  120 * Irms
print('Potencia ',PAPP)
sleep(1)

print('Im awake, but Im going to sleep')
#sleep for 1 second (1000 milliseconds)
deepsleep(1000)