/*
 * libgen.h - POSIX pattern matching functions
 */

#pragma once

#include <sys/cdefs.h>

__BEGIN_DECLS

/* basename - extract the filename component from a path */
_PCRTIMP char *basename(char *);

/* dirname - extract the directory component from a path */
_PCRTIMP char *dirname(char *);

__END_DECLS
