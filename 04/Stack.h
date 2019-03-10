#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>



typedef struct StackNode {
	Item elem;
	struct StackNode * next;
} StackNode;

//typedef StackNode TCelSt;
//typedef StackNode *ACelSt;

typedef struct Stack {
	StackNode * head;
	long size;
} Stack;

//typedef Stack TStiva;
//typedef Stack *ASt;

Stack * createStack() {
	// TODO: Cerinta 1
	return NULL;
}

int isStackEmpty(Stack * stack) {
	// TODO: Cerinta 1
}

void push(Stack * stack, Item elem) {
	// TODO: Cerinta 1
}

Item top(Stack * stack) {
	// TODO: Cerinta 1
}

void pop(Stack * stack) {
	// TODO: Cerinta 1
}

void destroyStack(Stack * stack) {
	// TODO: Cerinta 1
}

#endif 
