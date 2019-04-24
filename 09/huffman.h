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
	memset(freqs, 0, 256 * sizeof(int));
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
		leafs[leafCount].value = 0;
		ItemType t = { leafCount++, freqL + freqR };
		insert(heap, t);
	}
	*size = leafCount;
	return leafs;
}

void makeCodes(int index, HuffmanNode * nodes, char ** codes, char * code) {
	if (nodes[index].value == 0) {
		strcat(code, "0");
		makeCodes(nodes[index].left, nodes, codes, code);
		code[strlen(code) - 1] = 0;
		strcat(code, "1");
		makeCodes(nodes[index].right, nodes, codes, code);
		code[strlen(code) - 1] = 0;
	} else {
		codes[nodes[index].value] = (char *)calloc(strlen(code) + 1, sizeof(char));
		strcpy(codes[nodes[index].value], code);
	}
}

char * compress(char * text, int textSize, HuffmanNode * nodes, int numNodes) {
	char * codes[256] = { 0 };
	char code[10] = { 0 };
	char * out = (char *)calloc(numNodes * 10, sizeof(char));
	if (numNodes > 1) {
		makeCodes(numNodes - 1, nodes, codes, code);
		for (int i = 0; i < textSize; ++i) {
			strcat(out, codes[text[i]]);
		}
	} else {
		memset(out, '0', textSize * sizeof(char));
		if (textSize == 0) out[0] = 'x';
	}
	return out;
}

char getChar(char ** begin, HuffmanNode * nodes, int index) {
	if (nodes[index].right != -1 || nodes[index].left != -1) {
		if (**begin == '0') {
			(*begin)++;
			return getChar(begin, nodes, nodes[index].left);
		}
		if (**begin == '1') {
			(*begin)++;
			return getChar(begin, nodes, nodes[index].right);
		}
	} else return nodes[index].value;
}

char * decompress(char *text, int textSize, HuffmanNode * nodes, int numNodes) {
	char * string = (char *)calloc(textSize, sizeof(char));
	if (numNodes > 1) {
		while (*text) {
			char app[2] = { getChar(&text, nodes, numNodes - 1), 0 };
			strcat(string, app);
		}
	} else {
		if (text[0] != 'x') {
			while (*text) {
				char app[2] = {nodes->value, 0};
				strcat(string, app);
				text++;
			}
		}
	}
	return string;
}

#endif

