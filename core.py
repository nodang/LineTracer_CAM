#!/usr/bin/env python
# -*- coding: utf-8 -*-

import math
import numpy as np
import os, signal, sys
import threading, time

class thrd:
    def __init__(self, name):
        self.name = name
        self.alive_thread = False

    def thread_create(self, func):
        self.alive_thread = True
        self.thread = threading.Thread(target=func)

    def thread_destroy(self):
        self.alive_thread = False
        self.thread.join()
    

def main():

    return 0

if __name__ == '__main__':
    main()
