/* Ported from gnulib */
/* ffs.c -- find the first set bit in a word.
   Copyright (C) 2011-2025 Free Software Foundation, Inc.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by Eric Blake.  */

/* Specification.  */
#include <strings.h>

#include <limits.h>

#if defined _MSC_VER && !(__clang_major__ >= 4)
# include <intrin.h>
#endif

int
ffs (int i)
{
  /* _BitScanForward
     <https://docs.microsoft.com/en-us/cpp/intrinsics/bitscanforward-bitscanforward64> */
  unsigned long bit;
  if (_BitScanForward (&bit, i))
    return bit + 1;
  else
    return 0;
}
