#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "heap_build.h"

void Swap(void* a, void* b, size_t size) {
    assert(a);
    assert(b);
    uint8_t* ptr_a = (uint8_t*)a;
    uint8_t* ptr_b = (uint8_t*)b;

    uint64_t tmp64 = 0;
    uint32_t tmp32 = 0;
    uint16_t tmp16 = 0;
    uint8_t  tmp8  = 0;

    SWAP(uint64_t, tmp64);
    SWAP(uint32_t, tmp32);
    SWAP(uint16_t, tmp16);
    SWAP(uint8_t, tmp8);
}

int ParentIndex(size_t index) {
    return (index - 1) / 2;
}

void SiftUp(int* arr, size_t index) {
    assert(arr);

    while (index > 0 && arr[index] < arr[ParentIndex(index)]) {
        Swap(&arr[index], &arr[ParentIndex(index)], sizeof(int));
        index = ParentIndex(index);
    }
}

void HeapInsertion(int* arr, size_t n) {
    assert(arr);

    for (size_t i = 0; i < n; i++) {
        SiftUp(arr, i);
    }
}
