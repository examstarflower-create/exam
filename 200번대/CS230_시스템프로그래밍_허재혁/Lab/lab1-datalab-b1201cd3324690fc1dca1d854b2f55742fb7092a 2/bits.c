/* 
 * CS:APP Data Lab [Revised Version]
 * 
 * <Please put your name and userid here>
 * name : Rho Ukjin (노욱진)
 * userid : st20210203
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
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
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 1
 */
int conditional(int x, int y, int z) {
  /* if x is 0 -> 0xFFFFFFFF & y | 0x00000000 & z
             1 -> 0x00000000 & y | 0xFFFFFFFF & z */
  return ((!x) + ~0 & y) | ((!!x) + ~0 & z);
}
/* 
 * LSBFillLeftShift - shift x to the left by n, while filling bit at LSB
 *   Can assume that 0 <= n <= 31
 *   Examples: LSBFillLeftShift(0x87654321,8) = 0x654321ff
 *             LSBFillLeftShift(0x87654300,8) = 0x65430000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int LSBFillLeftShift(int x, int n) {
  /* first, Left shift x with n
     second, if LSB of x is 0 -> +0
             if LSB of x is 1 -> +1111...(n times)  */
  return (x << n) + (~(~0 << n) & ((x << 31) >> 31));
}
    /*
     * hexAlphabetCount - returns count of number of alphabet in hexadecimal
     *   Examples: hexAlphabetCount(0xABCDEF00) = 6
     *             hexAlphabetCount(0x12345600) = 0
     *             hexAlphabetCount(0xABC45600) = 3
     *   Legal ops: ! ~ & ^ | + << >>
     *   Max ops: 70
     *   Rating: 4
     */
    int hexAlphabetCount(int x)
{
    /* for every one byte of int, let x be x0,x1,x2,x3
    if x0 & (x1 | x2) is true, this byte is alphabet */
    int i88 = 0x88 | (0x88 << 8);
    int i44 = 0x44 | (0x44 << 8);
    int i22 = 0x22 | (0x22 << 8);
    int result;

    i88 = i88 | (i88 << 16);
    i44 = i44 | (i44 << 16);
    i22 = i22 | (i22 << 16);

    result = (x & i88) & (((x & i44) << 1) | ((x & i22) << 2));
    return ((result >> 31) & 1) + ((result >> 27) & 1) + ((result >> 23) & 1)
    + ((result >> 19) & 1) + ((result >> 15) & 1) + ((result >> 11) & 1)
    + ((result >> 7) & 1) + ((result >> 3) & 1);
}
    /*
     * patternMatching - return the number of found 4 pattern p in the given number x.
     *   Examples: patternMatching(11, 11) = 1, patternMatching(245, 13) = 1,
     *             patternMatching(170, 15) = 0, patternMatching(23397, 11) = 3
     *   Legal ops: ! ~ & ^ | + << >>
     *   Max ops: 85
     *   Rating: 6
     */
    int patternMatching(int x, int p)
{
    /* p is p1|p2|p3|p4 then make res_p* (matched bit -> 1)
    if the sequence of bits are all 1 then it's a pattern */
    int res_p1 = ~((~(((p >> 3) & 1)+ ~0)) ^ x);
    int res_p2 = ~((~(((p >> 2) & 1) + ~0)) ^ x);
    int res_p3 = ~((~(((p >> 1) & 1) + ~0)) ^ x);
    int res_p4 = ~((~((p & 1) + ~0)) ^ x);
    int i55;
    int i33;
    int i0F;
    int i00FF;
    int iFF;
    int result;
    /* counting # of 1 */ 
    i55 = 0x55 | (0x55 << 8); 
    i33 = 0x33 | (0x33 << 8);
    i0F = 0x0F | (0x0F << 8);
    i00FF = 0xFF | (0xFF << 16);
    iFF = 0xFF | (0xFF << 8);

    i55 = i55 | (i55 << 16);
    i33 = i33 | (i33 << 16);
    i0F = i0F | (i0F << 16);
    
    result = res_p4 & (res_p3 >> 1) & (res_p2 >> 2) & (res_p1 >> 3);
    result = result & ~(~0 << 29);

    result = (result & i55) + ((result >> 1) & i55);
    result = (result & i33) + ((result >> 2) & i33);
    result = (result & i0F) + ((result >> 4) & i0F);
    result = (result & i00FF) + ((result >> 8) & i00FF);
    result = (result & iFF) + ((result >> 16) & iFF);

    return result;
}
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 1
 */
int absVal(int x) {
  /* if x is neg, return !x + 1
             positive, return x + 0 */
  return ((x >> 31) ^ x) + !!(x >> 31);
}
    /*
     * averageOfTwo - calculate floor(average of two integers).
     *   Floor function takes as input a real number,
     *   and gives out the greatest integer less than or equal to x.
     *   Examples: averageOfTwo(1, 2) = 1
     *             averageOfTwo(30, 40) = 35
     *             averageOfTwo(-1, -2) = -2
     *             averageOfTwo(-30, -40) = -35
     *             averageOfTwo(-2147483648, -2147483648) = -2147483648
     *   Legal ops: ! ~ & ^ | + << >>
     *   Max ops: 20
     *   Rating: 2
     */
    int averageOfTwo(int x, int y)
{
    /* x/2 + y/2 + 1(if LSB of x and y are both 1)*/
    return (x >> 1) + (y >> 1) + ((x & 1) & (y & 1));
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
    /* check if x*y < 0. If so, check if the overflow occurred
    by checking MSB changed after subtraction */
    int isxydiff = (x >> 31) ^ (y >> 31);
    int ismsbchanged = (x >> 31) ^ ((x + (~y + 1)) >> 31);
    return !(isxydiff & ismsbchanged);
}
/* 
 * tc2sm - Convert from two's complement to sign-magnitude 
 *   where the MSB is the sign bit
 *   You can assume that x > TMin
 *   Example: tc2sm(-5) = 0x80000005.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int tc2sm(int x) {
  /* Maintain MSB. Add absVal(x) */
  return ((1 << 31) & x) + (((x >> 31) ^ x) + (!!(x >> 31)));
}
/*
 * mulNineoverSixteen - multiply by 9/16 rounding toward 0, avoiding overflow.
 *  Examples: mulNineoverSixteen(22) = 12
 *            mulNineoverSixteen(421) = 236
 *            mulNineoverSixteen(-121) = -68
 *            mulNineoverSixteen(-129) = -72
 *            mulNineoverSixteen(-158733) = -89287
 *            mulNineoverSixteen(0x40000000) = 603979776 (no overflow)
 *            mulNineoverSixteen(0x8F000000) = -1066401792 (no overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 6
 */
int mulNineoverSixteen(int x) {
  /* take quocient and remainder of x when divided by 16
  multiply nine by 9x = (x << 3) + x. when x is neg, -1 if 
  remainder*9 is not 0 */
  int quocient = x >> 4;
  int remainder = x & 0x0F;
  int mulremnine = (remainder << 3) + remainder;
  return ((quocient << 3) + quocient) + (mulremnine >> 4) + 
  ((x >> 31) & (((mulremnine & 0x0F) + 0x0F) >> 4));
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
  /* if exp of uf is 0xFF and frac is not 0, return uf
  else return uf with reversed sign.*/
  if ((uf << 1) > (0xFF << 24)) {
    return uf;
  }
  return uf ^ (1 << 31);
}
    /*
     * float_quarter - Return bit-level equivalent of expression 0.25*f for
     *   floating point argument f.
     *   Both the argument and result are passed as unsigned int's, but
     *   they are to be interpreted as the bit-level representation of
     *   single-precision floating point values.
     *   When argument is NaN, return argument
     *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
     *   Max ops: 30
     *   Rating: 6
     */
    unsigned float_quarter(unsigned uf)
{
  /* for special value, return uf.
  if exp is 0, divide frac with 4 and rounding toward 0
  if exp is 1 or 2, divide 1+frac with 2^(3-exp) and rounding toward 0
  else subtract 2 from exp */
  unsigned s = uf & (1 << 31);
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned frac = uf & ~(0xFF << 24);
  int frac_last = (frac >> 2) & 1;
  int r1 = (frac >> 1) & 1;
  int r2 = frac & 1;
  int p = r1 & (frac_last | r2);

  if (exp == 0xFF) {
    return uf;
  }
  if (exp == 0) {
    return s | ((frac >> 2) + p);
  }
  if (exp <= 2) {
    return s | (((frac | (1 << 23)) >> (3 - exp)) +  p);
  }
  return s | ((exp - 2) << 23) | frac;
}
    /*
     * float_f2i - Return bit-level equivalent of expression (int) f
     *   for floating point argument f.
     *   Argument is passed as unsigned int, but
     *   it is to be interpreted as the bit-level representation of a
     *   single-precision floating point value.
     *   Anything out of range (including NaN and infinity) should return
     *   0x80000000u.
     *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
     *   Max ops: 30
     *   Rating: 8
     */
    int float_f2i(unsigned uf)
{
  /* if exp is larger then 0x9F, return 0x80000000u because of overflow
  if exp is smaller than 0x7F return 0 because of rounding to 0
  else return uf with shifting and sign */
  unsigned s = uf & (1 << 31);
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned frac = uf & ~((1 << 31) | (0xFF << 24));
  int E = exp - 127;
  unsigned result = frac | (1 << 23);

  if (exp >= 0x9F) {
    return 1 << 31;
  }
  if (exp < 0x7E) {
    return 0;
  }
  if (E < 23) {
    result = result >> (23 - E);
  } else {
    result = result << (E - 23);
  }

  if (s) {
    return -result;
  } else {
    return result;
  }
}