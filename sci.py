#!/usr/bin/env python
# -*- coding: utf-8 -*-

import serial
import time, threading

class Sci:
    def __init__(self):
        self.ser = serial.Serial('/dev/ttyAMA1', 115200, timeout=3)
        self.line = ''

    def write(self, data, flag):
        word = '*' + data + '\n'
        trans = word.encode('utf-8')
        self.ser.write(trans)

    def read(self):
        for c in self.ser.read():
            self.line = self.line + (chr(c))
            if self.line.startswith('[') and self.line.endswith(']'):
                print('receive data=' + self.line)
                self.line = ''

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
            line = line + (chr(c))
            if line.startswith('[') and line.endswith(']'):
                print('receive data=' + line)
                line = ''
    print("readthread end")

def test_main():
    global alivethread
    alivethread = True

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

if __name__ == '__main__':
    test_main()
