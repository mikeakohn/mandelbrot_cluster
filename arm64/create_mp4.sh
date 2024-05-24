#!/usr/bin/env bash

#ffmpeg -start_number -pattern_type glob -i 'images/*.png' -framerate 30 -c:v libx264 -r 60 -pix_fmt yuv420p out.mp4

ffmpeg \
  -y \
  -framerate 60 \
  -start_number 0 \
  -i /var/www/html/mandelbrot_cluster/images/frame%05d.png \
  -c:v libx264 \
  out.mp4

  #-filter:v fps=60 \
  #-r 60 \
  #-pix_fmt yuv420p \

