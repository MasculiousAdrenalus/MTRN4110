# Date : 08/07/2019
# Author: Annie Wang
# github: https://github.com/annie7777

import serial
import time

#################Things need to be updated########################
port = 'COM3' # windows
#port = '/dev/.....' # MAC
##################################################################
ard = serial.Serial(port,9600,timeout=5)
time.sleep(3) # wait for Arduino

i = 0

while (i < 4):
    # Serial write section
    ard.flush()
    print ("Python value sent: ")
    print ('mtrn4110')
    ard.write(b'mtrn4110')
    
    time.sleep(3) # shortened or lengthen this to match the new value in your Arduino code

    # Serial read section
    msg = ard.read(ard.inWaiting()) # read all characters in buffer
    print ("Message from arduino: ")
    print (msg)
    i = i + 1
    print("-----------------------------")
else:
    print ("Exiting")
