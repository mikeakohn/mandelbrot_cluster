#!/usr/bin/env python3

import urllib.request
import sys
import os

host = "http://192.168.1.210"

def create_image(host):
  data = { }

  context = urllib.request.urlopen(host + "/mandelbrot_cluster/next.php")

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

  os.system("./mandelbrot fixed " + \
    data["r0"] + " " + \
    data["r1"] + " " + \
    data["i0"] + " " + \
    data["i1"] + " " + \
    "out.bmp")

  crop = "1024x768+0+128"
  jpeg = data["name"] + ".jpeg"

  os.system("convert -quality 100 -crop " + crop + " out.bmp " + jpeg)

  os.system("curl " +
            "-F \"file=@" + jpeg + ";filename=" + jpeg + "\" " + \
            "-F \"coordinate_id=" + data["coordinate_id"] + "\" " +
            host + "/mandelbrot_cluster/save_file.php")

  return True

# ------------------------------ fold here -------------------------------

print("Starting worker_node.py...")

# Originally the idea was to have 16 pods spun up where each pod would
# keep requesting new frames from the server. Unfortunately, Kubernetes
# distributed the pods unevenly among the four Rasperry Pi's so now it
# will create one frame per instance of a pod. Create 1000's of pods where
# 16 can run at a time.

#while True:
#  value = create_image(host)
#
#  if not value: break
#  value = create_image(host)

value = create_image(host)

