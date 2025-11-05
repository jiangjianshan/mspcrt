/*
 * search.h - POSIX search table functions
 *
 * This header provides POSIX-compliant search table functions including
 * binary search tree operations (tsearch, tfind, tdelete, twalk) and
 * hash table operations (hsearch, hcreate, hdestroy).
 *
 * Implementation notes:
 * - The tree functions implement Algorithm T from Knuth (6.2.2) for
 *   balanced binary search tree operations
 * - Internal node structure (node_t) is exposed when _SEARCH_PRIVATE
 *   is defined for implementation use
 * - All tree functions are thread-unsafe; external synchronization required
 * - Memory management follows POSIX semantics: caller allocates keys/data,
 *   library manages node structures
 *
 * Usage example:
 *   #include <search.h>
 *
 *   int compare(const void *a, const void *b) {
 *       return strcmp((const char *)a, (const char *)b);
 *   }
 *
 *   void action(const void *nodep, VISIT order, int level) {
 *       // Tree traversal action
 *   }
 *
 *   int main() {
 *       void *root = NULL;
 *       tsearch("key", &root, compare);
 *       twalk(root, action);
 *       tdestroy(root, free);
 *   }
 */

#pragma once

#include <../ucrt/search.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

/**
 * ENTRY - Hash table entry structure
 * @key: pointer to the entry's key
 * @data: pointer to the entry's associated data
 *
 * Used by hash table functions (hsearch, etc.) to represent
 * key-data pairs in the hash table.
 */
typedef struct entry {
	char *key;
	void *data;
} ENTRY;

/**
 * ACTION - Operation type for hash table functions
 * @FIND: search for an entry without modification
 * @ENTER: search and create if not found
 *
 * Specifies the action to perform in hsearch() function.
 */
typedef enum {
	FIND,
	ENTER
} ACTION;

/**
 * VISIT - Tree traversal order types
 * @preorder: visit node before its children
 * @postorder: visit node after left child, before right child
 * @endorder: visit node after both children
 * @leaf: visit leaf node (no children)
 *
 * Used by twalk() to indicate the traversal order during tree walking.
 */
typedef enum {
	preorder,
	postorder,
	endorder,
	leaf
} VISIT;

/*
 * Internal node structure for binary search tree implementation.
 * This structure is only visible when _SEARCH_PRIVATE is defined
 * for implementation purposes.
 */
#ifdef _SEARCH_PRIVATE
typedef struct node {
	char         *key;
	struct node  *llink, *rlink;
} node_t;
#endif

/* Tree search functions */

/**
 * tdelete - delete a node from a binary search tree
 * @key: key of the node to delete
 * @rootp: pointer to the root of the tree (updated after deletion)
 * @compar: comparison function for key ordering
 *
 * Searches for and deletes the node matching the given key from the tree.
 * Uses Knuth's Algorithm T for deletion with successor node replacement.
 *
 * Returns: pointer to the parent of the deleted node, or NULL if not found
 */
_PCRTIMP void * tdelete (const void * __restrict, void ** __restrict, int (*)(const void *, const void *));

/**
 * tfind - search for a node in a binary search tree
 * @key: key to search for
 * @rootp: pointer to the root of the tree to search
 * @compar: comparison function for key ordering
 *
 * Searches the tree for a node matching the given key without modifying
 * the tree structure.
 *
 * Returns: pointer to the found node, or NULL if not found
 */
_PCRTIMP void * tfind (const void *, void * const *, int (*)(const void *, const void *));

/**
 * tsearch - search and insert into a binary search tree
 * @key: key to search/insert
 * @rootp: pointer to the root of the tree (updated if root changes)
 * @compar: comparison function for key ordering
 *
 * Searches for the given key in the tree. If found, returns the existing node.
 * If not found, inserts a new node containing the key.
 *
 * Returns: pointer to the found or inserted node, or NULL on allocation failure
 */
_PCRTIMP void * tsearch (const void *, void **, int (*)(const void *, const void *));

/**
 * twalk - traverse a binary search tree in sorted order
 * @root: root of the tree to traverse
 * @action: callback function to execute for each node
 *
 * Performs an in-order traversal of the binary search tree, calling the
 * action callback for each node with the appropriate VISIT order indicator.
 * The traversal follows left-child, node, right-child order.
 */
_PCRTIMP void twalk (const void *, void (*)(const void *, VISIT, int));

/**
 * tdestroy - destroy an entire binary search tree
 * @root: root of the tree to destroy
 * @free_node: function to call for each node's key during destruction
 *
 * Recursively destroys the entire tree, freeing all nodes and calling
 * the provided free_node function for each key. Similar to free() but
 * for entire tree structures.
 */
_PCRTIMP void tdestroy(void *, void (*)(void *));

__END_DECLS
