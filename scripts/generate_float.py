#!/usr/bin/env python3

import os

# 81s * 60 = 4860 frames.

positions = [
  [   -2.00,   1.00,      -1.25,      1.25 ],
  [ -0.1692, -0.1492,   -1.0442,   -1.0192 ],
  [ -0.1592, -0.1492,   -1.0442,   -1.0317 ],
  [ -0.1545125, -0.1538875, -1.038340625, -1.0375593749999998 ]
];

count = 0

for n in range(0, len(positions) - 1):
  r0 = positions[n][0]
  r1 = positions[n][1]
  i0 = positions[n][2]
  i1 = positions[n][3]

  r0_delta = (positions[n + 1][0] - positions[n][0]) / 10
  r1_delta = (positions[n + 1][1] - positions[n][1]) / 10
  i0_delta = (positions[n + 1][2] - positions[n][2]) / 10
  i1_delta = (positions[n + 1][3] - positions[n][3]) / 10

  while r0 < positions[n + 1][0]:
    filename = "images/frame_%05d.bmp" % (count)

    print(filename + ": " + str(r0) + " to " + str(r1) + ", " + str(i0) + " to " + str(i1))

    os.system("./mandelbrot float " + \
      str(r0) + " " + \
      str(r1) + " " + \
      str(i0) + " " + \
      str(i1) + " " + \
      filename)

    r0 += r0_delta
    r1 += r1_delta
    i0 += i0_delta
    i1 += i1_delta

    count += 1

