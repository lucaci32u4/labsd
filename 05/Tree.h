#ifndef TREE_H_D
#define TREE_H_D

#include <stdio.h>
#include <stdlib.h>

typedef int Item;

typedef struct Link {
	Item elem;
	struct Link * l;
	struct Link * r;
} TreeNode;


void Init(TreeNode ** t, Item x) {
   (*t) = (TreeNode *)calloc(1, sizeof(TreeNode));
   (*t)->elem = x;
}

void Insert(TreeNode ** t, Item x) {
	if (*t) {
		if (x < (*t)->elem) {
			Insert(&((*t)->l), x);
		}
		if (x > (*t)->elem) {
			Insert(&((*t)->r), x);
		}
	} else Init(t, x);
}

void PrintPostorder(TreeNode * t) {
	if (t) {
		PrintPostorder(t->l);
		PrintPostorder(t->r);
		printf("%d ", t->elem);
	}
}

void PrintPreorder(TreeNode * t) {
	if (t) {
		printf("%d ", t->elem);
		PrintPreorder(t->l);
		PrintPreorder(t->r);
	}
}

void PrintInorder(TreeNode * t) {
	if (t) {
		PrintInorder(t->l);
		printf("%d ", t->elem);
		PrintInorder(t->r);
	}
}

void Free(TreeNode ** t) {
	if (*t) {
		Free(&((*t)->l));
		Free(&((*t)->r));
		free(*t);
	}
}

int Size(TreeNode * t) {
	return (t ? 1 + Size(t->l) + Size(t->r) : 0);
}

int maxDepth(TreeNode * t) {
	if (t) {
		int l = maxDepth(t->l);
		int r = maxDepth(t->r);
		return 1 + (l > r ? l : r);
	} else return 0;
}

#endif // LINKEDSTACK_H_INCLUDED
