#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* Key;
typedef int Value;
typedef long(*HashFunction)(Key, long);

typedef struct Element {
  Key key;
  Value value;
  struct Element *next;
} Element;

typedef struct HashTable {
  Element** elements;
  long size;
  HashFunction hashFunction;
} HashTable;

void initHashTable(HashTable **h, long size, HashFunction f) {
  // Cerinta 1
}

int exists(HashTable *hashTable, Key key) {
  // Cerinta 1
  return 0;
}

Value get(HashTable *hashTable, Key key) {
  // Cerinta 1
  return (Value)0;
}

void put(HashTable *hashTable, Key key, Value value) {
  // Cerinta 1
}

void deleteKey(HashTable *hashTable, Key key) {
  // Cerinta 1
}

void print(HashTable *hashTable) {
  // Cerinta 1
}

void freeHashTable(HashTable *hashTable) {
  // Cerinta 1
}


long hash1(Key word, long size) {
  // Cerinta 2
  return 0l;
}

int main(int argc, char* argv[]) {
  HashTable *hashTable;
  FILE *f1, *f2;
  char word[256];
  long hashSize, common;

  hashSize = atoi(argv[1]);
  f1 = fopen(argv[2], "r");
  f2 = fopen(argv[3], "r");

  initHashTable(&hashTable, hashSize, &hash1);

  // Cerinta 3

  // ...

  // Cerinta 4

  // ...

  printf("Common words: %ld\n", common);

  fclose(f1);
  fclose(f2);
  return 0;
}
