#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef long T;
#include "OrderedSet.h"

OrderedSet * multiplii(long n, long left, long right) {
    long up = 0;
    long count = 0;
    while (up * n <= right) {
        if (left < up * n) {
            count++;
        }
        up++;
    }
    OrderedSet * s = createOrderedSet(count);
    up = 0;
    while (up * n <= right) {
        if (left < up * n) {
            add(s, up * n);
        }
        up++;
    }
    return s;
}

void print(OrderedSet * s) {
    for (long i = 0; i < s->size; ++i) {
        printf("%ld ", s->elements[i]);
    }
    printf("\n");
}

int main() {
    OrderedSet * m1 = multiplii(3, 4, 25);
    OrderedSet * m2 = multiplii(4, 5, 30);
    OrderedSet * m3 = intersectie(m1, m2);
    OrderedSet * m4 = reuniune(m1, m2);
    print(m1);
    print(m2);
    print(m4);
    print(m3);
    freeSet(m1);
    freeSet(m2);
    freeSet(m3);
    freeSet(m4);
    return 0;
}