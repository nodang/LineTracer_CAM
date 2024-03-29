#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
import cv2, math
import signal, sys, os, time
#============================================================================#
ORIGIN_WIDTH, ORIGIN_HEIGHT = 640, 480
DIVISION_COEF = 2
SET_WIDTH = ORIGIN_WIDTH//DIVISION_COEF
SET_HEIGHT = ORIGIN_HEIGHT//DIVISION_COEF
CROPPED_W = 15
CROPPED_H = SET_HEIGHT/2

CAM_HEIGHT = 270
DEG_TO_RAD = math.pi/180
HORIZONTAL, VERTICAL = 62.2*DEG_TO_RAD, 48.8*DEG_TO_RAD
REAL_WIDTH = 2*CAM_HEIGHT*np.tan(HORIZONTAL/2)
#REAL_HEIGHT = 2*CAM_HEIGHT/np.tan(VERTICAL/2)

DIST_PER_PIX_W = REAL_WIDTH/SET_WIDTH
LINE_PIX_W_MAX, LINE_PIX_W_MIN = 30//DIST_PER_PIX_W, 10//DIST_PER_PIX_W
TURNMAKR_WIDTH, TURNMAKR_HEIGHT = 50//DIST_PER_PIX_W, 20//DIST_PER_PIX_W
LINE_MARGIN = 25//DIST_PER_PIX_W    #200 / 2
BLANK_MARGIN = 10//DIST_PER_PIX_W
TRUNMARK_MARGIN = 80//DIST_PER_PIX_W

WINDOWS_EACH = 8
#============================================================================#
class trace:
    def __init__(self):
        self.cap = cv2.VideoCapture(0)
        self.cap.set(cv2.CAP_PROP_FRAME_WIDTH, SET_WIDTH)
        self.cap.set(cv2.CAP_PROP_FRAME_HEIGHT, SET_HEIGHT)

        self.start_flag = 0
        self.turn_flag = 0
        self.save_time = time.time()
        self.stop_time = 0
        self.hold_time = 0
        self.func_hold_time = 0

        self.save_curr = 0
        self.turnmark_arr = []

        self.debug = False

    def check_mark_height(self, inds):
        height = len(inds)/TURNMAKR_WIDTH

        if height > TURNMAKR_HEIGHT*0.5 and height <=\
            TURNMAKR_HEIGHT*1.5:
            return 1
        elif height >= TURNMAKR_HEIGHT*1.5 and height <=\
                TURNMAKR_HEIGHT*2.5:
            return 2
        else:
            self.hold_time = 0
            return 0

    def tell_turnmark(self, l_inds, r_inds, cross):
        if cross == 1:
            return 0, 0
        else:
            if self.turn_flag == 1 and\
               abs(self.save_time - time.time()) > self.func_hold_time:
                
                self.turn_flag = 0
                self.func_hold_time = 0

                lmark = self.check_mark_height(l_inds)
                rmark = self.check_mark_height(r_inds)

                if lmark != 0 or rmark != 0:
                    if lmark > 0 and rmark > 0:
                        self.hold_time = 0.5
                    else:
                        self.hold_time = 0.0
                    self.save_time = time.time()
                    self.turnmark_arr.append([lmark, rmark])
                else:
                    self.hold_time = 0

                return lmark, rmark

            elif self.turn_flag == 0 and (len(l_inds) > 0 or len(r_inds) > 0):
                self.turn_flag = 1
                self.func_hold_time = 0.4
                self.save_time = time.time()
                return 0, 0
            else:
                return 0, 0

    def find_white_line(self, img):
        cropped = img[0:np.int(CROPPED_H), 
                      np.int(CROPPED_W):np.int(SET_WIDTH - CROPPED_W)]
        _, hls_l, _ = cv2.split(cv2.cvtColor(cropped, cv2.COLOR_BGR2HLS))
        max_l = np.int(np.amax(hls_l)*0.7)
        _, hls_l = cv2.threshold(hls_l, max_l, 255, cv2.THRESH_BINARY)

        histogram = np.sum(hls_l[hls_l.shape[0]//2:, :], axis=0)
        current = np.argmax(histogram)

        window_h = np.int(hls_l.shape[0]/WINDOWS_EACH)
        line_pix_max = LINE_PIX_W_MAX*window_h
        line_pix_min = LINE_PIX_W_MIN*window_h
        line_inds, lmark_inds, rmark_inds = [], [], []
        line_x = []
        cross = 0

        if self.debug == True:
            out_img = np.dstack((hls_l, hls_l, hls_l))

        nz = hls_l.nonzero()

        for window in range(WINDOWS_EACH):
            win_yl = hls_l.shape[0] - (window + 1)*window_h
            win_yh = hls_l.shape[0] - window*window_h

            win_xl = np.int(current - LINE_MARGIN)
            win_xh = np.int(current + LINE_MARGIN)
        
            win_left_xh = np.int(win_xl - BLANK_MARGIN)
            win_left_xl = np.int(win_left_xh - TRUNMARK_MARGIN)
        
            win_right_xl = np.int(win_xh + BLANK_MARGIN)
            win_right_xh = np.int(win_right_xl + TRUNMARK_MARGIN)
            
            if self.debug == True:
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

            line_x.append(current)
        
        line_inds = np.concatenate(line_inds)
        lmark_inds = np.concatenate(lmark_inds)
        rmark_inds = np.concatenate(rmark_inds)

        if len(line_inds) == 0:
            blind_flag = 1
        else:
            blind_flag = 0

        if abs(self.save_time - time.time()) > self.hold_time:
            lmark, rmark = self.tell_turnmark(lmark_inds, rmark_inds, cross)
        else:
            lmark, rmark = 0, 0
        
        if self.debug == True:
            out_img[nz[0][line_inds], nz[1][line_inds]] = (0, 0, 255)
            out_img[nz[0][lmark_inds], nz[1][lmark_inds]] = (0, 255, 0)
            out_img[nz[0][rmark_inds], nz[1][rmark_inds]] = (0, 255, 0)

            cv2.imshow("cam", out_img)
            cv2.waitKey(1)

        if blind_flag == 0:
            self.save_curr = np.mean(line_x)
        
        line_x = SET_WIDTH/2 - CROPPED_W - self.save_curr
        line_x = np.int(line_x)

        if line_x > 25:
            line_x = 25
        if line_x < -25:
            line_x = -25

        return line_x, lmark, rmark

    def decide_val_from_turnmark(self, goal_val, left_mark, right_mark):
        if self.start_flag == 3:
            if abs(time.time() - self.stop_time) > 0.85:
                val = 0
            else:
                val = 150
        elif self.start_flag == 2:
            val = goal_val
            self.start_flag = 3
            print(self.turnmark_arr)
            self.stop_time = time.time()
        elif left_mark == 1 and right_mark == 1:
            if self.start_flag == 1:
                self.start_flag = 2
                val = goal_val
            else:    
                self.start_flag = 1
                val = goal_val
        else:
            val = goal_val

        return val

    def linetracing_open(self, goal_val, debug=False):
        if self.cap.isOpened():
            ret, frame = self.cap.read()
            self.debug = debug
            pos, lmark, rmark = self.find_white_line(frame)
           
            val = self.decide_val_from_turnmark(goal_val, lmark, rmark)

            if debug == True:
                print(lmark, pos, rmark, self.turn_flag, self.start_flag, val)

            data = str(pos) + ',' + str(val)

            return data
    
    def linetracing_close(self):
        self.cap.release()
        cv2.destroyAllWindows()
        print("\ntracing exit\n")

if __name__ == '__main__':
    lt = trace()
    while True:
        lt.linetracing_open()
    lt.linetracing_close()
