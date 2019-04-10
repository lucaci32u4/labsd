
#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <stdlib.h>
#include <stdbool.h>

typedef bool boolean;

typedef struct AVLNode {
	Item elem;
	int height;
	struct AVLNode * l;
	struct AVLNode * r;
	struct AVLNode * p;

} AVLNode;

typedef struct AVLTree {
	long size;
	AVLNode * root;
	AVLNode * nil;

	int (* comp)(Item a, Item b);
} AVLTree;

AVLTree * avlCreateTree(int (* comp)(Item a, Item b)) {
	AVLTree * newTree = (AVLTree *) malloc(sizeof(AVLTree));
	newTree->comp = comp;
	newTree->nil = (AVLNode *) malloc(sizeof(AVLNode));
	newTree->nil->p = newTree->nil->l = newTree->nil->r = newTree->nil;
	newTree->nil->height = 0;
	newTree->root = (AVLNode *) malloc(sizeof(AVLNode));
	newTree->root->p = newTree->root->l = newTree->root->r = newTree->nil;
	newTree->root->height = 0;
	newTree->size = 0;

	return newTree;
}

int avlIsEmpty(AVLTree * tree) {
	return (tree->root->l == tree->nil);
}

AVLNode * avlNewNode(AVLTree * tree) {
	AVLNode * newNode = (AVLNode *) malloc(sizeof(AVLNode));
	newNode->p = newNode->r = newNode->l = tree->nil;
	newNode->height = 1;
	return newNode;
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

void updateHeight(AVLTree * tree, AVLNode * node, int height) {
	if (node != tree->nil) {
		node->height = height;
		updateHeight(tree, node->l, height + 1);
		updateHeight(tree, node->r, height + 1);
	}
}

void avlRightRotate(AVLTree * tree, AVLNode * y) {
	AVLNode * parent = y->p, * x = y->l;

	/* move beta */
	y->l = x->r;
	if (x->r != tree->nil) x->r->p = y;

	/* swap main nodes */
	x->r = y;
	y->p = x;
	x->p = parent;
	if (parent->r == y) parent->r = x;
	if (parent->l == y) parent->l = x;

	updateHeight(tree, tree->root->l, 1);
}

// A utility function to left rotate subtree rooted with x
void avlLeftRotate(AVLTree * tree, AVLNode * x) {
	AVLNode * parent = x->p, * y = x->r;

	/* move beta */
	x->r = y->l;
	if (y->l != tree->nil) y->l->p = x;

	/* swap main nodes */
	y->l = x;
	x->p = y;
	y->p = parent;
	if (parent->r == x) parent->r = y;
	if (parent->l == x) parent->l = y;

	updateHeight(tree, tree->root->l, 1);
}

int avlGetBalance(AVLNode * x) {
	if (x == NULL) return 0;
	else return x->l->height - x->r->height;
}

AVLNode * avlMinimum(AVLTree * tree, AVLNode * x) {
	while (x->l != tree->nil) {
		x = x->l;
	}
	return x;
}

AVLNode * avlMaximum(AVLTree * tree, AVLNode * x) {
	while (x->r != tree->nil) {
		x = x->r;
	}
	return x;
}

AVLNode * AVLInsert(AVLTree * tree, AVLNode * node, Item x) {
	if (node == tree->nil) {
		AVLNode * newNode = avlNewNode(tree);
		newNode->elem = x;
		tree->size++;
		return newNode;
	}
	int res = tree->comp(x, node->elem);
	if (!res) {
		/* throw NullPointerException */
		return NULL;
	}
	if (res < 0) {
		node->l = AVLInsert(tree, node->l, x);
		node->l->p = node;
	}
	if (res > 0) {
		node->r = AVLInsert(tree, node->r, x);
		node->r->p = node;
	}
	node->height = (max(node->l->height, node->r->height)) + 1;
	int balance = avlGetBalance(node);
	res = tree->comp(x, node->l->elem);
	if (balance > 1 && res <= 0) {
		/* Left Left */
		avlRightRotate(tree, node);
		return node->p;
	} else if (balance > 1 && res > 0) {
		/* Left Right */
		avlLeftRotate(tree, node->l);
		avlRightRotate(tree, node);
		return node->p;
	} else if (balance < -1 && res > 0) {
		/* Right Right */
		avlLeftRotate(tree, node);
		return node->p;
	} else if (balance < -1 && res <= 0) {
		/* Right Left */
		avlRightRotate(tree, node->r);
		avlLeftRotate(tree, node);
		return node->p;
	}
	return node;
}


void avlInsert(struct AVLTree * tree, Item elem) {
	tree->root->l = AVLInsert(tree, tree->root->l, elem);
}

void destroyElem(Item elem) {
	free(elem);
}

void avlDeleteNode(AVLTree * tree, AVLNode * node) {
	destroyElem(node->elem);
	free(node);
}

void avlDestroyTreeHelper(AVLTree * tree, AVLNode * x) {
	if (x != tree->nil) {
		avlDestroyTreeHelper(tree, x->l);
		avlDestroyTreeHelper(tree, x->r);
		avlDeleteNode(tree, x);
	}
}

void avlDestroyTree(AVLTree * tree) {
	avlDestroyTreeHelper(tree, tree->root->l);
	free(tree->root);
	free(tree->nil);
	free(tree);
}

#endif /* AVLTREE_H_ */
