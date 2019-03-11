#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>



typedef struct StackNode {
	Item elem;
	struct StackNode * next;
} StackNode;

typedef struct Stack {
	StackNode * head;
	long size;
} Stack;

Stack * createStack() {
	return (Stack *)calloc(1, sizeof(Stack));
}

int isStackEmpty(Stack * stack) {
	return stack->head == NULL;
}

void push(Stack * stack, Item elem) {
	StackNode * stackNode = (StackNode *)calloc(1, sizeof(StackNode));
	stackNode->next = stack->head;
	stackNode->elem = elem;
	stack->head = stackNode;
	stack->size++;
}

Item top(Stack * stack) {
	return stack->head->elem;
}

void pop(Stack * stack) {
	if (stack->head) {
		StackNode *orphan = stack->head;
		stack->head = orphan->next;
		stack->size--;
		free(orphan);
	}
}

void destroyStack(Stack * stack) {
	while (stack->head) {
		pop(stack);
	}
	free(stack);
}

#endif 
