#ifndef HEAP_INSERT
#define HEAP_INSERT

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

void HeapLine(int* arr, size_t n);
void HeapInsertion(int* arr, size_t n);

Heap* initHeap(size_t capacity);

#endif
