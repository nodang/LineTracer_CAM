import serial
import time
import threading

ser = serial.Serial('/dev/ttyAMA1', 115200, timeout=3)

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
    
def write(data, test=False):
    word = '*' + data + '\n'
    trans = word.encode('utf-8')
    ser.write(trans)

    if test:
        line = ''
        while True:
            c = ser.read()
            line = line + str(c.decode())
        
            if c == b'\n':
                print(line)
                line = ''
                break

if __name__ == '__main__':
    test_main()
