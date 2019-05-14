#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"

#define INF INT_MAX / 4

typedef int TCost;

typedef struct node {
	int v;
	TCost c;
	struct node * next;
} TNode, * ATNode;

typedef struct {
	int nn;
	ATNode * adl;
} TGraphL;


void alloc_list(TGraphL * G, int n) {
	int i;
	G->nn = n;
	G->adl = (ATNode *) malloc((n + 1) * sizeof(ATNode));
	for (i = 0; i < n; i++)
		G->adl[i] = NULL;

}

void free_list(TGraphL * G) {
	int i;
	ATNode it;
	for (i = 1; i < G->nn; i++) {
		it = G->adl[i];
		while (it != NULL) {
			ATNode aux = it;
			it = it->next;
			free(aux);
		}
		G->adl[i] = NULL;
	}
	G->nn = 0;
}

void insert_edge_list(TGraphL * G, int v1, int v2, int c) {
	TNode * t;
	t = (ATNode) malloc(sizeof(TNode));
	t->v = v2;
	t->c = c;
	t->next = G->adl[v1];
	G->adl[v1] = t;
	t = (ATNode) malloc(sizeof(TNode));
	t->v = v1;
	t->c = c;
	t->next = G->adl[v2];
	G->adl[v2] = t;
}

/*
void dijkstra(TGraphL g, int s) {
	MinHeap * heap = newQueue(g.nn);
	for (int i = 0; i < g.nn; ++i) {
		insert(heap, i, i == s ? 0 : INF);
	}
	while (!isEmpty(heap)) {
		MinHeapNode * u = removeMin(heap);
		int index = u->v;
		//printf("%d | %d\n", u->v, u->prior);
		for (struct node * cursor = g.adl[index]; cursor; cursor = cursor->next) {
			int l = isInMinHeap(heap, cursor->v);
			if (l != -1) {
				if (heap->elem[l]->prior > cursor->c + u->prior) {
					heap->elem[l]->prior = cursor->c + u->prior;
					printf("%d | %d\n", heap->elem[l]->v, heap->elem[l]->prior);
					SiftUp(heap, l);
				}
			}
		}
		free(u);
	}
}*/

void dijkstra(TGraphL g, int s) {
	int * dist = (int *)calloc(g.nn, sizeof(int));
	int * marked = (int *)calloc(g.nn, sizeof(int));
	int markCounter = 0;
	for (int i = 0; i < g.nn; ++i) {
		dist[i] = (i == s ? 0 : INF);
	}
	while (markCounter != g.nn) {
		int index = -1;
		for (int i = 0; i < g.nn; ++i) {
			if (!marked[i]) {
				if (index == -1) index = i;
				else if (dist[index] > dist[i]) index = i;
			}
		}
		printf("%d | %d\n", index, dist[index]);
		marked[index] = 1;
		markCounter++;
		for (struct node * cursor = g.adl[index]; cursor; cursor = cursor->next) {
			if (!marked[cursor->v]) {
				if (dist[cursor->v] > cursor->c + dist[index]) {
					dist[cursor->v] = cursor->c + dist[index];
				}
			}
		}
	}
	free(dist);
	free(marked);
}

void Prim(TGraphL g) {
	int * tree = (int *)calloc(g.nn, sizeof(int));
	int * dist = (int *)calloc(g.nn, sizeof(int));
	int * marked = (int *)calloc(g.nn, sizeof(int));
	for (int i = 0; i < g.nn; ++i) {
		dist[i] = INF;
	}
	dist[0] = 0; tree[0] = -1;
	for (int count = 0; count < g.nn - 1; ++count) {
		int index = -1;
		for (int i = 0; i < g.nn; ++i) {
			if (!marked[i]) {
				if (index == -1) index = i;
				else if (dist[index] > dist[i]) index = i;
			}
		}
		marked[index] = 1;
		for (int v = 0; v < g.nn; ++v) {
			int uvd = 0;
			for (struct node * cursor = g.adl[index]; cursor; cursor = cursor->next) {
				if (cursor->v == v) {
					uvd = cursor->c;
				}
			}
			if (uvd && !marked[v] && uvd < dist[v]) {
				tree[v] = index;
				dist[v] = uvd;
			}
		}
	}
	for (int i = 1; i < g.nn; ++i) {
		printf("%d ~ %d\n", tree[i], i);
	}
}


int main() {
	int i, v1, v2, c;
	int V, E;
	TGraphL G;
	ATNode t;
	freopen("graph.in", "r", stdin);
	scanf("%d %d", &V, &E);
	alloc_list(&G, V);

	for (i = 1; i <= E; i++) {
		scanf("%d %d %d", &v1, &v2, &c);
		insert_edge_list(&G, v1, v2, c);
	}

	for (i = 0; i < G.nn; i++) {
		printf("%d : ", i);
		for (t = G.adl[i]; t != NULL; t = t->next)
			printf("%d ", t->v);
		printf("\n");
	}
	printf("\n");
	dijkstra(G, 0);
	printf("\n");

	Prim(G);

	return 0;
}
