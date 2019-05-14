#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#include "Util.h"
#include "Graph.h"

typedef bool boolean;

TGraphL * createGraphAdjList(int numberOfNodes) {
	TGraphL * graph = (TGraphL *) calloc(1, sizeof(TGraphL));
	graph->nn = numberOfNodes;
	graph->adl = (ATNode *) calloc(numberOfNodes, sizeof(ATNode));
	return graph;
}

void addEdgeList(TGraphL * graph, int v1, int v2) {
	TNode * one = (TNode *) calloc(1, sizeof(TNode));
	TNode * two = (TNode *) calloc(1, sizeof(TNode));
	one->v = v2;
	two->v = v1;
	one->c = 1;
	two->c = 1;
	for (int i = 0; i < graph->nn; ++i) {
		if (i == v1) {
			one->next = graph->adl[i];
			graph->adl[i] = one;
		}
		if (i == v2) {
			two->next = graph->adl[i];
			graph->adl[i] = two;
		}
	}
}

List * dfsIterative(TGraphL * graph, int s) {
	Stack * stack = createStack();
	List * path = createList();
	boolean * visited = (boolean *) calloc(graph->nn, sizeof(boolean));
	for (push(stack, s); !isStackEmpty(stack);) {
		int index = top(stack);
		pop(stack);
		for (TNode * cursor = graph->adl[index]; cursor; cursor = cursor->next) {
			if (!visited[cursor->v]) push(stack, cursor->v);
		}
		enqueue(path, index);
		visited[index] = true;
	}
	destroyStack(stack);
	free(visited);
	return path;
}

void dfsRecHelper(TGraphL * graph, boolean * visited, List * path, int s) {
	if (!visited[s]) {
		visited[s] = true;
		enqueue(path, s);
		for (TNode * cursor = graph->adl[s]; cursor; cursor = cursor->next) {
			dfsRecHelper(graph, visited, path, cursor->v);
		}
	}
}

List * dfsRecursive(TGraphL * graph, int s) {
	List * path = createList();
	boolean * visited = (boolean *) calloc(graph->nn, sizeof(boolean));
	dfsRecHelper(graph, visited, path, s);
	free(visited);
	return path;
}

List * bfs(TGraphL * graph, int s) {
	boolean * visited = (boolean *) calloc(graph->nn, sizeof(boolean));
	Queue * queue = createQueue();
	List * path = createList();
	for (enqueue(queue, s); !isQueueEmpty(queue);) {
		int index = front(queue);
		dequeue(queue);
		enqueue(path, index);
		visited[index] = true;
		for (TNode * cursor = graph->adl[index]; cursor; cursor = cursor->next) {
			if (!visited[cursor->v]) {
				visited[cursor->v] = true;
				enqueue(queue, cursor->v);
			}
		}
	}
	destroyQueue(queue);
	free(visited);
	return path;
}


void destroyGraphAdjList(TGraphL * graph) {
	for (int i = 0; i < graph->nn; ++i) {
		for (TNode * cursor = graph->adl[i]; cursor;) {
			TNode * next = cursor->next;
			free(cursor);
			cursor = next;
		}
	}
	free(graph->adl);
	free(graph);
}

void removeEdgeList(TGraphL * graph, int v1, int v2) {
	TNode * it = graph->adl[v1];
	TNode * prev = NULL;
	while (it != NULL && it->v != v2) {
		prev = it;
		it = it->next;
	}

	if (it == NULL)return;

	if (prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v1] = it->next;
	free(it);

	it = graph->adl[v2];
	prev = NULL;
	while (it != NULL && it->v != v1) {
		prev = it;
		it = it->next;
	}
	if (it == NULL) return;
	if (prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v2] = it->next;

	free(it);
}

void removeNodeList(TGraphL * graph, int v) {
	for (int i = 0; i < graph->nn; i++) {
		removeEdgeList(graph, v, i);
	}
}
