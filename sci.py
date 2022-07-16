#!/usr/bin/env python
# -*- coding: utf-8 -*-

import serial
import time, threading

class Sci:
    def __init__(self):
        self.ser = serial.Serial('/dev/ttyAMA1', 115200, timeout=3)
        self.alive_thread = False
        self.line = ''

    def write(self, data, test=False):
        word = '*' + data + '\n'
        trans = word.encode('utf-8')
        self.ser.write(trans)

        if test:
            t_line = ''
            while True:
                c = self.ser.read()
                t_line = t_line + str(c.decode())
            
                if c == b'\n':
                    print(t_line)
                    t_line = ''
                    break

    def read_thread_create(self):
        self.alive_thread = True
        self.thread = threading.Thread(target=self.read_thread)
        self.thread.daemon = True
        self.thread.start()

    def read_thread_destroy(self):
        self.alive_thread = False
        self.thread.join()
        self.ser.close()

    def read_thread(self):
        while self.alive_thread is True:
            for c in self.ser.read():
                self.line = self.line + (chr(c))
                if self.line.startswith('[') and self.line.endswith(']'):
                    print('receive data=' + self.line)
                    self.line = ''
        print("read thread end")

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
