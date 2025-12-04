/**
 * unistd.h - standard symbolic constants and types
 */

#ifndef _UNISTD_H
#define _UNISTD_H
#define __UNISTD_H_SOURCED__ 1

#include <sys/cdefs.h>
#include <direct.h>
#include <io.h>
#include <process.h>
#include <stdio.h>
#include <getopt.h>
#include <sys/types.h>

/* Standard file descriptors */
#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

/* File access test macros for access() function */
#define R_OK    4
#define W_OK    2
#define X_OK    1
#define F_OK    0

__BEGIN_DECLS

/* Get login name */
_PCRTIMP char *getlogin (void);

/*
 * MSVC's stdio.h does not define popen and pclose, only _popen and _pclose.
 * Defining them in stdio.h may cause compilation errors with libraries using gnulib
 * due to conflicts with macros defined in stdio.in.h. Therefore, we define them here
 * in unistd.h which is a more appropriate place for MSVC POSIX compatibility.
 */

/* Execute a command and open a pipe to its input/output */
#ifndef popen
static inline FILE* popen(const char* command, const char* mode) {
    return _popen(command, mode);
}
#endif

/* Close a pipe opened by popen */
#ifndef pclose
static inline int pclose(FILE* stream) {
    return _pclose(stream);
}
#endif

__END_DECLS

#undef __UNISTD_H_SOURCED__
#endif /* _UNISTD_H */
