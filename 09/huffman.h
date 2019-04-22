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

void computeFreqs(char * text, int size, int freqs[256]) {
	memset(freqs, 0, 256 * sizeof(char));
	while (size) {
		freqs[*text]++;
		text++;
		size--;
	}
}

HuffmanNode * makeTree(int freqs[256], int * size) {
	HuffmanNode * leafs = (HuffmanNode *)calloc(512, sizeof(HuffmanNode));
	int leafCount = 0;
	for (int i = 0; i < 256; ++i) {
		if (freqs[i]) {
			leafs[leafCount].left = -1;
			leafs[leafCount].right = -1;
			leafs[leafCount].value = i;
			leafCount++;
		}
	}
	APriQueue heap = makeQueue(512);
	for (int i = 0; i < leafCount; ++i) {
		ItemType t = { i, freqs[leafs[i].value] };
		insert(heap, t);
	}
	while (heap->size > 1) {
		int freqL = getMin(heap).prior;
		int indexL = removeMin(heap).content;
		int freqR = getMin(heap).prior;
		int indexR = removeMin(heap).content;
		leafs[leafCount].left = indexL;
		leafs[leafCount].right = indexR;
		ItemType t = { leafCount++, freqL + freqR };
		insert(heap, t);
	}
	*size = leafCount;
	return leafs;
}

void makeCodes(int index, HuffmanNode * nodes, char ** codes, char * code) {
	if (nodes[index].left == -1 && nodes[index].right == -1) {
		strcpy(codes[nodes[index].value], code);
	} else {
		if (nodes[index].left != -1) {
			strcat(code, "0");
			makeCodes(nodes[index].left, nodes, codes, code);
			code[strlen(code) - 1] = 0;
		}
		if (nodes[index].right != -1) {
			strcat(code, "1");
			makeCodes(nodes[index].right, nodes, codes, code);
			code[strlen(code) - 1] = 0;
		}
	}
}

char * compress(char * text, int textSize, HuffmanNode * nodes, int numNodes) {
	char codes[256][10] = { 0 };
	char code[10] = { 0 };
	char * out = (char *)calloc(numNodes * 10, sizeof(char));
	makeCodes(numNodes - 1, nodes, (char **)codes, code);
	for (int i = 0; i < textSize; ++i) {
		strcat(out, codes[text[i]]);
	}
	return out;
}

char getChar(char ** begin, HuffmanNode * nodes, int index) {
	if (**begin == '0') {
		(*begin)++;
		return getChar(begin, nodes, nodes[index].left);
	}
	if (**begin == '1') {
		(*begin)++;
		return getChar(begin, nodes, nodes[index].right);
	}
}

char * decompress(char *text, int textSize, HuffmanNode * nodes, int numNodes) {

}

#endif

