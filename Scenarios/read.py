import serial

ser = serial.Serial('/dev/ttyUSB0',57600)

f = open('messageNew.txt','a')

while 1 :
    f.write(ser.readline())
    f.close()
    f = open('messageNew.txt','a')
