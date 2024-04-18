#ifndef HEAP_BUILD_H
#define HEAP_BUILD_H

#include <stdlib.h>

typedef struct {
    long long int value;
    int index;
    int index_insert;
} Node;

typedef struct {
    Node* heapArray;
    int capacity;
    int size;
} Heap;

#define SWAP(unitxx_t, tmpxx)                          \
    while (size >= sizeof(unitxx_t)) {                 \
        tmpxx = *((unitxx_t*)ptr_a);                   \
        *((unitxx_t*)ptr_a) = *((unitxx_t*)ptr_b);     \
        *((unitxx_t*)ptr_b) = tmpxx;                   \
                                                       \
        ptr_a += sizeof(unitxx_t);                     \
        ptr_b += sizeof(unitxx_t);                     \
        size -= sizeof(unitxx_t);                      \
    }

void HeapLine     (int* arr, size_t n);
void HeapInsertion(int* arr, size_t n);

void Swap(void* a, void* b, size_t size);

#endif
