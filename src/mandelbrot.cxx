/**
 *  Mandelbrot Cluster
 *  Author: Michael Kohn
 *   Email: mike@mikekohn.net
 *     Web: https://www.mikekohn.net/
 * License: GPLv3
 *
 * Copyright 2021 by Michael Kohn
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/time.h>

#include "BigFixed.h"
#include "write_bmp.h"

#define WIDTH 1024
#define HEIGHT 1024
//#define WIDTH 256
//#define HEIGHT 256

static int colors[] =
{
  0xff0000,  // f
  0xee3300,  // e
  0xcc5500,  // d
  0xaa5500,  // c
  0xaa3300,  // b
  0x666600,  // a
  0x999900,  // 9
  0x669900,  // 8
  0x339900,  // 7
  0x0099aa,  // 6
  0x0066aa,  // 5
  0x0033aa,  // 4
  0x0000aa,  // 3
  0x000099,  // 2
  0x000066,  // 1
  0x000000,  // 0
};

uint32_t *read_digits(uint32_t *digits, char *s)
{
  int n = 0, r;

  memset(digits, 0, sizeof(uint32_t) * 8);

  for (r = 1; r < 65; r += 8)
  {
    char d[16];
    memset(d, 0, sizeof(d));
    memcpy(d, s + r, 8);

    uint64_t value = strtoll(d, NULL, 16);
    digits[n++] = value;
  }

#if 0
  for (n = 0; n < 8; n++)
  {
    printf("%08x\n", digits[n]);
  }
#endif

  return digits;
}

int mandel_calc(
  int *picture,
  BigFixed &r0,
  BigFixed &r1,
  BigFixed &r_step,
  BigFixed &i0,
  BigFixed &i1,
  BigFixed &i_step)
{
  const int max_count = 127;
  int count, x, y;
  int ptr = 0;

  BigFixed i(i0);

  for (y = 0; y < HEIGHT; y++)
  {
    BigFixed r(r0);

    for (x = 0; x < WIDTH; x++)
    {
      //zr = 0;
      //zi = 0;
      BigFixed zr;
      BigFixed zi;

      for (count = 0; count < max_count; count++)
      {
        // ti = (2 * zr * zi);
        BigFixed ti = zr;
        ti.multiplyTimesTwo();
        ti.multiply(zi);

        // tr = ((zr * zr) - (zi * zi));
        // zr = tr + r;
        zr.square();
        zi.square();

        BigFixed result = zr;
        result.add(zi);
        if (result.getFloor() >= 4) { break; }

        zr.subtract(zi);
        zr.add(r);

        // zi = ti + i;
        zi = ti;
        zi.add(i);
      }

      picture[ptr++] = colors[count >> 3];

      r.add(r_step);
    }

    i.add(i_step);
  }

  return 0;
}

int mandel_calc(
  int *picture,
  double real_start,
  double real_end,
  double imaginary_start,
  double imaginary_end)
{
  BigFixed r_step((real_end - real_start) / (double)WIDTH);
  BigFixed i_step((imaginary_end - imaginary_start) / (double)HEIGHT);

  BigFixed r0(real_start);
  BigFixed r1(real_end);
  BigFixed i0(imaginary_start);
  BigFixed i1(imaginary_end);

  mandel_calc(picture, r0, r1, r_step, i0, i1, i_step);

  return 0;
}

int main(int argc, char *argv[])
{
  struct timeval tv_start, tv_end;
  int picture[WIDTH * HEIGHT];
  const char *filename;

  if (argc != 7)
  {
    printf("Usage: %s <float/fixed> <real_start> <real_end> <imaginary_start> <imaginary_end> <filename>\n", argv[0]);
    exit(0);
  }

  filename = argv[6];

  if (strcmp(argv[1], "fixed") == 0)
  {
    printf("Generate: %s\n", filename);

    uint32_t digits[8];
    BigFixed r0(read_digits(digits, argv[2]), argv[2][0] == '-');
    BigFixed r1(read_digits(digits, argv[3]), argv[3][0] == '-');
    BigFixed i0(read_digits(digits, argv[4]), argv[4][0] == '-');
    BigFixed i1(read_digits(digits, argv[5]), argv[5][0] == '-');

    BigFixed r_step(r1);
    r_step.subtract(r0);
    r_step.divideLog2(10);
    //r_step.divideLog2(8);

    BigFixed i_step(i1);
    i_step.subtract(i0);
    i_step.divideLog2(10);
    //i_step.divideLog2(8);

    gettimeofday(&tv_start, NULL);
    mandel_calc(picture, r0, r1, r_step, i0, i1, i_step);
  }
    else
  if (strcmp(argv[1], "float") == 0)
  {
    double real_start = atof(argv[2]);
    double real_end = atof(argv[3]);
    double imaginary_start = atof(argv[4]);
    double imaginary_end = atof(argv[5]);

    printf("Generate: %s %f %f %f %f\n",
      filename, real_start, real_end, imaginary_start, imaginary_end);

    gettimeofday(&tv_start, NULL);
    mandel_calc(picture, real_start, real_end, imaginary_start, imaginary_end);
  }
    else
  {
    printf("Error: '%s' is should be the word 'fixed' or 'float'\n", argv[1]);
    exit(1);
  }

  gettimeofday(&tv_end, NULL);

  //printf("%ld %ld\n", tv_end.tv_sec, tv_end.tv_usec);
  //printf("%ld %ld\n", tv_start.tv_sec, tv_start.tv_usec);
  long time_diff = tv_end.tv_usec - tv_start.tv_usec;
  while(time_diff < 0) { tv_end.tv_sec--; time_diff += 1000000; }
  time_diff += (tv_end.tv_sec - tv_start.tv_sec) * 1000000;
  printf("time=%f\n", (float)time_diff / 1000000);

  write_bmp(filename, picture, WIDTH, HEIGHT);

  return 0;
}

