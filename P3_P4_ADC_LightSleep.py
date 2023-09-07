from machine import lightsleep
from machine import Pin
from machine import ADC
from time import sleep

pin = Pin(4)
adc=ADC(pin)
adc.atten(ADC.ATTN_11DB)

                  
print('Going into Light Sleep Mode')

while True:
    print('Run')    
    
    val1=adc.read()
    val2=3.3*val1/4095
    print('Voltage: ',val2)
    lightsleep(1000)     #1000ms sleep time