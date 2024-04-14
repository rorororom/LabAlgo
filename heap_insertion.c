#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "common.h"

Heap* initHeap(size_t capacity) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    assert(heap);

    heap->capacity = capacity;
    heap->size = 0;
    heap->heapArray = (Node*)malloc(capacity * sizeof(Node));
    assert(heap->heapArray);

    return heap;
}

void swap(int* arr, size_t index1, size_t index2) {
    assert(arr != NULL);

    int temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}

int parentIndex(size_t index) {
    return (index - 1) / 2;
}

void siftUp(int* arr, size_t index) {
    assert(arr);

    while (index > 0 && arr[index] < arr[parentIndex(index)]) {
        swap(arr, index, parentIndex(index));
        index = parentIndex(index);
    }
}

void HeapInsertion(int* arr, size_t n) {
    assert(arr);

    for (size_t i = 0; i < n; i++) {
        siftUp(arr, i);
    }
}
