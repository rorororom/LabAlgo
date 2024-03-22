#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

const int CNT_CHILDREN = 5;

void heapifySort(int* arr, int n, int i, int k) {
    assert(arr);
    int largest = i;
    int child;

    while (1) {
        int first_child = k * i + 1;
        int last_child = k * (i + 1);

        for (child = first_child; child <= last_child && child < n; ++child) {
            if (arr[child] > arr[largest]) {
                largest = child;
            }
        }

        if (largest != i) {
            swap(&arr[i], &arr[largest]);
            i = largest;
        } else {
            break;
        }
    }
}


void heap_sort(int* arr, size_t n) {
    assert(arr);
    for (int i = (n / CNT_CHILDREN) - 1; i >= 0; --i) {
        heapifySort(arr, n, i, CNT_CHILDREN);
    }

    for (int i = n - 1; i > 0; --i) {
        swap(&arr[0], &arr[i]);

        heapifySort(arr, i, 0, CNT_CHILDREN);
    }
}

