/*
 * sys/cdefs.h - compiler and system feature definitions
 *
 * Important: This header provides compiler-specific macros and definitions
 *            required by other mspcrt (MSVC Posix C Runtime) headers.
 *            It is automatically included by system headers and typically
 *            should not be included directly by application code.
 *
 * Platform Requirements:
 * - This implementation is specifically designed for MSVC or MSVC-compatible
 *   compilers (e.g., clang-cl) targeting Windows.
 * - Usage with other compilers (like GCC or Clang in non-MSVC mode) will
 *   trigger a compilation error.
 */

#pragma once

/*
 * Compiler compatibility check.
 * The mspcrt headers rely on MSVC-specific extensions and behavior.
 * This check ensures the compiler is compatible to prevent subtle errors.
 */
#ifndef RC_INVOKED
# ifndef _MSC_VER
# error "You need a MSVC or MSVC-like compiler to use the mspcrt headers"
# endif
#endif

/*
 * C++ linkage support
 * C++ needs to know that types and declarations are C, not C++.
 * These macros ensure C-language linkage for symbols declared within them,
 * enabling proper linking from C++ code.
 */
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
