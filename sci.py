#!/usr/bin/env python
# -*- coding: utf-8 -*-

import serial
import sys, os, time, threading

class Sci:
    def __init__(self):
        self.ser = serial.Serial('/dev/ttyAMA0', 115200, timeout=3)
        self.line = ''

    def write(self, data):
        #word = '*' + data + '\n'
        word = data
        trans = word.encode('utf-8')
        self.ser.write(trans)

    def read(self):
        for c in self.ser.read():
            if chr(c) == '#':
                self.write('g')
                return
            if chr(c) == '\n':
                print(self.line)
                self.line = ''
            else:
                self.line = self.line + (chr(c))

    def sci_close(self):
        self.ser.close()
        print("\nsci exit\n")

#============================================================================#
# test func
#============================================================================#

def readthread(ser):
    global alivethread
    global line
    line = ''
    while alivethread is True:
        for c in ser.read():
            if chr(c) == '\n':
                print(line)
                line = ''
            else:
                line = line + (chr(c))
    print("readthread end")
'''
def test_main():
    global alivethread
    alivethread = True
    global ser
    ser = serial.Serial('/dev/ttyAMA0', 115200, timeout=3)

    thread = threading.Thread(target=readthread, args=(ser,))
    thread.daemon = True
    thread.start()

    count = 10
    while count > 0:
        strcmd = '[test' + str(count) + ']'
        print('send data=' + strcmd)
        ser.write(strcmd.encode())
        time.sleep(1)
        count = count - 1

    alivethread = False
    thread.join()
    ser.close()
'''

if __name__ == '__main__':
    global alivethread, ser
    alivethread = True
    ser = serial.Serial('/dev/ttyAMA0', 115200, timeout=3)

    thread = threading.Thread(target=readthread, args=(ser,))
    thread.daemon = True
    thread.start()

    try:
        while 1:
            time.sleep(1)
    except:
        os.system('killall -9 python')
        sys.exit(0)