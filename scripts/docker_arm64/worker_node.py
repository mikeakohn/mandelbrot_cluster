#!/usr/bin/env python3

import urllib.request
import sys
import os

host = "http://192.168.1.210"

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

def create_image(host):
  data = { }

  context = urllib.request.urlopen(host + "/mandelbrot_cluster/next_arm64.php")

  for line in context:
    line = line.decode("utf-8").strip()

    if line == "empty":
      print("empty... done")
      return False

    (name, value) = line.split(":")

    name = name.strip()
    value = value.strip()

    data[name] = value

  print(data)

  command = "./mandelbrot simd " + \
    data["r0"] + " " + \
    data["r1"] + " " + \
    data["i0"] + " " + \
    data["i1"]

  os.system(command)

  rotation = int(data["rotation"])
  output = data["name"]

  if rotation != 0:
    os.system("convert -rotate " + str(rotation) + " out.bmp out_2.bmp")
    crop_image("out_2.bmp", data["name"])
  else:
    crop_image("out.bmp", data["name"])

  os.system("curl " +
            "-F \"file=@" + data["name"] + ";" +
            "filename=" + data["name"] + "\" " + \
            "-F \"coordinate_id=" + data["coordinate_id"] + "\" " +
            host + "/mandelbrot_cluster/save_file.php")

  return True

# ------------------------------ fold here -------------------------------

print("Starting worker_node.py...")

for count in range(0, 50):
  value = create_image(host)
  if not value: break

