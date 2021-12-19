
#ifndef BIG_FIXED_H
#define BIG_FIXED_H

#include <string.h>
#include <stdint.h>
#include <math.h>

static const int LENGTH = 8;
static const int WHOLE = LENGTH - 1;
static const int ANSWER_LENGTH = LENGTH * 2;

class BigFixed
{
public:
  BigFixed(int whole, double fraction) : is_negative(false)
  {
    set(whole, fraction);
  }

  BigFixed(double value) : is_negative(false)
  {
    if (value < 0)
    {
      is_negative = true;
      value = -value;
    }

    double whole = floor(value);
    double fraction = value - whole;

    set(whole, fraction);
  }

  BigFixed(const BigFixed &num) : is_negative(num.is_negative)
  {
    memcpy(digits, num.digits, sizeof(digits));
  }

  BigFixed() : is_negative(false)
  {
    memset(digits, 0, sizeof(digits));
  }

  ~BigFixed()
  {
  }

  bool isNegative() const { return is_negative; }
  bool isPositive() const { return !is_negative; }
  void setNegative() { is_negative = true; }
  void setPositive() { is_negative = false; }
  bool signsMatch(const BigFixed &num) { return is_negative == num.is_negative; }

  bool isBiggerThan(const BigFixed &num)
  {
    int n;

    for (n = WHOLE; n >= 0; n--)
    {
      if (digits[n] > num.digits[n]) { return true; }
      if (digits[n] < num.digits[n]) { return false; }
    }

    return true;
  }

  void add(const BigFixed &num)
  {
    if (signsMatch(num))
    {
      addForward(num);
      return;
    }

    if (num.isNegative())
    {
      if (isBiggerThan(num))
      {
        subtractForward(num);
        setPositive();
      }
        else
      {
        subtractReverse(num);
        setNegative();
      }
    }
      else
    {
      if (isBiggerThan(num))
      {
        subtractForward(num);
        setNegative();
      }
        else
      {
        subtractReverse(num);
        setPositive();
      }
    }
  }

  void subtract(const BigFixed &num)
  {
    if (!signsMatch(num))
    {
      addForward(num);
      return;
    }

    if (isPositive())
    {
      if (isBiggerThan(num))
      {
        subtractForward(num);
        setPositive();
      }
        else
      {
        subtractReverse(num);
        setNegative();
      }
    }
      else
    {
      if (isBiggerThan(num))
      {
        subtractForward(num);
        setNegative();
      }
        else
      {
        subtractReverse(num);
        setPositive();
      }
    }
  }

  void multiplyTimesTwo()
  {
    int n;
    int carry = 0;

    for (n = 0; n < LENGTH; n++)
    {
      uint64_t a = (uint64_t)digits[n] << 1;

      digits[n] = (a & 0xffffffff) + carry;
      carry = a >> 32;
    }
  }

  void multiply(const BigFixed &num)
  {
    uint32_t answer[ANSWER_LENGTH];
    int n, i;

    memset(answer, 0, sizeof(answer));

    // For every digit in "num".
    for (n = 0; n < LENGTH; n++)
    {
      uint64_t carry = 0;
      uint64_t value;
      int index = n;

      // Multiply that digit by every digit in "this".
      for (i = 0; i < LENGTH; i++)
      {
        value = (uint64_t)num.digits[n] * (uint64_t)digits[i];
        value += carry + (uint64_t)answer[index];

        carry = value >> 32;
        answer[index++] = value & 0xffffffff;
      }

      while (index < ANSWER_LENGTH && carry != 0)
      {
        value = (uint64_t)answer[index] + carry;
        carry = value >> 32;
        answer[index++] = value & 0xffffffff;
      }
    }

    int dec = LENGTH - 1;

    //memcpy(digits, answer + dec, sizeof(digits));

    for (n = 0; n < LENGTH; n++)
    {
      digits[n] = answer[dec++];
    }

    is_negative = !signsMatch(num);
  }

  void square()
  {
    uint32_t answer[ANSWER_LENGTH];
    int n, i;

    memset(answer, 0, sizeof(answer));

    // For every digit in "num".
    for (n = 0; n < LENGTH; n++)
    {
      uint64_t carry = 0;
      uint64_t value;
      int index = n;

      // Multiply that digit by every digit in "this".
      for (i = 0; i < LENGTH; i++)
      {
        value = (uint64_t)digits[n] * (uint64_t)digits[i];
        value += carry + (uint64_t)answer[index];

        carry = value >> 32;
        answer[index++] = value & 0xffffffff;
      }

      while (index < ANSWER_LENGTH && carry != 0)
      {
        value = (uint64_t)answer[index] + carry;
        carry = value >> 32;
        answer[index++] = value & 0xffffffff;
      }
    }

#if 0
for (n = 0; n < ANSWER_LENGTH; n++)
{
  printf("  - %x\n", answer[n]);
}
#endif

    int dec = LENGTH - 1;

    //memcpy(digits, answer + dec, sizeof(digits));

    for (n = 0; n < LENGTH; n++)
    {
      digits[n] = answer[dec++];
    }

    is_negative = false;
  }

  void multiplySlow(const BigFixed &num)
  {
    uint32_t answer[ANSWER_LENGTH];
    int n, i, j;
    uint32_t r;

    memset(answer, 0, sizeof(answer));

    // For every digit in "num".
    for (n = 0; n < LENGTH; n++)
    {
      // Multiply that digit by every digit in "this".
      for (i = 0; i < LENGTH; i++)
      {
        uint64_t a = (uint64_t)num.digits[n] * (uint64_t)digits[i];

        if (a == 0) { continue; }

        uint64_t carry = a >> 32;
        a &= 0xffffffff;

        r = 0;

        // Add the result to answer, every iteration shifted by one index.
        for (j = n + i; j < ANSWER_LENGTH; j++)
        {
          a += (uint64_t)answer[j] + r;

          r = a >> 32;
          a &= 0xffffffff;

          answer[j] = a;
          a = 0;

          if (r == 0) { break; }
        }

        r = 0;

        // Add carry to the result at the next index.
        for (j = n + i + 1; j < ANSWER_LENGTH; j++)
        {
          carry += (uint64_t)answer[j] + r;

          r = carry >> 32;
          carry &= 0xffffffff;

          answer[j] = carry;
          carry = 0;

          if (r == 0) { break; }
        }
      }
    }

    int dec = LENGTH - 1;

    //memcpy(digits, answer + dec, sizeof(digits));

    for (n = 0; n < LENGTH; n++)
    {
      digits[n] = answer[dec++];
    }

    is_negative = !signsMatch(num);
  }

  void squareSlow()
  {
    uint32_t answer[ANSWER_LENGTH];
    int n, i, j;
    uint32_t r;

    memset(answer, 0, sizeof(answer));

    // For every digit in "num".
    for (n = 0; n < LENGTH; n++)
    {
      // Multiply that digit by every digit in "this".
      for (i = 0; i < LENGTH; i++)
      {
        uint64_t a = (uint64_t)digits[n] * (uint64_t)digits[i];

        if (a == 0) { continue; }

        uint64_t carry = a >> 32;
        a &= 0xffffffff;

        r = 0;

        // Add the result to answer, every iteration shifted by one index.
        for (j = n + i; j < ANSWER_LENGTH; j++)
        {
          a += (uint64_t)answer[j] + r;

          r = a >> 32;
          a &= 0xffffffff;

          answer[j] = a;
          a = 0;

          if (r == 0) { break; }
        }

        r = 0;

        // Add carry to the result at the next index.
        for (j = n + i + 1; j < ANSWER_LENGTH; j++)
        {
          carry += (uint64_t)answer[j] + r;

          r = carry >> 32;
          carry &= 0xffffffff;

          answer[j] = carry;
          carry = 0;

          if (r == 0) { break; }
        }
      }
    }

#if 0
for (n = 0; n < ANSWER_LENGTH; n++)
{
  printf("  - %x\n", answer[n]);
}
#endif

    int dec = LENGTH - 1;

    //memcpy(digits, answer + dec, sizeof(digits));

    for (n = 0; n < LENGTH; n++)
    {
      digits[n] = answer[dec++];
    }

    is_negative = false;
  }

  int getFloor()
  {
    if (isPositive())
    {
      return digits[WHOLE];
    }

    int n;

    for (n = 0; n < LENGTH - 1; n++)
    {
      if (digits[n] != 0) { return -(digits[WHOLE] + 1); }
    }

    return -digits[WHOLE];
  }

  int getWholeValue()
  {
    return digits[WHOLE];
  }

  void dump()
  {
    int n;

    for (n = 0; n < LENGTH; n++)
    {
      printf("  0x%08x\n", digits[n]);
    }

    printf("  (%s)  %f\n", is_negative ? "negative" : "positive", getValue());
  }

  double getValue()
  {
    double whole = (double)digits[WHOLE];
    double fraction = (double)digits[WHOLE - 1] / (double)0x100000000ULL;
    double value = whole + fraction;

    if (isNegative()) { value = -value; }

    return value;
  }

  uint32_t *getDigits()
  {
    return digits;
  }

private:
  void subtractForward(const BigFixed &num)
  {
    int n;
    uint64_t r;
    uint32_t complement[LENGTH];

    int carry = 1;

    for (n = 0; n < LENGTH; n++)
    {
      complement[n] = (num.digits[n] ^ 0xffffffff) + carry;
      carry = complement[n] == 0 ? 1 : 0;
    }

    r = 0;

    for (n = 0; n < LENGTH; n++)
    {
      uint64_t i = (uint64_t)digits[n] + (uint64_t)complement[n] + r;

      digits[n] = i;
      r = i >> 32;
    }
  }

  void subtractReverse(const BigFixed &num)
  {
    int n;
    uint64_t r;
    uint32_t complement[LENGTH];

    int carry = 1;

    for (n = 0; n < LENGTH; n++)
    {
      complement[n] = (digits[n] ^ 0xffffffff) + carry;
      carry = complement[n] == 0 ? 1 : 0;
    }

    r = 0;

    for (n = 0; n < LENGTH; n++)
    {
      uint64_t i = (uint64_t)num.digits[n] + (uint64_t)complement[n] + r;

      digits[n] = i;
      r = i >> 32;
    }
  }

  void addForward(const BigFixed &num)
  {
    int n;
    uint64_t r = 0;

    for (n = 0; n < LENGTH; n++)
    {
      uint64_t i = (uint64_t)digits[n] + (uint64_t)num.digits[n] + r;

      digits[n] = i;
      r = i >> 32;
    }
  }

  void set(int whole, double fraction)
  {
    memset(digits, 0, sizeof(digits));

    if (whole < 0)
    {
      is_negative = true;
      whole = -whole;
    }

    digits[LENGTH - 1] = whole;
    digits[LENGTH - 2] = 0x100000000ULL * fraction;
  }

  uint32_t digits[LENGTH];
  bool is_negative;
};

#endif

