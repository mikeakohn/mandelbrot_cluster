#ifndef BIG_FIXED_SLOW_H
#define BIG_FIXED_SLOW_H

#include "BigFixed.h"

class BigFixedSlow : public BigFixed
{
public:
  BigFixedSlow(double value) : BigFixed(value)
  {
  }

  void multiplySlow(BigFixed &num)
  {
    uint32_t answer[ANSWER_LENGTH];
    int n, i, j;
    uint32_t r;

    memset(answer, 0, sizeof(answer));

    uint32_t *digits_in = num.getDigits();

    // For every digit in "num".
    for (n = 0; n < LENGTH; n++)
    {
      // Multiply that digit by every digit in "this".
      for (i = 0; i < LENGTH; i++)
      {
        uint64_t a = (uint64_t)digits_in[n] * (uint64_t)digits[i];

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
};

#endif

