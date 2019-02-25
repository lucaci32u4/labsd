#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <stdlib.h>
#include <assert.h>

/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------

typedef T Type;

typedef struct tag_SortedList {
	Type value;
	struct tag_SortedList *next;
} SortedList;

void init(SortedList ** list) {
	*list = NULL;
}

int isEmpty(SortedList * list) {
	return list == NULL;
}

int contains(SortedList * list, Type element) {
	if (list) {
		if (list->value == element) {
			return 1;
		} else return contains(list->next, element);
	} else return 0;
}

void insert(SortedList ** list, Type element) {
	SortedList * el = (SortedList *)calloc(1, sizeof(SortedList));
	el->value = element;
	if (*list) {
		if (element < (*list)->value) {
			el->next = *list;
			*list = el;
		} else {
			SortedList *cursor = *list;
			while (cursor) {
				char ins = 0;
				if (cursor->next) {
					if (cursor->next->value > element) ins = 1;
				} else ins = 1;
				if (ins) {
					el->next = cursor->next;
					cursor->next = el;
					break;
				}
				cursor = cursor->next;
			}
		}
	} else {
		*list = el;
	}
}

void deleteOnce(SortedList ** list, Type element) {
	if (*list) {
		SortedList * cursor = *list;
		if (cursor->value == element) {
			*list = cursor->next;
			free(cursor);
		} else {
			while (cursor->next) {
				if (cursor->next->value == element) {
					SortedList * orphan = cursor->next;
					cursor->next = cursor->next->next;
					free(orphan);
					break;
				}
				cursor = cursor->next;
			}
		}
	}
}

long length(SortedList * list) {
	return (list ? 1 + length(list->next) : 0);
}

Type getNth(SortedList * list, long n) {
	return (n == 1 ? list->value : getNth(list->next, n - 1));
}

void freeSortedList(SortedList ** list) {
	if (*list) {
		freeSortedList(&((*list)->next));
		free(*list);
		*list = NULL;
	}
}

#endif
