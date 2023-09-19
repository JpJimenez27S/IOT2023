import bluetooth
import random
import time
from simpleBLE import BLEPeripheral

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

# Bluetooth object
ble = bluetooth.BLE() 

# Environmental service
service="ed570147-da2a-4e1f-8ae4-a3e11e4c0eec"

# Temperature characteristic
characteristic="e17d00c6-9212-4bf4-b3fa-cda696999862"

# BLE peripheral object
temp = BLEPeripheral(ble,"TIE",service,characteristic) 

PAPP = 0
i = 0
n = 3585
S = 0.066
PA = 0

while True:
    # Write every second, notify every 10 seconds.
    i = (i + 1) % 10
    
    Vprom = MedirVprom(n)
    Irms = MedirIrms(n,S)
    PAPP =  120 * Irms
    PA += PAPP;
    temp.set_values([int(PA)], notify=i == 0, indicate=False)
    print('Potencia ',PA)
    time.sleep_ms(1000)
