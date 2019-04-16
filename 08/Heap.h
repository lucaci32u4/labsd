#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

/* We assume there is a defined primitive type Item. */
typedef struct {
	int prior; // Item priority
	Item data; // Item d
} ItemType;

typedef struct heap {
	long maxHeapSize; // capacity
	long size; // number of elements
	ItemType * elem; // array of elements
} PriQueue, * APriQueue;


PriQueue * makeQueue(int maxHeapSize) {
	PriQueue * queue = (PriQueue *)calloc(1, sizeof(PriQueue));
	queue->maxHeapSize = maxHeapSize;
	queue->elem = (ItemType *)calloc(queue->maxHeapSize, sizeof(ItemType));
	return queue;
}

int getLeftChild(int i) {
	return 2 * i + 1;
}

int getRightChild(int i) {
	return 2 * i + 2;
}

int getParent(int i) {
	return (i - 1) / 2;
}

ItemType getMax(APriQueue h) {
	return h->elem[0];
}

void siftUp(APriQueue h, int index) {
	while (index) {
		ItemType parent = h->elem[getParent(index)];
		if (parent.prior < h->elem[index].prior) {
			/* swap elems */
			h->elem[getParent(index)] = h->elem[index];
			h->elem[index] = parent;
			index = getParent(index);
		} else break;
	}
}


void insert(PriQueue * h, ItemType x) {
	/* ensure size */
	h->size++;
	if (h->size > h->maxHeapSize) {
		h->elem = (ItemType *)realloc(h->elem, (++(h->maxHeapSize)) * sizeof(ItemType));
	}

	/* add element */
	h->elem[h->size - 1] = x;
	siftUp(h, h->size - 1);
}

void siftDown(APriQueue h, int index) {
	while (1) {
		int lastIndex = index;
		if (getLeftChild(index) < h->size) {
			if (h->elem[index].prior < h->elem[getLeftChild(index)].prior) {
				index = getLeftChild(index);
			}
			if (getRightChild(lastIndex) < h->size) {
				if (h->elem[index].prior < h->elem[getRightChild(lastIndex)].prior) {
					index = getRightChild(lastIndex);
				}
			}
		}
		if (lastIndex != index) {
			/* swap */
			ItemType aux = h->elem[lastIndex];
			h->elem[lastIndex] = h->elem[index];
			h->elem[index] = aux;
		} else {
			break;
		}
	}
}

void removeMax(APriQueue h) {
	if (h->size > 0) {
		h->elem[0] = h->elem[h->size - 1];
		h->size--;
		siftDown(h, 0);
	}
}

void freeQueue(APriQueue h) {
	free(h->elem);
	free(h);
}

#endif

