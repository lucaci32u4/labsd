typedef long Item; // Valorile din BST
#include "BST.h"
#include "List.h"

typedef BSTNode * Item2; // Elementele cozii sunt noduri din arbore
#include "Queue.h"


BSTree * buildTree(Item * array, long len);

// -----------------------------------------------------------------------------

int addLevel(BSTNode * tree, List * list, BSTNode * __local_nil, int level) {
	if (NOTNULL(tree)) {
		if (level) {
			return addLevel(tree->l, list, NIL, level - 1) + addLevel(tree->r, list, NIL, level - 1);
		} else {
			listPushBack(list, tree->elem);
			return 1;
		}
	}
	return 0;
}

List * bstToList(BSTree * tree) {
	List * list = createList();
	int level = 0, progress;
	do {
		progress = addLevel(tree->root->l, list, tree->nil, level++);
	} while (progress);
	return list;
}

void printList(List * list) {
	ListNode * cursor = list->head->next;
	while (cursor != list->head) {
		printf("%ld ", cursor->elem);
		cursor = cursor->next;
	}
}
// -----------------------------------------------------------------------------

int main(void) {
	Item array[] = {5, 3, 2, 4, 7, 6, 8};

	BSTree * tree = buildTree(array, sizeof(array) / sizeof(Item));

	List * list = bstToList(tree);

	printList(list);

	destroyList(list);
	destroyTree(tree);

	return 0;
}

BSTree * buildTree(Item * array, long len) {
	BSTree * newTree = createTree();
	for (int i = 0; i < len; i++) {
		insert(newTree, array[i]);
	}
	return newTree;
}
