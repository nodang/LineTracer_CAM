#!/usr/bin/env python
# -*- coding: utf-8 -*-

import math
import numpy as np
import os, signal, sys
import threading, time

import linetracing as lntc
import sci

class thrd:
    def __init__(self, name):
        self.name = name
        self.alive_thread = False

    def thread_create(self, func, daemon=True):
        self.alive_thread = True
        self.thread = threading.Thread(target=self.thrding, args=(func,))
        if daemon == True:
            self.thread.daemon = True

    def thread_destroy(self):
        self.thread_end()
        self.thread.join()
        print("\n[", self.name, "] thread destroy\n")

    def thread_start(self, func):
        self.thread_create(func)
        self.thread.start()

    def thread_end(self):
        self.alive_thread = False

    def thrding(self, func):
        while self.alive_thread == True:
            func()
        print("\n[", self.name, "] thread end\n")

#============================================================================#
#
#============================================================================#
lt = lntc.trace()

sc = sci.Sci()
sci_rd_th = thrd("sci_read")

def signal_handler(sig, frame):
    sci_rd_th.thread_destroy()
    data = '*' + str(0) + ',' + str(0) + '\n'
    sc.write(data)
    sc.sci_close()
    lt.linetracing_close()
    print("\ncore exit\n")
    os.system('killall -9 python3')
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

def main():
    num = int(sys.argv[1])
    tf = int(sys.argv[2])

    if num > 200:
        num = 200
    elif num < 100:
        num = 100

    if tf == 0:
        tf = False
    else:
        tf = True

    sci_rd_th.thread_start(sc.read)
    print("start")
    sc.write('g')
    
    while True:
        data = lt.linetracing_open(num, debug=tf)
        data = '*' + data + '\n'
        sc.write(data)

        if sc.restart == True:
            sci_rd_th.thread_destroy()
            sc.sci_close()
            lt.linetracing_close()
            restart()

    sci_rd_th.thread_destroy()

    return 0

def restart():
    os.execl(sys.executable, sys.executable, *sys.argv)

if __name__ == '__main__':
    main()
