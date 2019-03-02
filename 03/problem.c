#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 255

typedef char Item;
#include "DoubleLinkedList.h"


void printList(List *list){
	ListNode* iterator = list->first;
	printf("[");
	while(iterator != list->last){
		printf("%c, ", iterator->elem);
		iterator = iterator->next;
	}
	printf("%c]",list->last->elem);
}

void printListReverse(List* list){
	ListNode* iterator = list->last;
	printf("[");
	while(iterator != list->last){
		printf("%c ", iterator->elem);
		iterator = iterator->prev;
	}
	printf("%c]",list->last->elem);
}




int isPalindrome(List* list) {
	if (list->first == list->last) return 1;
	else {
		List l = *list;
		int palindrome = 1;
		int running = 1;
		while (running) {
			if (list->first == list->last) running = 0;
			else if (list->first->elem == list->last->elem) {
				if (list->last->prev == list->first && list->first->next == list->last) running = 0;
				else {
					list->last = list->last->prev;
					list->first = list->first->next;
				}
			} else {
				palindrome = 0;
				running = 0;
			}
		}
		*list = l;
		return palindrome;
	}
}

/* Main Program */
int main(void) {

	int len;
	int inputCount = 0;
	char inputCharacters[256];
	FILE* inputFile = fopen("input","r");



	while(fgets(inputCharacters, MAX_INPUT_LEN, inputFile) != NULL){
			inputCharacters[strcspn(inputCharacters, "\r\n")] = 0;
			len = (int)strlen(inputCharacters);
			if(len == 0) break;

			List *list = createList();
			for(int i = 0; i < len; i++) insertAt(list, inputCharacters[i],i);


			printf("Input%d: ", ++inputCount);
			printf("\"%s\" --- ", inputCharacters);
			printf("List: ");
			printList(list);

			if(isPalindrome(list)) printf(" is a palindrome.");
			else printf(" is NOT a palindorme.");
			printf("\n");

			destroyList(list);
	}

	fclose(inputFile);
	return 0;
}



