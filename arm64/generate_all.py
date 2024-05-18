#!/usr/bin/env python3

import sys, os, math

def get_rotated_size(filename):
  p = os.popen("identify " + filename, "r")
  line = p.readline().strip()
  p.close()

  size = line.split()[2]

  print(size)

  (width, height) = size.split("x")
  return (int(width), int(height))

def print_info(frame_number, r0, r1, i0, i1, rotate):
  print("%d,%f,%f,%f,%f,%d,%.2fs" % (frame_number, r0, r1, i0, i1, rotate, float(frame_number) / 60))

def generate_frame(frame_number, r0, r1, i0, i1, rotate):
  print_info(frame_number, r0, r1, i0, i1, rotate)
  return

  filename = "images/frame%05d.png" % (frame_number)

  command = "./mandelbrot normal " + \
    str(r0) + " " + \
    str(r1) + " " + \
    str(i0) + " " + \
    str(i1) 

  print(command)

  os.system(command)

  if rotate != 0:
    os.system("convert -rotate " + str(rotate) + " out.bmp out_2.bmp")
    os.system("mv out_2.bmp out.bmp")

  (rotated_width, rotated_height) = get_rotated_size("out.bmp")

  #print(rotated_width)
  #print(rotated_height)

  w = 1280
  h = 720

  crop_x = int((rotated_width  / 2) - (w / 2))
  crop_y = int((rotated_height / 2) - (h / 2))

  crop = str(w) + "x" + str(h) + "+" + str(crop_x) + "+" + str(crop_y)
  #crop = str(w) + "x" + str(h)

  print(crop)

  os.system("convert -crop " + crop + " out.bmp " + filename)

class Current:
  def __init__(self, r0, r1, r2, r3, scale):
    self.frame_number = 0

    # Current coordinates.
    self.r0 = _r0 * scale
    self.r1 = _r1 * scale
    self.i0 = _i0 * scale
    self.i1 = _i1 * scale

    # For side zooming.
    self.delta_zoom_r = 0.0
    self.delta_zoon_i = 0.0

    # For side motion.
    self.delta_shift_r = 0.0
    self.delta_shift_i = 0.0

    # Rotation.
    self.rotation = 0
    self.rotation_position = 0.0
    self.rotation_delta = (math.pi * 2) / 752
    self.do_rotation = False

  def set_zoom_value(self, divisor):
    self.delta_zoom_r = (self.r1 - self.r0) / divisor
    self.delta_zoom_i = (self.i1 - self.i0) / divisor

  def set_shift_value(self, divisor):
    self.delta_shift_r = (self.r1 - self.r0) / divisor
    self.delta_shift_i = (self.i1 - self.i0) / divisor

  def zoom_in(self):
    self.r0 += self.delta_zoom_r
    self.r1 -= self.delta_zoom_r
    self.i0 += self.delta_zoom_i
    self.i1 -= self.delta_zoom_i

  def zoom_out(self):
    self.r0 -= self.delta_zoom_r
    self.r1 += self.delta_zoom_r
    self.i0 -= self.delta_zoom_i
    self.i1 += self.delta_zoom_i

  def shift_left(self):
    self.r0 -= self.delta_shift_r
    self.r1 -= self.delta_shift_r

  def shift_right(self):
    self.r0 += self.delta_shift_r
    self.r1 += self.delta_shift_r

  def shift_up(self):
    self.i0 -= self.delta_shift_i
    self.i1 -= self.delta_shift_i

  def shift_down(self):
    self.i0 += self.delta_shift_i
    self.i1 += self.delta_shift_i

  def rotate(self):
    self.rotation = int(90 * math.sin(self.rotation_position))
    self.rotation_position += self.rotation_delta
    self.do_rotation = True

  def reset_rotation(self):
    self.rotation_position = 0.0
    self.do_rotation = False

  def generate(self):
    generate_frame(self.frame_number, self.r0, self.r1, self.i0, self.i1, self.rotation)
    self.frame_number += 1

# -------------------------- fold here --------------------------

_r0 = -2.00;
_r1 = 1.00;
_i0 = -1.00;
_i1 = 1.00;

scale = 4.0

current = Current(_r0, _r1, _i0, _i1, scale)

for i in range(0, 4):
  current.set_zoom_value(800)
  current.set_shift_value(1600)

  for n in range(0, 94):
    current.generate()
    current.zoom_in()
    current.shift_right()
    current.rotate()

  for n in range(0, 94):
    current.generate()
    current.zoom_in()
    current.shift_left()
    current.rotate()

#print(current.rotation)
#print(current.rotation_position)
#sys.exit(0)
current.reset_rotation()

current.set_zoom_value(800)
current.set_shift_value(800)

for n in range(0, 200):
  current.generate()
  current.shift_right()

for n in range(0, 300):
  current.generate()
  current.zoom_in()

current.set_shift_value(800)

for n in range(0, 100):
  current.generate()
  current.shift_down()

current.set_zoom_value(1200)
current.set_shift_value(20000)

for n in range(0, 500):
  current.generate()
  current.zoom_in()
  current.shift_right()

current.set_zoom_value(1200)
current.set_shift_value(16000)

for n in range(0, 500):
  current.generate()
  current.zoom_in()
  current.shift_left()
  current.shift_up()

current.set_zoom_value(1200)
current.set_shift_value(16000)

for n in range(0, 700):
  current.generate()
  current.zoom_in()

current.set_zoom_value(800)
current.set_shift_value(16000)

for n in range(0, 500):
  current.generate()
  current.zoom_out()

current.set_zoom_value(200)

for n in range(0, 500):
  current.generate()
  current.zoom_out()

current.set_zoom_value(200)

for n in range(0, 500):
  current.generate()
  current.zoom_out()

current.set_zoom_value(100)

for n in range(0, 500):
  current.generate()
  current.zoom_out()

current.set_zoom_value(100)

for n in range(0, 600):
  current.generate()
  current.zoom_out()

