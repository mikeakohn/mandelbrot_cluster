#!/usr/bin/env python3

import os

# 77.8s * 60 = 4668 frames.

fp = open("coordinates.txt", "r")

#start = 0
start = 3312

while True:
  line = fp.readline()
  if not line: break

  filename = "images/" + line.replace(":", "").strip()
  r0 = fp.readline().replace(" ", "").strip()
  r1 = fp.readline().replace(" ", "").strip()
  i0 = fp.readline().replace(" ", "").strip()
  i1 = fp.readline().replace(" ", "").strip()

  #print(filename + ": " + r0 + " to " + r1 + ", " + i0 + " to " + i1)
  print(filename)

  count = int(filename.replace(".bmp", "").split("_")[1])

  if count < start: continue

  os.system("./mandelbrot fixed " + \
    r0 + " " + \
    r1 + " " + \
    i0 + " " + \
    i1 + " " + \
    filename)

fp.close()

