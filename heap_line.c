#include <assert.h>
#include <stdio.h>

#include "common.h"

void sift_down(int* arr, int n, int index) {
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

        int temp = arr[index];
        arr[index] = arr[smallest];
        arr[smallest] = temp;

        index = smallest;
    }
}

void build_heap(int* arr, int n) {
    assert(arr);

    for (int i = n / 2; i >= 0; --i) {
        sift_down(arr, n, i);
    }
}

void HeapLine(int* arr, size_t n) {
    assert(arr);
    build_heap(arr, n);
}
