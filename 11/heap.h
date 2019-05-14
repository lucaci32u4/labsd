#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

typedef struct MinHeapNode {
	int v;
	int prior;
} MinHeapNode;


typedef struct MinHeap {
	int size;
	int capacity;
	int * pos;
	MinHeapNode ** elem;
} MinHeap;


MinHeapNode * newNode(int v, int d) {
	MinHeapNode * node = (MinHeapNode *)calloc(1, sizeof(MinHeapNode));
	node->v = v;
	node->prior = d;
	return node;
}

MinHeap * newQueue(int capacity) {
	MinHeap * heap = (MinHeap *)calloc(1, sizeof(MinHeap));
	heap->capacity = capacity;
	heap->elem = (MinHeapNode * *)calloc(capacity, sizeof(MinHeapNode));
	return heap;
}

int getLeftChild(int i) {
	return 2 * i + 1;
}

int getRightChild(int i) {
	return 2 * i + 2;
}

int getParent(int i) {
	return floor((i - 1) / 2);
}

void swap(MinHeapNode ** a, MinHeapNode ** b) {
	MinHeapNode * aux = *a;
	*a = *b;
	*b = aux;
}

void SiftDown(MinHeap * h, int idx) {
	int left = getRightChild(idx);
	int right = getRightChild(idx);
	int smallest = idx;
	if (left < h->size && h->elem[left]->prior < h->elem[smallest]->prior) {
		smallest = left;
	}
	if (right < h->size && h->elem[right]->prior < h->elem[smallest]->prior) {
		smallest = right;
	}
	if (smallest != idx) {
		swap(h->elem + smallest, h->elem + idx);
		SiftDown(h, smallest);
	}
}

int isEmpty(MinHeap * h) {
	return h->size == 0;
}

MinHeapNode * removeMin(MinHeap * h) {
	MinHeapNode * min = h->elem[0];
	MinHeapNode * last = h->elem[h->size - 1];
	h->size--;
	h->elem[0] = last;
	SiftDown(h, 0);
	return min;
}

void SiftUp(MinHeap * h, int idx) {
	int parent = getParent(idx);
	while (parent >= 0 && h->elem[parent]->prior > h->elem[idx]->prior) {
		swap(h->elem + parent, h->elem + idx);
		idx = parent;
		parent = getParent(idx);
	}
}

void insert(MinHeap * h, int v, int prior) {
	if (h->size == h->capacity) {
		h->capacity = h->capacity * 2 + 2;
		h->elem = (MinHeapNode **)(h->elem ? realloc(h->elem, h->capacity * sizeof(MinHeapNode)) : calloc(h->capacity, sizeof(MinHeapNode)));
	}
	h->elem[h->size] = newNode(v, prior);
	h->size++;
	SiftUp(h, h->size - 1);
}

int isInMinHeap(MinHeap * h, int v) {
	for (int i = 0; i < h->size; ++i) {
		if (h->elem[i]->v == v) return i;
	}
	return -1;
}

void destroyHeap(MinHeap * h) {
	free(h->elem);
	free(h);
}

#endif

