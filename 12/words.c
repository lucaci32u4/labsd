#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char * Key;
typedef int Value;

typedef long(* HashFunction)(Key, long);

typedef struct Element {
	Key key;
	Value value;
	struct Element * next;
} Element;

typedef struct HashTable {
	Element ** elements;
	long size;
	HashFunction hashFunction;
} HashTable;

void initHashTable(HashTable ** h, long size, HashFunction f) {
	HashTable * table = (HashTable *) calloc(1, sizeof(HashTable));
	table->size = size;
	table->hashFunction = f;
	table->elements = (Element **) calloc(size, sizeof(Element *));
	*h = table;
}

long hashIndex(HashTable * t, Key key) {
	return t->hashFunction(key, t->size);
}

int exists(HashTable * hashTable, Key key) {
	long index = hashIndex(hashTable, key);
	for (Element * cursor = hashTable->elements[index]; cursor; cursor = cursor->next) {
		if (strcmp(cursor->key, key) == 0) return 1;
	}
	return 0;
}

Value get(HashTable * hashTable, Key key) {
	long index = hashIndex(hashTable, key);
	for (Element * cursor = hashTable->elements[index]; cursor; cursor = cursor->next) {
		if (strcmp(cursor->key, key) == 0) return cursor->value;
	}
	return 0;
}

void put(HashTable * hashTable, Key key, Value value) {
	long i = hashIndex(hashTable, key);
	Element * element = (Element *) calloc(1, sizeof(Element));
	element->key = (Key)calloc(strlen(key) + 1, sizeof(char));
	strcpy(element->key, key);
	element->value = value;
	if (hashTable->elements[i]) {
		Element * cursor = hashTable->elements[i];
		while (cursor->next) {
			cursor = cursor->next;
		}
		cursor->next = element;
	} else {
		hashTable->elements[i] = element;
	}
}

void deleteKey(HashTable * hashTable, Key key) {
	long i = hashIndex(hashTable, key);
	Element * cursor = hashTable->elements[i];
	if (cursor) {
		if (strcmp(cursor->key, key) == 0) {
			hashTable->elements[i] = cursor->next;
			free(cursor->key);
			free(cursor);
		} else {
			while (cursor->next) {
				if (strcmp(cursor->next->key, key) == 0) {
					Element * next = cursor->next->next;
					free(cursor->next->key);
					free(cursor->next);
					cursor->next = next;
				}
				cursor = cursor->next;
			}
		}
	}
}

void print(HashTable * hashTable) {
	printf("_____\n");
	for (int i = 0; i < hashTable->size; ++i) {
		if (hashTable->elements[i]) {
			printf("%s |", hashTable->elements[i]->key);
			for (Element * cursor = hashTable->elements[i]; cursor; cursor = cursor->next) {
				printf(" %d :", cursor->value);
			}
			printf("\n");
		}
	}
}

void freeHashTable(HashTable * hashTable) {
	for (int i = 0; i < hashTable->size; ++i) {
		if (hashTable->elements[i]) {
			Element * cursor = hashTable->elements[i];
			while (cursor) {
				Element * next = cursor->next;
				free(cursor->key);
				free(cursor);
				cursor = next;
			}
		}

	}
}


long hash1(Key word, long size) {
	int h = 0;
	do {
		h = h * 17 + *word;
	} while (*(++word));
	return abs(h) % size;
}

char * readFile(FILE * file) {
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, 0, SEEK_SET);
	char * data = (char *)calloc(size + 1, sizeof(char));
	fread(data, size, 1, file);
	return data;
}

HashTable * createHashTable(FILE * file) {
	HashTable * hashTable;
	initHashTable(&hashTable, 1000, hash1);
	char * data = readFile(file);
	for (char * cuv = strtok(data, "\n\r "); cuv; cuv = strtok(NULL, "\n\r ")) {
		if (exists(hashTable, cuv)) {
			int occ = 1 + get(hashTable, cuv);
			deleteKey(hashTable, cuv);
			put(hashTable, cuv, occ);
		} else {
			put(hashTable, cuv, 1);
		}
	}
	free(data);
	return hashTable;
}

int main(int argc, char * argv[]) {
	HashTable * h1, * h2;
	FILE * f1, * f2;
	long common = 0;
	f1 = fopen("fileA", "rb");
	f2 = fopen("fileB", "rb");

	h1 = createHashTable(f1);
	print(h1);
	h2 = createHashTable(f2);
	for (int i = 0; i < 1000; ++i) {
		for (Element * cursor = h1->elements[i]; cursor; cursor = cursor->next) {
			if (exists(h2, cursor->key)) {
				int occ = get(h2, cursor->key);
				if (occ < cursor->value) common += occ;
				else common += cursor->value;
			}
		}
	}
	printf("Common words: %ld\n", common);

	freeHashTable(h1);
	freeHashTable(h2);
	fclose(f1);
	fclose(f2);
	return 0;
}
