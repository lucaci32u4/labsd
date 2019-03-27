#ifndef BST_H_
#define BST_H_

#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef bool boolean;

#define SUPRESS_NIL_MODE false

/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just assume
  some type T was previously defined.
 */

// -----------------------------------------------------------------------------

/*
 * !!!!ATENTION!!!!
 * 1. This implementation uses two sentinels (dummy nodes) root and nil.
 * 2. The convetion is that we always root the tree at root->l (the left of the root sentinel)
 */

typedef struct BSTNode {
	Item elem;
	struct BSTNode * p; // parent - not really needed, but simplifies implementation.
	struct BSTNode * l; // left child.
	struct BSTNode * r; // right child.
} BSTNode;

typedef struct BSTree {
	long size; // This inintially is 0, and is updated by insert/delete
	BSTNode * root; // The sentinel root (a sentinel not the actual root). The actual root node is root->l !
	BSTNode * nil; // The nil sentinel to avoid checks for NULL
} BSTree;

#define NILDECL BSTNode * __local_nil
#define INITNIL(__null__) NILDECL = __null__;
#define NOTNULL(__val__) ((__val__) != (__local_nil))
#define ISNULL(__val__) ((__val__) == (__local_nil))
#define NIL (__local_nil)

// TODO: Cerinta 1 si 2

BSTree * createTree() {
	BSTree * tree = (BSTree *) calloc(1, sizeof(BSTree));
	tree->root = (BSTNode *) calloc(1, sizeof(BSTNode));
	tree->nil = (BSTNode *) calloc(1, sizeof(BSTNode));
	INITNIL(tree->nil);
#if (!SUPRESS_NIL_MODE)
	tree->nil->l = NIL;
	tree->nil->p = NIL;
	tree->nil->r = NIL;
	tree->root->l = NIL;
	tree->root->p = NIL;
	tree->root->r = NIL;
#endif
	tree->nil->elem = (Item) LONG_MAX;
	tree->root->elem = (Item) LONG_MAX;
	return tree;
}

int isEmpty(BSTree * tree) {
	INITNIL(tree->nil);
	return ISNULL(tree->root->l);
}

boolean __insert(BSTNode * cursor, Item item, NILDECL) {
	BSTNode ** placement = NULL;
	while (!placement) {
		if (item < cursor->elem) {
			if (NOTNULL(cursor->l)) {
				cursor = cursor->l;
			} else {
				placement = &(cursor->l);
			}
		}
		if (item > cursor->elem) {
			if (NOTNULL(cursor->r)) {
				cursor = cursor->r;
			} else {
				placement = &(cursor->r);
			}
		}
		if (item == cursor->elem) {
			return false;
		}
	}
	*placement = (BSTNode *) calloc(1, sizeof(BSTNode));
	(*placement)->elem = item;
	(*placement)->p = cursor;
	(*placement)->l = NIL;
	(*placement)->r = NIL;
	return true;
}

void insert(BSTree * tree, Item elem) {
	tree->size += __insert(tree->root, elem, tree->nil);
}

BSTNode * __search(BSTNode * cursor, Item elem, NILDECL) {
	return (NOTNULL(cursor) ? (cursor->elem == elem ? cursor : (elem <cursor->elem ? __search(cursor->l, elem, NIL) : __search(cursor->r, elem, NIL))) : NULL);
}

BSTNode * search(BSTree * tree, Item elem) {
	return __search(tree->root, elem, tree->nil);
}

BSTNode * __minimum(BSTNode * cursor, NILDECL) {
	if (NOTNULL(cursor)) {
		BSTNode * min = cursor;
		if (NOTNULL(cursor->l)) {
			BSTNode * l = __minimum(cursor->l, NIL);
			if (l->elem < min->elem) min = l;
		}
		if (NOTNULL(cursor->l)) {
			BSTNode * r = __minimum(cursor->r, NIL);
			if (r->elem < min->elem) min = r;
		}
		return min;
	}
	return cursor;
}

BSTNode * minimum(BSTree * tree, BSTNode * cursor) {
	return __minimum(cursor, tree->nil);
}

BSTNode * __maximum(BSTNode * cursor, NILDECL) {
	if (NOTNULL(cursor)) {
		BSTNode * max = cursor;
		if (NOTNULL(cursor->l)) {
			BSTNode * l = __maximum(cursor->l, NIL);
			if (l->elem > max->elem) max = l;
		}
		if (NOTNULL(cursor->l)) {
			BSTNode * r = __maximum(cursor->r, NIL);
			if (r->elem > max->elem) max = r;
		}
		return max;
	}
	return cursor;
}

BSTNode * maximum(BSTree * tree, BSTNode * cursor) {
	return __maximum(cursor, tree->nil);
}

void __destroyTree(BSTNode * cursor,  NILDECL) {
	if (NOTNULL(cursor)) {
		__destroyTree(cursor->l, NIL);
		__destroyTree(cursor->r, NIL);
		free(cursor);
	}
}

void destroyTree(BSTree * tree) {
	__destroyTree(tree->root->l, tree->nil);
	free(tree->root);
	free(tree->nil);
	free(tree);
}

BSTNode * __succesor(BSTree * tree, BSTNode * cursor, Item val) {
	INITNIL(tree->nil);
	if (NOTNULL(cursor)) {
		BSTNode * min = NULL, * l = NULL, * r = NULL;
		Item valx = (Item) LONG_MAX;
		if (NOTNULL(cursor->l)) l = __succesor(tree, cursor->l, val);
		if (NOTNULL(cursor->l)) r = __succesor(tree, cursor->r, val);
		if (cursor->elem > val) {
			min = cursor;
			valx = cursor->elem;
		}
		if (min) {
			if (l) {
				if (l->elem > val && l->elem < valx) {
					min = l;
					valx = l->elem;
				}
			}
		} else {
			if (l) {
				if (l->elem > val) {
					min = l;
					valx = l->elem;
				}
			}
		}
		if (min) {
			if (r) {
				if (r->elem > val && r->elem < valx) { min = r; }
			}
		} else {
			if (r) {
				if (r->elem > val) { min = r; }
			}
		}
		return min;
	}
	return NULL;
}

BSTNode * successor(BSTree * tree, BSTNode * cursor) {
	return __succesor(tree, tree->root->l, cursor->elem);
}

BSTNode * __predecesor(BSTree * tree, BSTNode * cursor, Item val) {
	INITNIL(tree->nil);
	if (NOTNULL(cursor)) {
		BSTNode * min = NULL, * l = NULL, * r = NULL;
		Item valx = (Item) LONG_MAX;
		if (NOTNULL(cursor->l)) l = __predecesor(tree, cursor->l, val);
		if (NOTNULL(cursor->l)) r = __predecesor(tree, cursor->r, val);
		if (cursor->elem < val) {
			min = cursor;
			valx = cursor->elem;
		}
		if (min) {
			if (l) {
				if (l->elem < val && l->elem > valx) {
					min = l;
					valx = l->elem;
				}
			}
		} else {
			if (l) {
				if (l->elem < val) {
					min = l;
					valx = l->elem;
				}
			}
		}
		if (min) {
			if (r) {
				if (r->elem < val && r->elem > valx) { min = r; }
			}
		} else {
			if (r) {
				if (r->elem < val) { min = r; }
			}
		}
		return min;
	}
	return NULL;
}

BSTNode * predecessor(BSTree * tree, BSTNode * cursor) {
	return __predecesor(tree, tree->root->l, cursor->elem);
}

void delete(BSTree * tree, Item elem) {
	BSTNode * z; // node to be deleted
	BSTNode * y; // Node that is spliced out
	BSTNode * x; // The child of the sliced out node
	if ((z = search(tree, elem)) == tree->nil)
		return;
	y = ((z->l == tree->nil) || (z->r == tree->nil)) ? z : successor(tree, z);
	x = (y->l == tree->nil) ? y->r : y->l;
	if (tree->root == (x->p = y->p))
		tree->root->l = x;
	else if (y == y->p->l)
		y->p->l = x;
	else
		y->p->r = x;
	if (y != z) {
		y->l = z->l;
		y->r = z->r;
		y->p = z->p;
		z->l->p = z->r->p = y;
		if (z == z->p->l) z->p->l = y;
		else z->p->r = y;
		free(z);
	} else {
		free(y);
	}

	tree->size--;
}

#endif /* BST_H_ */

