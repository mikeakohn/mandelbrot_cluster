#include <stdio.h>
#include <stdlib.h>

//#include "BigNumber.h"
#include "BigFixed.h"

int test_add_1()
{
  BigFixed num(2, 0.0);
  BigFixed fix_4_4(4, 0.4);

  num.add(fix_4_4);
  num.add(fix_4_4);
  num.add(fix_4_4);

  if (num.getFloor() != 15)
  {
    printf("ERROR: test_add_1() %d\n", num.getFloor());
    return 1;
  }

  return 0;
}

int test_add_2()
{
  BigFixed num(2, 0.0);
  BigFixed fix_n4_4(-4, 0.4);

  num.add(fix_n4_4);
  num.add(fix_n4_4);
  num.add(fix_n4_4);

  if (num.getFloor() != -12)
  {
    printf("ERROR: test_add_2() %d\n", num.getFloor());
    return 1;
  }

  return 0;
}

int test_add_3()
{
  BigFixed num(2, 0.0);
  BigFixed fix_n1_4(-1, 0.4);

  num.add(fix_n1_4);

  if (num.getFloor() != 0)
  {
    printf("ERROR: test_add_3() %d\n", num.getFloor());
    return 1;
  }

  return 0;
}

int test_add_4()
{
  BigFixed num(0, 0.0);
  BigFixed fix(-0.236600);

  num.add(fix);

  if (num.getFloor() != -1)
  {
    printf("ERROR: test_add_4() %d\n", num.getFloor());
    return 1;
  }

  return 0;
}

int test_subtract_1()
{
  BigFixed num(2, 0.0);
  BigFixed fix_1_4(1, 0.4);

  num.subtract(fix_1_4);
  num.subtract(fix_1_4);
  num.subtract(fix_1_4);

  if (num.getFloor() != -3)
  {
    printf("ERROR: test_subtract_1() %d\n", num.getFloor());
    return 1;
  }

  return 0;
}

int test_subtract_2()
{
  BigFixed num(2, 0.0);
  BigFixed fix_n1_4(-1, 0.4);

  num.subtract(fix_n1_4);

  if (num.getFloor() != 3)
  {
    printf("ERROR: test_subtract_2() %d\n", num.getFloor());
    return 1;
  }

  return 0;
}

int test_subtract_3()
{
  BigFixed num(-2, 0.0);
  BigFixed fix_n1_4(-1, 0.4);

  num.subtract(fix_n1_4);

  if (num.getFloor() != -1)
  {
    printf("ERROR: test_subtract_3() %d\n", num.getFloor());
    return 1;
  }

  return 0;
}

int test_subtract_4()
{
  BigFixed zr(0.203329);
  BigFixed zi(0.169484);

  uint32_t *digits;

  digits = zr.getDigits();
  digits[0] = 0xe4a6f431;
  digits[1] = 0x30b0c04c;
  digits[2] = 0x340d62a1;
  digits[3] = 0x00000000;
  zr.setPositive();

  digits = zi.getDigits();
  digits[0] = 0x597e8b6b;
  digits[1] = 0x44d077d7;
  digits[2] = 0x2b6348e8;
  digits[3] = 0x00000000;
  zi.setPositive();

  zr.subtract(zi);

  if (zr.getFloor() != 0)
  {
    printf("ERROR: test_subtract_3() %d\n", zr.getFloor());
    return 1;
  }

  return 0;
}

int test_multiply_1()
{
  BigFixed num(3, 0.0);
  BigFixed fix_n1_4(-5, 0.8);

  num.multiply(fix_n1_4);

  if (num.getFloor() != -18)
  {
    printf("ERROR: test_multiply_1() %d\n", num.getFloor());
    return 1;
  }

  return 0;
}

int test_multiply_2()
{
  BigFixed num(1, 0.0);
  BigFixed fix_n1_1(0, 0.00001);

  num.multiply(fix_n1_1);

  if (num.getFloor() != 0)
  {
    printf("ERROR: test_multiply_2() %d\n", num.getFloor());
    return 1;
  }

  return 0;
}

int test_multiply_3()
{
  BigFixed num(-7, 0.7);
  BigFixed fix(-7, 0.7);

  num.multiply(fix);

  if (num.getFloor() != 59)
  {
    printf("ERROR: test_multiply_3() %d\n", num.getFloor());
    return 1;
  }

  return 0;
}

int test_multiply_4()
{
  BigFixed num(2, 0.0);
  BigFixed zr(1.403846);
  BigFixed zi(0.607873);

  num.multiply(zr);
  num.multiply(zi);

  if (num.getFloor() != 1)
  {
    printf("ERROR: test_multiply_4() %d\n", num.getFloor());
    return 1;
  }

  return 0;
}

int test_multiply_5()
{
  uint32_t *digits;

  BigFixed num(2, 0.0);
  BigFixed zr(1.403846);
  BigFixed zi(0.607873);

  digits = zr.getDigits();
  digits[0] = 0x8b2868c6;
  digits[1] = 0xebe04875;
  digits[2] = 0x67626ba3;
  digits[3] = 0x00000001;
  zr.setPositive();

  digits = zi.getDigits();
  digits[0] = 0xb3a27ab7;
  digits[1] = 0xf24333fc;
  digits[2] = 0x9b9d9858;
  digits[3] = 0x00000000;
  zi.setPositive();

//zr.dump();
//zi.dump();

  num.multiply(zr);
  num.multiply(zi);
//printf("%f\n", num.getValue());

  if (num.getFloor() != 1)
  {
    printf("ERROR: test_multiply_5() %d\n", num.getFloor());
    return 1;
  }

  return 0;
}

int test_multiply_6()
{
  BigFixed num(2, 0.0);
  BigFixed zr(0.370000);
  BigFixed zi(-0.236600);

  num.multiply(zr);
  num.multiply(zi);

//printf("%f\n", num.getValue());
  if (num.getFloor() != -1)
  {
    printf("ERROR: test_multiply_6() %d\n", num.getFloor());
    return 1;
  }

  return 0;
}

int test_square_1()
{
  BigFixed num(-7, 0.7);

  num.square();

  if (num.getFloor() != 59)
  {
    printf("ERROR: test_square_1() %d\n", num.getFloor());
    return 1;
  }

  return 0;
}

int test_double()
{
  BigFixed num(5.5);

  if (num.getFloor() != 5)
  {
    printf("ERROR: test_double() %d\n", num.getFloor());
    return 1;
  }

  return 0;
}

int test_copy()
{
  BigFixed num(5.5);
  BigFixed temp = num;

  if (temp.getFloor() != 5)
  {
    printf("ERROR: test_double() %d\n", temp.getFloor());
    return 1;
  }

  //temp.dump();

  return 0;
}

int test_times_2()
{
  BigFixed num(5.5);

  num.multiplyTimesTwo();

  if (num.getFloor() != 11)
  {
    printf("ERROR: test_double() %d\n", num.getFloor());
    return 1;
  }

  //temp.dump();

  return 0;
}

int test_multiply_fast()
{
  uint32_t *digits;

  BigFixed zr(0.0);
  BigFixed zi(0.0);

  digits = zr.getDigits();
  digits[0] = 0x00000000;
  digits[1] = 0x00000000;
  digits[2] = 0xffffffff;
  digits[3] = 0xffffffff;
  digits[4] = 0xffffffff;
  digits[5] = 0x00000008;
  digits[6] = 0x00000000;
  digits[7] = 0x00000000;
  zr.setPositive();

  digits = zi.getDigits();
  digits[0] = 0x00000000;
  digits[1] = 0x00000000;
  digits[2] = 0xffffffff;
  digits[3] = 0xffffffff;
  digits[4] = 0xffffffff;
  digits[5] = 0x00000008;
  digits[6] = 0x00000000;
  digits[7] = 0x00000000;
  zi.setPositive();

//zr.dump();
//zi.dump();

  zr.square();
  zi.squareSlow();

//zr.dump();
//zi.dump();

  uint32_t *digits_zr = zr.getDigits();
  uint32_t *digits_zi = zi.getDigits();

  for (int n = 0; n < LENGTH; n++)
  {
    if (digits_zr[n] != digits_zi[n])
    {
      printf("Error: %d> %d %d\n", n, digits_zr[n], digits_zi[n]);
      return 1;
    }
  }

  return 0;
}

int main(int argc, char *argv[])
{
  int errors = 0;

  errors += test_add_1();
  errors += test_add_2();
  errors += test_add_3();
  errors += test_add_4();

  errors += test_subtract_1();
  errors += test_subtract_2();
  errors += test_subtract_3();
  errors += test_subtract_4();

  errors += test_multiply_1();
  errors += test_multiply_2();
  errors += test_multiply_3();
  errors += test_multiply_4();
  errors += test_multiply_5();
  errors += test_multiply_6();

  errors += test_square_1();
  errors += test_copy();
  errors += test_times_2();

  errors += test_multiply_fast();

  printf("%s\n", errors == 0 ? "PASSED" : "FAILED");

  return 0;
}

