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

int main(int argc, char *argv[])
{
  FILE *out;
  int frame_count = 0;
  int n;

  BigFixed r0(-2.00);
  BigFixed r1( 1.00);
  BigFixed i0(-1.25);
  BigFixed i1( 1.25);

  //double r0 = -2.00;
  //double r1 =  1.00;
  //double i0 = -1.25;
  //double i1 =  1.25;

  out = fopen("coordinates.txt", "wb");

  if (out == NULL)
  {
    printf("Error: Can't open output file.\n");
    exit(1);
  }

  for (n = 0; n < 10; n++)
  {
    fprintf(out, "frame_%05d.bmp:\n", frame_count++);

    printDigits(out, r0);
    printDigits(out, r1);
    printDigits(out, i0);
    printDigits(out, i1);
  }

  fclose(out);

  return 0;
}

