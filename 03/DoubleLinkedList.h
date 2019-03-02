#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_
#include <stdlib.h>

typedef struct ListNode {
	Item elem;
	struct ListNode* next;
	struct ListNode* prev;
} ListNode;

typedef struct List {
	ListNode* first;
	ListNode* last;
} List;


List * createList() {
	return (List *)calloc(1, sizeof(List));
}

int isEmpty(List * list) {
	if ((list->first == NULL) ==  (list->last == NULL)) {
		return list->first == NULL;
	} else {
		fprintf(stderr, "Malformed list at %p\n", list);
		return 1;
	}
}

int contains(List * list, Item elem) {
	if (list->first) {
		if (list->first->elem == elem) {
			return 1;
		} else {
			ListNode * next = list->first;
			list->first = next->next;
			int exists = contains(list, elem);
			list->first = next;
			return exists;
		}
	} else {
		return 0;
	}
}

void insertAt(List * list, Item elem, int pos) {
	if(list && pos >= 0) {
		if (list->first && pos) {
			ListNode * next = list->first;
			list->first = next->next;
			insertAt(list, elem, pos - 1);
			list->first = next;
		} else {
			if (pos == 0) {
				ListNode * node = (ListNode *)calloc(1, sizeof(ListNode));
				node->elem = elem;
				if (!list->last) {
					list->last = node;
				} else if (!list->first) {
					node->prev = list->last;
					list->last = node;
					if (node->prev) node->prev->next = node;
					if (node->next) node->next->prev = node;
				} else {
					node->prev = list->first->prev;
					node->next = list->first;
					if (node->prev) node->prev->next = node;
					if (node->next) node->next->prev = node;
				}
				list->first = node;
			} // else nothing
		}
	}
}

void deleteOnce(List * list, Item elem) {
	if (list) {
		if (list->first) {
			if (list->first->elem == elem) {
				if (list->first == list->last) list->last = list->first->prev;
				if (list->first->prev) list->first->prev->next = list->first->next;
				if (list->first->next) list->first->next->prev = list->first->prev;
				ListNode * orphan = list->first;
				list->first = list->first->next;
				free(orphan);
			} else {
				ListNode * next = list->first;
				list->first = next->next;
				deleteOnce(list, elem);
				list->first = next;
			}
		}
	}
}

int length(List * list) {
	if (list) {
		if (list->first) {
			ListNode * next = list->first;
			list->first = next->next;
			int exists = 1 + length(list);
			list->first = next;
			return exists;
		}
		return 0;
	}
	return 0;
}

void destroyList(List * list) {
	if (list) {
		ListNode * node = list->first;
		while (node) {
			ListNode * current = node;
			node = node->next;
			free(current);
		}
		free(list);
	}
}

#endif
