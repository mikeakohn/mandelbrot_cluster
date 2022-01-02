
FROM ubuntu:latest
RUN apt update
RUN apt -y install curl imagemagick python3
ADD mandelbrot /root/
ADD worker_node.sh /root/
ADD worker_node.py /root/
RUN chmod 777 /root/worker_node.sh

