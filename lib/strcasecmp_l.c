/* Ported from gnulib */
/* Case-insensitive string comparison function for unibyte locales.
   Copyright (C) 1998-2025 Free Software Foundation, Inc.

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

#include <strings.h>

#include <ctype.h>
#include <string.h>
#include <limits.h>

int
strcasecmp_l (const char *s1, const char *s2, _locale_t locale)
{
  unsigned char c1, c2;

  if (s1 == s2)
    return 0;

  do
    {
      c1 = _tolower_l ((unsigned char) *s1, locale);
      c2 = _tolower_l ((unsigned char) *s2, locale);

      if (c1 == '\0')
        break;

      ++s1;
      ++s2;
    }
  while (c1 == c2);

  if (UCHAR_MAX <= INT_MAX)
    return c1 - c2;
  else
    /* On machines where 'char' and 'int' are types of the same size, the
       difference of two 'unsigned char' values - including the sign bit -
       doesn't fit in an 'int'.  */
    return (((c1) > (c2)) - ((c1) < (c2)));
}
