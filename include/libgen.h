/*
 * libgen.h - POSIX pattern matching functions
 *
 * Important: This header provides POSIX-compatible implementations of
 *            dirname() and basename() functions with full Windows path support.
 *
 * Windows Path Handling Notes:
 * - Supports both DOS drive letters (C:\) and UNC paths (\\host\share)
 * - Handles both forward slashes (/) and backslashes (\) as directory separators
 * - Properly handles DBCS (Double-Byte Character Set) code pages for international paths
 * - Maintains POSIX semantics while accommodating Windows path conventions
 *
 * Path Processing Logic:
 * 1. UNC paths (\\host\share\path): prefix_end points after share name
 * 2. Drive letters (C:\path): prefix_end points after colon
 * 3. Relative paths: treated according to POSIX rules with Windows extensions
 *
 * Memory Management:
 * - dirname() may modify the input string in place for efficiency
 * - In edge cases, dirname() may allocate static storage (caller should not free)
 * - basename() typically returns pointers into the original input string
 *
 * Thread Safety:
 * - basename() is thread-safe when given different input buffers
 * - dirname() uses static storage in rare edge cases (not fully thread-safe)
 *
 * Examples:
 *   Path                    dirname()        basename()
 *   --------                ---------        ----------
 *   "" or NULL              "."              "."
 *   "usr"                   "."              "usr"
 *   "C:\usr\lib"            "C:\usr"         "lib"
 *   "\\host\usr\lib"        "\\host\usr"     "lib"
 */

#pragma once

#include <sys/cdefs.h>

__BEGIN_DECLS

/**
 * basename - extract the filename component from a path
 * @path: path string (may be modified by the function)
 *
 * Returns: pointer to the filename component within the path
 *
 * Behavior:
 * - Returns "." for NULL, empty string, or paths with no filename component
 * - Returns "\" for paths containing only directory separators (Windows-specific)
 * - For UNC paths, returns the component after the share name
 * - For drive-relative paths (C:file), returns the filename after the drive prefix
 * - Handles trailing directory separators correctly (trailing slashes are ignored)
 */
_PCRTIMP char *basename(char *);

/**
 * dirname - extract the directory component from a path
 * @path: path string (may be modified by the function)
 *
 * Returns: pointer to the directory path (may be static storage in edge cases)
 *
 * Behavior:
 * - Returns "." for NULL, empty string, or relative paths without directory components
 * - Returns "\" for absolute paths without additional directory components
 * - For drive letters, returns "C:\" for absolute paths, "C:." for relative paths
 * - For UNC paths, returns the full UNC prefix including host and share names
 * - May modify the input string by inserting null terminators
 * - In rare cases with insufficient buffer space, may return a pointer to static storage
 */
_PCRTIMP char *dirname(char *);

__END_DECLS
