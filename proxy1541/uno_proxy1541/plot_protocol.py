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
    for i in xrange(2000):
        stdout.write("[+] Sample %d\r" % i)
        ch = serial.read(1)
        if ch == "":
            print "nada @ %d        " % i
            continue
        y.append(ord(ch))

    serial.close()
    #x = np.linspace(0.0, 5,5, 100)
    #y = np.cos(2 * np.pi * x) * np.exp(-x)

    #plt.plot(x, y, 'k')
    #plt.title("C64 IEC protocol representation")
    #plt.xlabel("time (s)")
    #plt.ylabel("voltage (V)")

    #plt.subplots_adjust(left=0.15)
    #plt.show()

    for i in y:
        data = (i >> 2) & 1
        clk = (i >> 1) & 1
        atn = i & 1
        print "-> %d - %d - %d" % (data, clk, atn)

if __name__ == "__main__":
    if len(argv) != 2:
        print "Usage:\n\n    %s <capture_device>\n" % argv[0]
    else:
        main(argv[1])