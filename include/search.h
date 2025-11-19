/*
 * search.h - POSIX search table functions
 */

#pragma once

#include <../ucrt/search.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

/* ENTRY - Hash table entry structure */
typedef struct entry {
	char *key;
	void *data;
} ENTRY;

/* ACTION - Operation type for hash table functions */
typedef enum {
	FIND,
	ENTER
} ACTION;

/* VISIT - Tree traversal order types */
typedef enum {
	preorder,
	postorder,
	endorder,
	leaf
} VISIT;

/* Internal node structure for binary search tree implementation. */
#ifdef _SEARCH_PRIVATE
typedef struct node {
	char         *key;
	struct node  *llink, *rlink;
} node_t;
#endif

/* Tree search functions */

/* tdelete - delete a node from a binary search tree */
_PCRTIMP void * tdelete (const void * __restrict, void ** __restrict, int (*)(const void *, const void *));

/* tfind - search for a node in a binary search tree */
_PCRTIMP void * tfind (const void *, void * const *, int (*)(const void *, const void *));

/* tsearch - search and insert into a binary search tree */
_PCRTIMP void * tsearch (const void *, void **, int (*)(const void *, const void *));

/* twalk - traverse a binary search tree in sorted order */
_PCRTIMP void twalk (const void *, void (*)(const void *, VISIT, int));

/* tdestroy - destroy an entire binary search tree */
_PCRTIMP void tdestroy(void *, void (*)(void *));

__END_DECLS
