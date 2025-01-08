import serial
import keyboard as kb
import time

port = "COM3"
baudrate = 115200

a = []
count = 0
n = 5
mass = []
last = 0

ser = serial.Serial(port, baudrate=baudrate)

while True:
    line = ser.readline().decode("utf-8").strip()
    a = line.split(",")
    for i in range(n):
        a[count] = int(a[count])
        count += 1
    count = 0
    #print(a)
    if a[0] < 35:
        kb.press("w")
        print("Up")
    if a[0] > 45:
        kb.press("s")
        print("Dawn")
    if a[1] < 35:
        kb.press("q")
        print("Left el")
    if a[1] > 45:
        kb.press("e")
        print("Right el")
    if a[2] < 35:
        kb.press("d")
        print("Right")
    if a[2] > 45:
        kb.press("a")
        print("Left")

    if a[0] < 45 and a[0] > 35:
        kb.release("w")
        kb.release("s")
    if a[1] < 45 and a[1] > 35:
        kb.release("q")
        kb.release("e")
    if a[2] < 45 and a[2] > 35:
        kb.release("a")
        kb.release("d")
        

    
    
