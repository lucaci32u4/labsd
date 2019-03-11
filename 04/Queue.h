#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode {
	Item elem;
	struct QueueNode * next;
} QueueNode;

typedef struct Queue {
	QueueNode * front;
	QueueNode * rear;
	long size;
} Queue;

Queue * createQueue(void) {
	return (Queue *)calloc(1, sizeof(Queue));
}

int isQueueEmpty(Queue * q) {
	return (q->front == 0 || q->rear == 0);
}

void enqueue(Queue * q, Item elem) {
	QueueNode * queueNode = (QueueNode *)calloc(1, sizeof(QueueNode));
	queueNode->next = NULL;
	queueNode->elem = elem;
	if (!q->rear) {
		q->rear = queueNode;
		q->front = queueNode;
	} else {
		q->rear->next = queueNode;
		q->rear = queueNode;
	}
	q->size++;
}

Item front(Queue * q) {
	return q->front->elem;
}

void dequeue(Queue * q) {
	if (q->rear == q->front) {
		free(q->front);
		q->rear = NULL;
		q->front = NULL;
	} else {
		QueueNode * orphan = q->front;
		q->front = q->front->next;
		free(orphan);
	}
	q->size--;
}

void destroyQueue(Queue * q) {
	while (!isQueueEmpty(q)) {
		dequeue(q);
	}
	free(q);
}

#endif
