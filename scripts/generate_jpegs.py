#!/usr/bin/env python3

import os, sys

# This script was for converting a full directory of .bmp's to cropped .jpegs.
# It was used for testing, but probably not that useful for final system.

files = []

for filename in os.listdir("images/"):
  if not filename.endswith(".bmp"): continue
  if not filename.startswith("frame_"): continue
  files.append(filename)

files.sort()

width = 256
height = 256
#width = 1024
#height = 1024

crop_w = width
crop_h = int(height * 768 / 1024)
diff = height - crop_h

crop_y0 = int(diff / 2)
crop_y1 = height - crop_y0

crop = str(crop_w) + "x" + str(crop_h) + "+0+" + str(crop_y0)

print(str(crop_w) + "x" + str(crop_h))
print("(0, " + str(crop_y0) + ")")
print("(" + str(crop_w - 1) + ", " + str(crop_y1) + ")")
print(crop)

count = 0

temp = "images/temp.bmp"

for filename in files:
  print(filename)

  bmp = "images/" + filename
  jpeg = "images/" + filename.replace(".bmp", ".jpeg")

  os.system("convert -quality 100 -crop " + crop + " " + temp + " " + jpeg)

