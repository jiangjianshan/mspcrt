/*
 * sys/stat.h - POSIX Standard File Status Definitions and Permission Macros
 */

#pragma once

#include <../ucrt/sys/stat.h>

/* ===== File Type Macros ===== */
/* Block special file type macro */
#define _S_IFBLK    0060000
/* Block special file type (POSIX) */
#define S_IFBLK     _S_IFBLK
/* FIFO (named pipe) file type (POSIX) */
#define S_IFIFO     _S_IFIFO

/* ===== File Type Test Macros ===== */
/* Test for block special file (POSIX) */
#define S_ISBLK(m)  (((m) & S_IFMT) == S_IFBLK)
/* Test for character special file (POSIX) */
#define S_ISCHR(m)  (((m) & S_IFMT) == S_IFCHR)
/* Test for directory (POSIX) */
#define S_ISDIR(m)  (((m) & S_IFMT) == S_IFDIR)
/* Test for FIFO (named pipe) (POSIX) */
#define S_ISFIFO(m) (((m) & S_IFMT) == S_IFIFO)
/* Test for regular file (POSIX) */
#define S_ISREG(m)  (((m) & S_IFMT) == S_IFREG)

/* ===== User (Owner) Permission Macros ===== */
/* Read permission bit for owner (POSIX: S_IRUSR) */
#define	_S_IRUSR	  _S_IREAD
/* Write permission bit for owner (POSIX: S_IWUSR) */
#define	_S_IWUSR	  _S_IWRITE
/* Execute/search permission bit for owner (POSIX: S_IXUSR) */
#define	_S_IXUSR	  _S_IEXEC
/* Read, write, execute/search by owner (POSIX: S_IRWXU) */
#define	_S_IRWXU	  (_S_IREAD | _S_IWRITE | _S_IEXEC)

/* Read permission bit for owner (POSIX) */
#define	S_IRUSR		  _S_IRUSR
/* Write permission bit for owner (POSIX) */
#define	S_IWUSR		  _S_IWUSR
/* Execute/search permission bit for owner (POSIX) */
#define	S_IXUSR		  _S_IXUSR
/* Read, write, execute/search by owner (POSIX) */
#define	S_IRWXU	    _S_IRWXU

/* ===== Group Permission Macros ===== */

/* Read permission bit for group (POSIX: S_IRGRP) */
#define S_IRGRP     (S_IRUSR >> 3)
/* Write permission bit for group (POSIX: S_IWGRP) */
#define S_IWGRP     (S_IWUSR >> 3)
/* Execute/search permission bit for group (POSIX: S_IXGRP) */
#define S_IXGRP     (S_IXUSR >> 3)
/* Read, write, execute/search by group (POSIX: S_IRWXG) */
#define S_IRWXG     (S_IRWXU >> 3)

/* ===== Others Permission Macros ===== */
/* Read permission bit for others (POSIX: S_IROTH) */
#define S_IROTH     (S_IRGRP >> 3)
/* Write permission bit for others (POSIX: S_IWOTH) */
#define S_IWOTH     (S_IWGRP >> 3)
/* Execute/search permission bit for others (POSIX: S_IXOTH) */
#define S_IXOTH     (S_IXGRP >> 3)
/* Read, write, execute/search by others (POSIX: S_IRWXO) */
#define S_IRWXO     (S_IRWXG >> 3)
