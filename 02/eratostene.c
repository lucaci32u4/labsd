#include <stdio.h>
#include <math.h>
#include <stdbool.h>

typedef int T;

#include "SortedList.h"

SortedList *getNaturals(int A, int B) {
	SortedList *nats;
	int i;
	init(&nats);
	for (i = A; i <= B; i++) {
		insert(&nats, i);
	}
	return nats;
}

SortedList *getPrimes(int N) {
	SortedList * nats = getNaturals(1, N);
	SortedList * upcounter = getNaturals(1, N);
	SortedList * dels = NULL;
	while (!isEmpty(upcounter)) {
		int i = getNth(upcounter, 1);
		int current = getNth(nats, i);
		bool prime = true;
		deleteOnce(&upcounter, i);
		SortedList * divs = getNaturals(2, current / 2);
		while (!isEmpty(divs)) {
			int div = getNth(divs, 1);
			deleteOnce(&divs, div);
			if (current % div == 0) {
				prime = false;
			}
		}
		if (!prime) {
			insert(&dels, current);
		}
	}
	while (!isEmpty(dels)) {
		deleteOnce(&nats, getNth(dels, 1));
		deleteOnce(&dels, getNth(dels, 1));
	}
	return nats;
}

void printInts(SortedList *list) {
	while (!isEmpty(list)) {
		printf("%d ", list->value);
		list = list->next;
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	printInts(getPrimes(100));
	return 0;
}
