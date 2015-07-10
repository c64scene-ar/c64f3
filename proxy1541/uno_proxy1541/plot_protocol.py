#!/usr/bin/env python
from sys import argv, stdout

from serial import Serial
#import numpy as np
import matplotlib.pyplot as plt

def main(capture_dev):

    serial = Serial(capture_dev, 115200, timeout=0.1)

    #fd = open(capture)
    
    x = [i for i in xrange(2000)]
    #y = [[((k>>2) & 1), ((k >> 1) & 1), (k & 1)] for k in fd.read()]
    y = []
    i = 0
    while True:#for i in xrange(2000):
        stdout.write("\r[+] Sample %09d " % i)
        ch = serial.read(1)
        if ch == "":
            #print "nada @ %d        " % i
            continue
        #y.append(ord(ch))

        packed = ord(ch)
        data = (packed >> 2) & 1
        clk = (packed >> 1) & 1
        atn = packed & 1
        stdout.write("-> D:%d - C:%d - A:%d" % (data, clk, atn))
        #if (data | clk | atn) == 1:
        if clk == 0:
            break
        i += 1


    serial.close()
    #x = np.linspace(0.0, 5,5, 100)
    #y = np.cos(2 * np.pi * x) * np.exp(-x)

    #plt.plot(x, y, 'k')
    #plt.title("C64 IEC protocol representation")
    #plt.xlabel("time (s)")
    #plt.ylabel("voltage (V)")

    #plt.subplots_adjust(left=0.15)
    #plt.show()

if __name__ == "__main__":
    if len(argv) != 2:
        print "Usage:\n\n    %s <capture_device>\n" % argv[0]
    else:
        main(argv[1])
