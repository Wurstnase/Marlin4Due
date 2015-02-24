#!/usr/bin/env python

""" Generate the stepper delay lookup table for Marlin firmware. """

import argparse

__author__ = "Ben Gamari <bgamari@gmail.com>"
__copyright__ = "Copyright 2012, Ben Gamari"
__license__ = "GPL"

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('-f', '--cpu-freq', type=int, default=84, help='CPU clockrate in MHz (default=16)')
parser.add_argument('-d', '--divider', type=int, default=2, help='Timer/counter pre-scale divider (default=8)')
args = parser.parse_args()

cpu_freq = args.cpu_freq * 1000000
timer_freq = cpu_freq / args.divider

print "#ifndef SPEED_LOOKUPTABLE_H"
print "#define SPEED_LOOKUPTABLE_H"
print
print '#include "Marlin.h"'
print

print "const uint16_t speed_lookuptable_fast[512][2] PROGMEM = {"
a = [ timer_freq / ((i*256)+(32)) for i in range(512) ]
b = [ a[i] - a[i+1] for i in range(511) ]
b.append(b[-1])
for i in range(128):
    print "  ",
    for j in range(8):
        print "{%d, %d}," % (a[8*i+j], b[8*i+j]),
    print 
print "};"
print

print "const uint16_t speed_lookuptable_slow[256][2] PROGMEM = {"
a = [ timer_freq / ((i*8)+(1)) for i in range(256) ]
b = [ a[i] - a[i+1] for i in range(255) ]
b.append(b[-1])
for i in range(32):
    print "  ",
    for j in range(8):
        print "{%d, %d}," % (a[8*i+j], b[8*i+j]),
    print 
print "};"
print

print "#endif"

