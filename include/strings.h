/*
 * strings.h - Standard string operations header (POSIX compliant)
 *
 * This header provides case-insensitive string comparison functions and
 * bit manipulation utilities that are not available in standard string.h.
 *
 * All functions are implemented with locale support where appropriate.
 * The case-insensitive comparison functions work correctly only with
 * single-byte character encodings and are not suitable for multibyte
 * locales like UTF-8.
 *
 * Functions are ported from gnulib implementation to ensure POSIX
 * compliance and cross-platform compatibility.
 */

#pragma once

#include <sys/cdefs.h>
#include <string.h>
#include <ctype.h>

/* Find first set bit: returns the position of the least significant 1-bit */
_PCRTIMP int ffs(int i);

/* Case-insensitive string comparison (uses current locale) */
_PCRTIMP int strcasecmp(const char *s1, const char *s2);

/* Case-insensitive string comparison with explicit locale */
_PCRTIMP int strcasecmp_l(const char *s1, const char *s2, _locale_t locale);

/* Bounded case-insensitive string comparison (uses current locale) */
_PCRTIMP int strncasecmp(const char *s1, const char *s2, size_t n);

/* Bounded case-insensitive string comparison with explicit locale */
_PCRTIMP int strncasecmp_l(const char *s1, const char *s2, size_t n, _locale_t locale);
