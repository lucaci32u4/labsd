#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

typedef struct MinHeapNode
{
    int  v;
    int d;
} MinHeapNode;


typedef struct MinHeap
{
    int size;
    int capacity;
    int *pos;
    MinHeapNode **elem;
} MinHeap;


MinHeapNode* newNode(int v, int d)
{

}

MinHeap* newQueue(int capacity)
{
  
}

void swap(MinHeapNode** a, MinHeapNode** b)
{
   
}

void SiftDown(MinHeap* h, int idx)
{
    
}

int isEmpty(MinHeap* h)
{
    
}

MinHeapNode* removeMin(MinHeap* h)
{
    
}

void SiftUp(MinHeap* h, int v, int d)
{
    
}

int isInMinHeap(MinHeap *h, int v)
{
  
}

#endif

