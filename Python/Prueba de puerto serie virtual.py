# -*- coding: utf-8 -*-
"""
Created on Mon Dec 18 23:49:18 2023

@author: Eze
"""

import serial
import time
COM = 'COM3'
com_serial = serial.Serial(COM,9600,8,stopbits=1)

com_serial.close()
if(not(com_serial.isOpen())): #si el puerto está cerrado, lo abre
    com_serial.open()

#i = 0
while True:

    for i in range(20):
        #com_serial.write('I'.encode())
        #com_serial.write(bytes(i))
        #com_serial.write(str(i).encode() + b'\r\n')
        com_serial.write(str(i).encode() + b'\n') #así debe quedar para usar con la planta de quanser
        #com_serial.write(str(i).encode())
        time.sleep(0.1)
        #Lo duermo 3 s entre dato enviado para no saturar el buffer
        print(i)
        print('\n')
        #com_serial.write(b'\n')
com_serial.close()