#ifndef ORDERED_SET_H
#define ORDERED_SET_H

#include <stdio.h>                                          // needed for printf
#include <stdlib.h>                           // needed for alloc, realloc, free

/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------

/*
  OrderedSet represents a set with elements of type T stored in memory
  in an ordered fashion.
*/

typedef struct OrderedSet {
    T* elements;                    // pointer to where the elements are in memory
    long size;                                // the number of elements in the set
    long capacity;                      // the current capacity (allocated memory)
} OrderedSet;

// -----------------------------------------------------------------------------

/*
  Function that creates an OrderedSet with elements of type T with a given
  initial capacity.
*/

OrderedSet* createOrderedSet(long initialCapacity) {

    OrderedSet* newSet = (OrderedSet*) malloc(sizeof(OrderedSet));

    newSet->size = 0;                        // initially, the set is empty
    newSet->capacity = initialCapacity;
    newSet->elements = (T*) malloc(initialCapacity * sizeof(T));

    return newSet;
}

void freeSet(OrderedSet * s) {
    free(s->elements);
    free(s);
}

// -----------------------------------------------------------------------------

/*
  Function that checks if an element exists in a given set. As the
  elements of the set are ordered in memory, this function uses binary
  search.

  Function returns 1 if the given element exists in the set, and 0
  otherwise.
*/

int contains(OrderedSet* set, const T element) {
    for (int i = 0; i < set->size; ++i) {
        if (element == set->elements[i]) return 1;
    }
    return 0;
}

// -----------------------------------------------------------------------------

/*
  Function that adds a new element to a set. If the element was
  already in the set, nothing changes. Otherwise, the element is added
  to the set. In the end, the elements must be in ascending order.
*/

void add(OrderedSet* set, const T newElement) {
    if (!contains(set, newElement)) {
        for (int i = 0; i < set->size; ++i) {
            if (newElement < set->elements[i]) {
                memmove(set->elements + i + 1, set->elements + i, (size_t)(set->size - i));
                set->elements[i] = newElement;
                set->size++;
                return;
            }
        }
        set->elements[set->size++] = newElement;

    }
}

// -----------------------------------------------------------------------------

/*
  This function takes two ordered sets with elements of type T and it
  returns the address of a new ordered set representing the union of
  the two
*/

OrderedSet * reuniune(OrderedSet * a, OrderedSet * b) {
    OrderedSet * r = createOrderedSet(a->size + b->size);
    for (int i = 0; i < a->size; ++i) {
        add(r, a->elements[i]);
    }
    for (int i = 0; i < b->size; ++i) {
        if (!contains(a, b->elements[i])) {
            add(r, b->elements[i]);
        }
    }
    return r;
}

OrderedSet * intersectie(OrderedSet * a, OrderedSet * b) {
    OrderedSet * r = createOrderedSet(a->size + b->size);
    for (int i = 0; i < a->size; ++i) {
        if (contains(b, a->elements[i])) {
            add(r, a->elements[i]);
        }
    }
    return r;
}

OrderedSet* unionOrderedSets(OrderedSet* s1, OrderedSet* s2) {
    return reuniune(s1, s2);
}

// -----------------------------------------------------------------------------

/*
  This function takes two ordered sets with elements of type T and it
  returns the addres of a new ordered set representing the
  intersection of the two
*/

OrderedSet* intersectOrderedSets(OrderedSet* s1, OrderedSet* s2) {
    return intersectie(s1, s2);
}


// -----------------------------------------------------------------------------

#endif
