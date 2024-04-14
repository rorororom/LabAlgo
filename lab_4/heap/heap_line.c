#include <assert.h>
#include <stdio.h>

#include "common.h"

void SiftDown(int* arr, int n, int index) {
    assert(arr);
    assert(n     >= 0);
    assert(index >= 0);

    while (index * 2 + 1 < n) {
        int left_child = index * 2 + 1;
        int right_child = index * 2 + 2;
        int smallest = left_child;

        if (right_child < n && arr[right_child] < arr[left_child]) {
            smallest = right_child;
        }

        if (arr[index] <= arr[smallest]) {
            break;
        }

        Swap(arr, index, smallest);

        index = smallest;
    }
}

void HeapLine(int* arr, size_t n) {
    assert(arr);
    for (int i = n / 2; i >= 0; --i) {
        SiftDown(arr, n, i);
    }
}
