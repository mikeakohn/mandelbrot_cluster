#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/time.h>

#include "BigFixed.h"
#include "write_bmp.h"

#define WIDTH 1024
#define HEIGHT 768

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

int mandel_calc(
  int *picture,
  int width,
  int height,
  double real_start,
  double real_end,
  double imaginary_start,
  double imaginary_end)
{
  const int max_count = 127;
  int x, y;
  int ptr, count;

  BigFixed r_step((real_end - real_start) / (double)width);
  BigFixed i_step((imaginary_end - imaginary_start) / (double)height);

  ptr = 0;

  BigFixed i(imaginary_start);

  for (y = 0; y < height; y++)
  {
    BigFixed r(real_start);

    for (x = 0; x < width; x++)
    {
      //zr = 0;
      //zi = 0;
      //BigFixed zr(0, 0.0);
      //BigFixed zi(0, 0.0);
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
        zr.subtract(zi);
        zr.add(r);

        // zi = ti + i;
        zi = ti;
        zi.add(i);

        // if ((zr * zr) + (zi * zi) > 4) { break; }
        BigFixed result = zr;
        BigFixed temp = zi;

        if (result.getWholeValue() >= 2) { break; }
        if (temp.getWholeValue() >= 2) { break; }

        result.square();
        temp.square();
        result.add(temp);

        if (result.getFloor() >= 4) { break; }
      }

      picture[ptr++] = colors[count >> 3];

      r.add(r_step);
    }

    i.add(i_step);
  }

  return 0;
}

int main(int argc, char *argv[])
{
  struct timeval tv_start, tv_end;
  int picture[WIDTH * HEIGHT];
#if 0
  double real_start = -0.1592 - 0.01;
  double real_end = -0.1592 + 0.01;
  double imaginary_start = -1.0317 - 0.01;
  double imaginary_end = -1.0317 + 0.01;
#endif

  double real_start = 0.37 - 0.00;
  double real_end = 0.37 + 0.04;
  double imaginary_start = -0.2166 - 0.02;
  double imaginary_end = -0.2166 + 0.02;

#if 0
  double real_start = -2.00;
  double real_end = 1.00;
  double imaginary_start = -1.00;
  double imaginary_end = 1.00;
#endif

  if (argc != 1)
  {
    printf("Usage: %s\n", argv[0]);
    exit(0);
  }

  gettimeofday(&tv_start, NULL);

  mandel_calc(picture, WIDTH, HEIGHT, real_start, real_end, imaginary_start, imaginary_end);

  gettimeofday(&tv_end, NULL);

#if 0
  int picture2[WIDTH * HEIGHT];
  mandel_calc(picture2, WIDTH, HEIGHT, real_start, real_end, imaginary_start, imaginary_end);

  int n;
  for (n = 0; n < WIDTH * HEIGHT; n++)
  {
    if (picture[n] != picture2[n])
    {
      printf("error %d  %8x %8x\n", n, picture[n], picture2[n]);
    }
  }
#endif

  printf("%ld %ld\n", tv_end.tv_sec, tv_end.tv_usec);
  printf("%ld %ld\n", tv_start.tv_sec, tv_start.tv_usec);
  long time_diff = tv_end.tv_usec - tv_start.tv_usec;
  while(time_diff < 0) { tv_end.tv_sec--; time_diff += 1000000; }
  time_diff += (tv_end.tv_sec - tv_start.tv_sec) * 1000000;
  printf("time=%f\n", (float)time_diff / 1000000);

  write_bmp("out.bmp", picture, WIDTH, HEIGHT);

  return 0;
}

