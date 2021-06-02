import os
import serial


print("Press 'i' for sending data")
print("Press 'q' to quit")
port = input("port: ")
baud = 9600

ser = serial.Serial(port, baud)


try:
    ser_in = ser.readline().decode('utf-8').strip('\n')
    print(ser_in)
    os.system('streamer -q -c /dev/video0 -f rgb24 -r 3 -t 00:30:00 -o ~/outfile.avi')
except UnicodeDecodeError:
    print("Serial Error")

