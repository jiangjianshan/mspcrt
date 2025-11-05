/*
 * sys/time.h - POSIX time types and timer functions
 *
 * WARNING: On Windows platforms, this header must be included AFTER
 *          any Windows socket headers (winsock2.h or winsock.h)
 *          to avoid struct timeval redefinition errors.
 *
 * Important: This header does NOT include Windows-specific headers like
 *            windows.h or winsock2.h to avoid include order dependencies
 *            and namespace pollution. System headers should remain
 *            platform-agnostic.
 *
 * Usage scenarios:
 * 1. If winsock2.h is included first:
 *    #include <winsock2.h>  // defines struct timeval and protection macros
 *    #include <sys/time.h>  // uses existing timeval definition
 *
 * 2. If sys/time.h is included first (RISKY):
 *    #include <sys/time.h>  // defines struct timeval with warnings
 *    #include <winsock2.h>  // will cause redefinition errors!
 *
 * 3. Recommended approach on Windows:
 *    #include <winsock2.h>  // always include Windows headers first
 *    #include <sys/time.h>  // then include POSIX compatibility headers
 */

#pragma once

#include <sys/cdefs.h>
#include <time.h>

/*
 * We avoid including Windows headers directly in system headers to
 * maintain clean separation and prevent include order issues.
 * Instead, we conditionally define timeval only when Windows socket
 * headers haven't been included yet.
 */
#if !defined(_WINSOCK2API_) && !defined(_WINSOCKAPI_)
/*
 * Windows socket headers not included - proceeding with caution.
 * This may lead to redefinition errors if winsock2.h is included later.
 *
 * Note: If your library already uses winsock2.h or winsock.h and you want
 *       to avoid potential redefinition conflicts, you can define
 *       _TIMEVAL_DEFINED in your build options to suppress this definition.
 *       Example: -D_TIMEVAL_DEFINED
 */
#pragma message("WARNING: sys/time.h is being included without prior inclusion of Windows socket headers.")
#pragma message("         This may cause struct timeval redefinition errors if winsock2.h is included later.")
#pragma message("         To avoid this, include winsock2.h or winsock.h BEFORE sys/time.h.")
#pragma message("         Alternatively, define _TIMEVAL_DEFINED in build options to suppress timeval definition.")

/*
 * Define timeval structure for POSIX compatibility.
 * This matches the definition in winsock2.h to ensure binary compatibility.
 */
# ifndef _TIMEVAL_DEFINED
# define _TIMEVAL_DEFINED
struct timeval {
    long tv_sec;   /* seconds */
    long tv_usec;  /* microseconds */
};
# endif

#endif /* !defined(_WINSOCK2API_) && !defined(_WINSOCKAPI_) */

__BEGIN_DECLS

#pragma pack(push,_CRT_PACKING)
/*
 * timezone structure for handling time zone information.
 * Note: This is not part of winsock2.h and is specific to POSIX compatibility.
 */
#ifndef _TIMEZONE_DEFINED
#define _TIMEZONE_DEFINED
struct timezone {
    int tz_minuteswest; /* minutes west of Greenwich */
    int tz_dsttime;     /* type of DST correction to apply */
};
#endif
#pragma pack(pop)

/*
 * gettimeofday - get the current time with microsecond precision
 * @tp: pointer to timeval structure to receive current time
 * @tzp: pointer to timezone structure (obsolete, can be NULL)
 *
 * Returns: 0 on success, -1 on error
 *
 * Note: On Windows, this function provides a POSIX-compatible wrapper
 *       around the native Windows time APIs.
 */
_PCRTIMP int gettimeofday(struct timeval *__restrict tp, void *__restrict tzp);

__END_DECLS
