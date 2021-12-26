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

#include "BigFixed.h"

#define DIVISOR 8
//#define DIVISOR 10

#define RECALCULATE() \
  rx = r1; \
  ix = i1; \
  rx.subtract(r0); \
  ix.subtract(i0); \
  rx_negative = rx; \
  ix_negative = ix; \
  rx_negative.negate(); \
  ix_negative.negate();

struct Coordinates
{
  Coordinates() : frame_count(0) { }

  void compute(int value)
  {
    rx = r1;
    ix = i1;

    rx.subtract(r0);
    ix.subtract(i0);

    rx.divideLog2(DIVISOR + value);
    ix.divideLog2(DIVISOR + value);

    rx_negative = rx;
    ix_negative = ix;

    rx_negative.negate();
    ix_negative.negate();
  }

  void advance()
  {
    r0.add(rx);
    i0.add(ix);
    r1.add(rx_negative);
    i1.add(ix_negative);
  }

  void advanceWithoutNegative()
  {
    r0.add(rx);
    i0.add(ix);
  }

  void advanceWithoutPositive()
  {
    r1.add(rx_negative);
    i1.add(ix_negative);
  }

  void advancePositiveRNegativeI()
  {
    r0.add(rx);
    i1.add(ix_negative);
  }

  void advanceNegative()
  {
    r0.add(rx_negative);
    i1.add(ix_negative);
  }

  void doubleSpeed()
  {
    rx.multiplyTimesTwo();
    ix.multiplyTimesTwo();
    rx_negative.multiplyTimesTwo();
    ix_negative.multiplyTimesTwo();
  }

  void divideLog2(int value)
  {
    rx.divideLog2(value);
    ix.divideLog2(value);

    rx_negative = rx;
    ix_negative = ix;

    rx_negative.negate();
    ix_negative.negate();
  }

  void printDigits(FILE *out, BigFixed number)
  {
    uint32_t *digits = number.getDigits();
    int count = number.getDigitsLength();
    int n;

    fprintf(out, "  %c", number.isNegative() ? '-' : '+');

    for (n = 0; n < count; n ++)
    {
      fprintf(out, " %08x", digits[n]);
    }

    fprintf(out, "\n");
  }

  void print(FILE *out)
  {
    fprintf(out, "frame_%05d.bmp:\n", frame_count++);

    printDigits(out, r0);
    printDigits(out, r1);
    printDigits(out, i0);
    printDigits(out, i1);
  }

  int frame_count;

  BigFixed r0;
  BigFixed r1;
  BigFixed i0;
  BigFixed i1;

  BigFixed rx;
  BigFixed ix;
  BigFixed rx_negative;
  BigFixed ix_negative;
};

void zoom(Coordinates &coordinates)
{
}

int main(int argc, char *argv[])
{
  FILE *out;
  //int frame_count = 0;
  int n;

  Coordinates coordinates;

  coordinates.r0 = -2.00;
  coordinates.r1 =  1.00;
  coordinates.i0 = -1.25;
  coordinates.i1 =  1.25;

  out = fopen("coordinates.txt", "wb");

  if (out == NULL)
  {
    printf("Error: Can't open output file.\n");
    exit(1);
  }

  coordinates.compute(0);

  printf("frame_count=%d\n", coordinates.frame_count);

  for (n = 0; n < 128; n++)
  {
    coordinates.print(out);
    coordinates.advanceWithoutNegative();
  }

  coordinates.divideLog2(2);

  printf("frame_count=%d\n", coordinates.frame_count);

  for (n = 0; n < 64; n++)
  {
    coordinates.print(out);
    coordinates.advance();
  }

  coordinates.compute(1);

  printf("frame_count=%d\n", coordinates.frame_count);

  for (n = 0; n < 200; n++)
  {
    coordinates.print(out);
    coordinates.advance();
  }

  printf("frame_count=%d\n", coordinates.frame_count);

  int r;

  for (r = 0; r < 6; r++)
  {
    coordinates.compute(1);

    printf("frame_count=%d\n", coordinates.frame_count);

    for (n = 0; n < 100; n++)
    {
      coordinates.print(out);
      coordinates.advancePositiveRNegativeI();
    }
  }

  printf("frame_count=%d\n", coordinates.frame_count);

  for (r = 0; r < 10; r++)
  {
    coordinates.compute(1);

    printf("frame_count=%d\n", coordinates.frame_count);

    for (n = 0; n < 128; n++)
    {
      coordinates.print(out);
      coordinates.advance();
    }
  }

  printf("frame_count=%d\n", coordinates.frame_count);

  for (r = 0; r < 2; r++)
  {
    coordinates.compute(1);

    printf("frame_count=%d\n", coordinates.frame_count);

    for (n = 0; n < 100; n++)
    {
      coordinates.print(out);
      //coordinates.advanceNegative();
      coordinates.advanceWithoutNegative();
    }
  }

  printf("frame_count=%d\n", coordinates.frame_count);

  for (r = 0; r < 5; r++)
  {
    coordinates.compute(1);

    printf("frame_count=%d\n", coordinates.frame_count);

    for (n = 0; n < 128; n++)
    {
      coordinates.print(out);
      coordinates.advance();
    }
  }

  for (n = 0; n < 200; n++)
  {
    coordinates.print(out);
    coordinates.advance();
  }

  printf("HERE frame_count=%d\n", coordinates.frame_count);

  for (r = 0; r < 10; r++)
  {
    coordinates.doubleSpeed();
    coordinates.doubleSpeed();
    coordinates.doubleSpeed();

    for (n = 0; n < 155; n++)
    {
      coordinates.print(out);
      coordinates.advance();

      if (coordinates.frame_count >= 4668) { break; }
    }

    if (coordinates.frame_count >= 4668) { break; }
  }

  printf("total_count=%d\n", coordinates.frame_count);

  fclose(out);

  return 0;
}

