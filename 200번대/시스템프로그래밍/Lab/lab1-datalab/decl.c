#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TMin INT_MIN
#define TMax INT_MAX

#include "btest.h"
#include "bits.h"

test_rec test_set[] = {
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
 {"conditional", (funct_t) conditional, (funct_t) test_conditional, 3, "! ~ & ^ | << >>", 16, 1,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"LSBFillLeftShift", (funct_t) LSBFillLeftShift, (funct_t) test_LSBFillLeftShift, 2,
    "! ~ & ^ | + << >>", 20, 3,
  {{TMin, TMax},{0,31},{TMin,TMax}}},
{"hexAlphabetCount", (funct_t)hexAlphabetCount, (funct_t)test_hexAlphabetCount, 1, "! ~ & ^ | + << >>", 70, 4, {{TMin, TMax}, {TMin, TMax}, {TMin, TMax}}},
{"patternMatching", (funct_t)patternMatching, (funct_t)test_patternMatching, 2, "! ~ & ^ | + << >>", 85, 6, {{TMin, TMax}, {0, 15}, {TMin, TMax}}},
 {"absVal", (funct_t) absVal, (funct_t) test_absVal, 1, "! ~ & ^ | + << >>", 10, 1,
  {{-TMax, TMax},{TMin,TMax},{TMin,TMax}}},
{"averageOfTwo", (funct_t)averageOfTwo, (funct_t)test_averageOfTwo, 2, "! ~ & ^ | + << >>", 20, 2, {{TMin, TMax}, {TMin, TMax}, {TMin, TMax}}},
 {"subOK", (funct_t) subOK, (funct_t) test_subOK, 2,
    "! ~ & ^ | + << >>", 20, 3,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
 {"tc2sm", (funct_t) tc2sm, (funct_t) test_tc2sm, 1, "! ~ & ^ | + << >>", 15, 3,
  {{TMin+1, TMax},{TMin+1,TMax},{TMin+1,TMax}}},
 {"mulNineoverSixteen", (funct_t) mulNineoverSixteen, (funct_t) test_mulNineoverSixteen, 1,
    "! ~ & ^ | + << >>", 25, 6,
  {{TMin,TMax},{TMin,TMax},{TMin,TMax}}},
 {"float_neg", (funct_t) float_neg, (funct_t) test_float_neg, 1,
    "$", 10, 2,
     {{1, 1},{1,1},{1,1}}},
{"float_quarter", (funct_t)float_quarter, (funct_t)test_float_quarter, 1, "$", 30, 6, {{1, 1}, {1, 1}, {1, 1}}},
{"float_f2i", (funct_t)float_f2i, (funct_t)test_float_f2i, 1, "$", 30, 8, {{1, 1}, {1, 1}, {1, 1}}},
  {"", NULL, NULL, 0, "", 0, 0,
   {{0, 0},{0,0},{0,0}}}
};
