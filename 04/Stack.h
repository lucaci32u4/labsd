#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>



typedef struct StackNode{
	Item elem;
	struct StackNode *next;
}StackNode;

typedef StackNode TCelSt; // Redenumirea unui nod la notatiile din curs 
typedef StackNode *ACelSt; // Redenumirea unui pointer la nod la notatiile din curs

typedef struct Stack{
	StackNode* head;  // Varful stivei
	long size; // Numarul de elemente din stiva
}Stack;

typedef Stack TStiva; // Redenumirea stivei la notatiile din curs
typedef Stack *ASt;//  // Redenumirea unui pointer la stiva la notatiile din curs

Stack* createStack(void){
	// TODO: Cerinta 1
	return NULL;
}

int isStackEmpty(Stack* stack){
	// TODO: Cerinta 1
}

void push(Stack *stack, Item elem){
	// TODO: Cerinta 1
}

Item top(Stack *stack){	
	// TODO: Cerinta 1
} 

void pop(Stack *stack){
	// TODO: Cerinta 1
}

void destroyStack(Stack *stack){
	// TODO: Cerinta 1
}

#endif 
