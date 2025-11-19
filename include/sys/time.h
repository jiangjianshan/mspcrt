/*
 * sys/time.h - POSIX time types and timer functions
 */

#pragma once

#include <sys/cdefs.h>
#include <sys/timeb.h>
#include <time.h>

__BEGIN_DECLS

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

/* gettimeofday - get the current time with microsecond precision */
_PCRTIMP int gettimeofday(struct timeval *__restrict, void *__restrict);

__END_DECLS
