#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <string.h>

typedef struct {
    unsigned char value;
    int left, right;
} HuffmanNode;

#define Item int

// Including below so `Item` is defined.
#include "heap.h"

void computeFreqs(char *text, int size, int freqs[256]) {
}

HuffmanNode *makeTree(int freqs[256], int *size) {
}

void makeCodes(int index, HuffmanNode *nodes, char **codes, char *code) {
}

char *compress(char *text, int textSize, HuffmanNode *nodes, int numNodes) {
}

char *decompress(char *text, int textSize, HuffmanNode *nodes, int numNodes) {
}

#endif

