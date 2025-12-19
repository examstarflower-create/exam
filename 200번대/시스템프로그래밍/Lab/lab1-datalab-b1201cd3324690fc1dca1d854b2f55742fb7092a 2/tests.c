/* Testing Code */

#include <limits.h>
#include <math.h>

/* Routines used by floation point test code */

/* Convert from bit level representation to floating point number */
float u2f(unsigned u) {
  union {
    unsigned u;
    float f;
  } a;
  a.u = u;
  return a.f;
}

/* Convert from floating point number to bit-level representation */
unsigned f2u(float f) {
  union {
    unsigned u;
    float f;
  } a;
  a.f = f;
  return a.u;
}

/* Copyright (C) 1991-2020 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
int test_conditional(int x, int y, int z)
{
  return x?y:z;
}
int test_LSBFillLeftShift(int x, int n) {
    int zmask = (!!(x << 31)) ? 0x1 : 0x0;
    int left = x << n;
    for (int idx = 0; idx < n; idx++) {
        left |= zmask << idx;
    }
    return left;
}
int test_hexAlphabetCount(int x)
{
    int counter = 0;
    char buff[9];
    sprintf(buff, "%08x", x);
    for (int idx = 0; idx < 8; idx++)
    {
        if ((buff[idx] == 'a') | (buff[idx] == 'b') | ((buff[idx]) == 'c') |
            (buff[idx] == 'd') | (buff[idx] == 'e') | ((buff[idx]) == 'f'))
            counter++;
    }
    return counter;
}
int test_patternMatching(int x, int p)
{
    int i;
    int count = 0;
    for (i = 0; i < 29; i++)
    {
        if (((x >> i) & 0xF) == p)
            count++;
    }
    return count;
}
int test_absVal(int x) {
  return (x < 0) ? -x : x;
}
int test_averageOfTwo(int x, int y)
{
    long long xx = x;
    long long yy = y;
    return xx + yy < 0 ? ((xx + yy) % 2 ? (xx + yy) / 2 - 1 : (xx + yy) / 2) : (xx + yy) / 2;
}
int test_subOK(int x, int y)
{
  long long ldiff = (long long) x - y;
  return ldiff == (int) ldiff;
}
int test_tc2sm(int x) {
  int sign = x < 0;
  int mag = x < 0 ? -x : x;
  return (sign << 31) | mag;
}
int test_mulNineoverSixteen(int x)
{
 return (int)(((long long int)x * 9) / 16);
}
unsigned test_float_neg(unsigned uf) {
    float f = u2f(uf);
    float nf = -f;
    if (isnan(f))
 return uf;
    else
 return f2u(nf);
}
unsigned test_float_quarter(unsigned uf)
{
    float f = u2f(uf);
    float hf = 0.25 * f;
    if (isnan(f))
        return uf;
    else
        return f2u(hf);
}
int test_float_f2i(unsigned uf)
{
  float f = u2f(uf);
  int x = (int)f;
  return x;
}
