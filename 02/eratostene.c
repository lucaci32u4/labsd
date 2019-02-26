#include <stdio.h>
#include <math.h>
#include <stdbool.h>

typedef int T;

#include "SortedList.h"

#define get getNth

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
	SortedList * nats = getNaturals(2, N);
	SortedList * running = NULL;
	insert(&running, 1);
	int p = 1;
	while (!isEmpty(running)) {
		SortedList * ilist = getNaturals(1, (int)length(nats));
		while (!isEmpty(ilist)) {
			int i = get(ilist, 1); deleteOnce(&ilist, i);
			if (p < get(nats, i)) {
				p = get(nats, i);
				if (i == (int)length(nats)) {
					deleteOnce(&running, 1);
				}
				break;
			}
		}
		SortedList * mul = getNaturals(2, N / p);
		while (!isEmpty(mul)) {
			int m = p * get(mul, 1); deleteOnce(&mul, get(mul, 1));
			if (contains(nats, m)) deleteOnce(&nats, m);
		}
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
