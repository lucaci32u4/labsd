#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

/* We assume there is a defined primitive type Item. */
typedef struct {
	int prior; // Item priority
	Item data; // Item d
}ItemType;

typedef struct heap{
	long maxHeapSize; // capacity
	long size; // number of elements
	ItemType *elem; // array of elements
} PriQueue, *APriQueue;


PriQueue* makeQueue(int maxHeapSize){
	//TODO:
	return NULL;
}

int getLeftChild(int i){
	//TODO:
	return 0;
}

int getRightChild(int i) {
	//TODO:
	return 0;
}

int getParent(int i) {
	//TODO:
	return 0;
}

ItemType getMax(APriQueue h) {
	//TODO:
}

void siftUp(APriQueue h, int idx) {
	//TODO:
}


void insert(PriQueue *h, ItemType x) {
	//TODO:
}

void siftDown(APriQueue h, int idx){

	//TODO:
}

void removeMax(APriQueue h) {
	//TODO:
}

void freeQueue(APriQueue h){
	// TODO:
}

#endif

