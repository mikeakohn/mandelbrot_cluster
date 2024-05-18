#!/usr/bin/env python3

import sys, os

def get_rotated_size(filename):
  p = os.popen("identify " + filename, "r")
  line = p.readline().strip()
  p.close()

  size = line.split()[2]

  print(size)

  (width, height) = size.split("x")
  return (int(width), int(height))

def crop_image(filename, outname):
  (rotated_width, rotated_height) = get_rotated_size(filename)

  w = 1280
  h = 720

  crop_x = int((rotated_width  / 2) - (w / 2))
  crop_y = int((rotated_height / 2) - (h / 2))

  crop = str(w) + "x" + str(h) + "+" + str(crop_x) + "+" + str(crop_y)
  #crop = str(w) + "x" + str(h)

  print(crop)

  os.system("convert -crop " + crop + " " + filename + " " + outname)

# ----------------------------- fold here --------------------------

frame_number = int(sys.argv[1])

fp = open("coords.txt", "r")

for line in fp:
  line = line.strip()

  tokens = line.split(",")

  #print(str(frame_number) + " " + tokens[0])

  if frame_number != int(tokens[0]): continue

  r0 = tokens[1]
  r1 = tokens[2]
  i0 = tokens[3]
  i1 = tokens[4]
  rotate = tokens[5]

  print("Frame at " + tokens[6])

  command = "./mandelbrot normal " + \
    r0 + " " + \
    r1 + " " + \
    i0 + " " + \
    i1

  print(command)

  os.system(command)
  os.system("convert -rotate " + str(rotate) + " out.bmp out_2.bmp")

  crop_image("out.bmp", "normal.png")
  crop_image("out_2.bmp", "rotated.png")

  sys.exit(0)

print("Not found")

