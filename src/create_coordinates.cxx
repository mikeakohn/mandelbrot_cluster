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
  BigFixed r0;
  BigFixed r1;
  BigFixed i0;
  BigFixed i1;

  BigFixed rx;
  BigFixed ix;
  BigFixed rx_negative;
  BigFixed ix_negative;
};

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

void zoom()
{
}

int main(int argc, char *argv[])
{
  FILE *out;
  int frame_count = 0;
  int n;

  BigFixed r0(-2.00);
  BigFixed r1( 1.00);
  BigFixed i0(-1.25);
  BigFixed i1( 1.25);

  out = fopen("coordinates.txt", "wb");

  if (out == NULL)
  {
    printf("Error: Can't open output file.\n");
    exit(1);
  }

  BigFixed rx(r1);
  BigFixed ix(i1);

  rx.subtract(r0);
  ix.subtract(i0);

  rx.divideLog2(DIVISOR);
  ix.divideLog2(DIVISOR);

  printf("frame_count=%d\n", frame_count);

  for (n = 0; n < 128; n++)
  {
    fprintf(out, "frame_%05d.bmp:\n", frame_count++);

    printDigits(out, r0);
    printDigits(out, r1);
    printDigits(out, i0);
    printDigits(out, i1);

    r0.add(rx);
    i0.add(ix);
  }

  rx.divideLog2(2);
  ix.divideLog2(2);

  BigFixed rx_negative(rx);
  BigFixed ix_negative(ix);

  rx_negative.negate();
  ix_negative.negate();

  printf("frame_count=%d\n", frame_count);

  for (n = 0; n < 64; n++)
  {
    fprintf(out, "frame_%05d.bmp:\n", frame_count++);

    printDigits(out, r0);
    printDigits(out, r1);
    printDigits(out, i0);
    printDigits(out, i1);

    r0.add(rx);
    i0.add(ix);
    r1.add(rx_negative);
    i1.add(ix_negative);
  }

  RECALCULATE();

  rx.divideLog2(DIVISOR + 1);
  ix.divideLog2(DIVISOR + 1);
  rx_negative.divideLog2(DIVISOR + 1);
  ix_negative.divideLog2(DIVISOR + 1);

  printf("frame_count=%d\n", frame_count);

  for (n = 0; n < 200; n++)
  {
    fprintf(out, "frame_%05d.bmp:\n", frame_count++);

    printDigits(out, r0);
    printDigits(out, r1);
    printDigits(out, i0);
    printDigits(out, i1);

    r0.add(rx);
    i0.add(ix);
    r1.add(rx_negative);
    i1.add(ix_negative);
  }

  int r;

  for (r = 0; r < 4; r++)
  {
    RECALCULATE();

    rx.divideLog2(DIVISOR + 1);
    ix.divideLog2(DIVISOR + 1);
    rx_negative.divideLog2(DIVISOR + 1);
    ix_negative.divideLog2(DIVISOR + 1);

    printf("frame_count=%d\n", frame_count);

    for (n = 0; n < 128; n++)
    {
      fprintf(out, "frame_%05d.bmp:\n", frame_count++);

      printDigits(out, r0);
      printDigits(out, r1);
      printDigits(out, i0);
      printDigits(out, i1);

      r0.add(rx);
      //i0.add(ix);
      //r1.add(rx_negative);
      i1.add(ix_negative);
    }
  }

  for (r = 0; r < 10; r++)
  {
    RECALCULATE();

    rx.divideLog2(DIVISOR + 1);
    ix.divideLog2(DIVISOR + 1);
    rx_negative.divideLog2(DIVISOR + 1);
    ix_negative.divideLog2(DIVISOR + 1);

    printf("frame_count=%d\n", frame_count);

    for (n = 0; n < 128; n++)
    {
      fprintf(out, "frame_%05d.bmp:\n", frame_count++);

      printDigits(out, r0);
      printDigits(out, r1);
      printDigits(out, i0);
      printDigits(out, i1);

      r0.add(rx);
      i0.add(ix);
      r1.add(rx_negative);
      i1.add(ix_negative);
    }
  }

#if 0
  for (r = 0; r < 10; r++)
  {
    RECALCULATE();

    rx.divideLog2(DIVISOR + 1);
    ix.divideLog2(DIVISOR + 1);
    rx_negative.divideLog2(DIVISOR + 1);
    ix_negative.divideLog2(DIVISOR + 1);

    printf("frame_count=%d\n", frame_count);

    for (n = 0; n < 128; n++)
    {
      fprintf(out, "frame_%05d.bmp:\n", frame_count++);

      printDigits(out, r0);
      printDigits(out, r1);
      printDigits(out, i0);
      printDigits(out, i1);

      r0.add(rx);
      i0.add(ix);
      r1.add(rx_negative);
      i1.add(ix_negative);
    }
  }
#endif

  printf("total_count=%d\n", frame_count);

  fclose(out);

  return 0;
}

