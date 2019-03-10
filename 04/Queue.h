#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode{
	Item elem;
	struct QueueNode *next;
}QueueNode;

typedef QueueNode TcelQ;
typedef QueueNode *ACelQ;

typedef struct Queue{
	QueueNode *front;
	QueueNode *rear;
	long size;
}Queue;

typedef Queue TCoada;
typedef Queue *AQ;


Queue* createQueue(void){
	// TODO: Cerinta 2
	return NULL;
} 

int isQueueEmpty(Queue *q){
	// TODO: Cerinta 2
	return 0;
}

void enqueue(Queue *q, Item elem){
	// TODO: Cerinta 2
}

Item front(Queue* q){
	// TODO: Cerinta 2
}

void dequeue(Queue* q){
	// TODO: Cerinta 2

}

void destroyQueue(Queue *q){
	// TODO: Cerinta 2
}

#endif
