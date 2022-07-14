import numpy as np
import cv2
import signal
import sys
import os

def signal_handler(sig, frame):
    cap.release()
    cv2.destroyAllWindows()
    print("\ntracing exit\n")
    os.system('killall -9 python')
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)
#=================================================#
cap = cv2.VideoCapture(0)


def main():
    global cap

    if cap.isOpened():
        ret, frame = cap.read()

        while ret:
            ret, frame = cap.read()
            cv2.imshow("cam", frame)

            cv2.waitKey(1)

if __name__ == '__main__':
    main()