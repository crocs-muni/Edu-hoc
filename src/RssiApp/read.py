import serial

ser = serial.Serial('/dev/ttyUSB0',57600)

f = open('values.txt','a')
f.write("\n")
character  = '0'
while character != '&' :
    character = ser.read()
    f.write(character)
    f.close()
    f = open('values.txt','a')
