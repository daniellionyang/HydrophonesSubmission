#!/usr/bin/env python3

import sys

import image as im

img = im.read(sys.stdin.buffer)
im.write(sys.stdout.buffer.raw, img)

