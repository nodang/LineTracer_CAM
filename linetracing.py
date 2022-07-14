#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
import cv2, math
import signal
import sys
import os
#============================================================================#
def signal_handler(sig, frame):
    cap.release()
    cv2.destroyAllWindows()
    print("\ntracing exit\n")
    os.system('killall -9 python')
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)
#============================================================================#
cap = cv2.VideoCapture(0)

ORIGIN_WIDTH, ORIGIN_HEIGHT = 640, 480
DIVISION_COEF = 2
SET_WIDTH = ORIGIN_WIDTH//DIVISION_COEF
SET_HEIGHT = ORIGIN_HEIGHT//DIVISION_COEF

cap.set(cv2.CAP_PROP_FRAME_WIDTH, SET_WIDTH)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, SET_HEIGHT)

CAM_HEIGHT = 250
DEG_TO_RAD = math.pi/180
HORIZONTAL, VERTICAL = 62.2*DEG_TO_RAD, 48.8*DEG_TO_RAD
REAL_WIDTH = 2*CAM_HEIGHT*np.tan(HORIZONTAL/2)
#REAL_HEIGHT = 2*CAM_HEIGHT/np.tan(VERTICAL/2)

DIST_PER_PIX_W = REAL_WIDTH/SET_WIDTH
LINE_PIX_W_MAX, LINE_PIX_W_MIN = 30//DIST_PER_PIX_W, 10//DIST_PER_PIX_W
TRUNMAKR_WIDTH, TRUNMAKR_HEIGHT = 50//DIST_PER_PIX_W, 20//DIST_PER_PIX_W
LINE_MARGIN = 25//DIST_PER_PIX_W    #200 / 2
BLANK_MARGIN = 10//DIST_PER_PIX_W
TRUNMARK_MARGIN = 80//DIST_PER_PIX_W
#============================================================================#
def tell_turnmark(inds, cross):
    if cross == 1:
        return 0
    else:
        height = np.int(len(inds)/TRUNMAKR_WIDTH)

        if height >= 2*TRUNMAKR_HEIGHT:
            return 2
        elif height >= 1*TRUNMAKR_HEIGHT:
            return 1
        else:
            return 0
    

def find_white_line(img):
    blur_img = cv2.GaussianBlur(img, (5, 5), 0)
    _, hls_l, _ = cv2.split(cv2.cvtColor(blur_img, cv2.COLOR_BGR2HLS))
    _, hls_l = cv2.threshold(hls_l, 207, 255, cv2.THRESH_BINARY)

    histogram = np.sum(hls_l[hls_l.shape[0]//2:, :], axis=0)
    current = np.argmax(histogram)
    #print(histogram)

    window_h = np.int(hls_l.shape[0]/12)
    line_pix_max = LINE_PIX_W_MAX*window_h
    line_pix_min = LINE_PIX_W_MIN*window_h
    line_inds, lmark_inds, rmark_inds = [], [], []
    line_x = []
    cross = 0

    out_img = np.dstack((hls_l, hls_l, hls_l))*255

    nz = hls_l.nonzero()

    for window in range(12):
        win_yl = hls_l.shape[0] - (window + 1)*window_h
        win_yh = hls_l.shape[0] - window*window_h

        win_xl = np.int(current - LINE_MARGIN)
        win_xh = np.int(current + LINE_MARGIN)
       
        win_left_xh = np.int(win_xl - BLANK_MARGIN)
        win_left_xl = np.int(win_left_xh - TRUNMARK_MARGIN)
       
        win_right_xl = np.int(win_xh + BLANK_MARGIN)
        win_right_xh = np.int(win_right_xl + TRUNMARK_MARGIN)

        cv2.rectangle(out_img, (win_xl, win_yl), (win_xh, win_yh),
                      (255, 0, 0), 2)

        cv2.rectangle(out_img, (win_left_xl, win_yl), (win_left_xh, win_yh),
                      (0, 0, 255), 2)
        cv2.rectangle(out_img, (win_right_xl, win_yl), (win_right_xh, win_yh),
                      (0, 0, 255), 2)

        good_inds = ((nz[0] >= win_yl) &
                     (nz[0] < win_yh) &
                     (nz[1] >= win_xl) &
                     (nz[1] < win_xh)).nonzero()[0]

        left_inds = ((nz[0] >= win_yl) &
                     (nz[0] < win_yh) &
                     (nz[1] >= win_left_xl) &
                     (nz[1] < win_left_xh)).nonzero()[0]

        right_inds = ((nz[0] >= win_yl) &
                      (nz[0] < win_yh) &
                      (nz[1] >= win_right_xl) &
                      (nz[1] < win_right_xh)).nonzero()[0]

        line_inds.append(good_inds)
        lmark_inds.append(left_inds)
        rmark_inds.append(right_inds)

        good_len = len(good_inds)
        
        if good_len >= line_pix_max:
            current = np.int(np.mean(nz[1][good_inds]))
            cross = 1
        elif good_len >= line_pix_min and good_len <= line_pix_max:
            current = np.int(np.mean(nz[1][good_inds]))

        #print(line_pix_min, good_len, line_pix_max)

        line_x.append(current)
    
    line_inds = np.concatenate(line_inds)
    lmark_inds = np.concatenate(lmark_inds)
    rmark_inds = np.concatenate(rmark_inds)

    lmark = tell_turnmark(lmark_inds, cross)
    rmark = tell_turnmark(rmark_inds, cross)

    out_img[nz[0][line_inds], nz[1][line_inds]] = (0, 0, 255)
    out_img[nz[0][lmark_inds], nz[1][lmark_inds]] = (0, 255, 0)
    out_img[nz[0][rmark_inds], nz[1][rmark_inds]] = (0, 255, 0)

    cv2.imshow("cam", out_img)
    cv2.waitKey(1)

    line_x = SET_WIDTH/2 - np.int(np.mean(line_x))

    return line_x, lmark, rmark

def main():
    global cap

    while cap.isOpened():
        ret, frame = cap.read()

        pos, lmark, rmark = find_white_line(frame)
        print(lmark, pos, rmark)

if __name__ == '__main__':
    main()