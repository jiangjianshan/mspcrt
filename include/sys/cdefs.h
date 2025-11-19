/*
 * sys/cdefs.h - compiler and system feature definitions
 */

#pragma once

#ifndef RC_INVOKED
# ifndef _MSC_VER
# error "You need a MSVC or MSVC-like compiler to use the mspcrt headers"
# endif
#endif

#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS   }
#else
# define __BEGIN_DECLS
# define __END_DECLS
#endif

/*
 * Library import/export control
 * _PCRTIMP macro for dynamic library import/export and static library compatibility.
 *
 * Usage scenarios:
 * 1. When building the mspcrt library itself (_PCRT_BUILD defined):
 *    - Symbols are marked for export (__declspec(dllexport)).
 * 2. When linking against the mspcrt DLL (default):
 *    - Symbols are marked for import (__declspec(dllimport)).
 * 3. When linking against the static mspcrt library (_PCRT_STATIC defined):
 *    - The macro expands to nothing, as no import/export attributes are needed.
 *
 * This ensures correct symbol visibility across different linking methods.
 */
#ifndef _PCRTIMP
# if defined(_PCRT_STATIC)
#  define _PCRTIMP
# elif defined(_PCRT_BUILD)
#  define _PCRTIMP __declspec(dllexport)
# else
#  define _PCRTIMP __declspec(dllimport)
# endif
#endif
