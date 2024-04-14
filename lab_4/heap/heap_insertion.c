#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "common.h"

void Swap(int* arr, size_t index1, size_t index2) {
    assert(arr != NULL);

    int temp    = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}

int ParentIndex(size_t index) {
    return (index - 1) / 2;
}

void SiftUp(int* arr, size_t index) {
    assert(arr);

    while (index > 0 && arr[index] < arr[ParentIndex(index)]) {
        Swap(arr, index, ParentIndex(index));
        index = ParentIndex(index);
    }
}

void HeapInsertion(int* arr, size_t n) {
    assert(arr);

    for (size_t i = 0; i < n; i++) {
        SiftUp(arr, i);
    }
}
