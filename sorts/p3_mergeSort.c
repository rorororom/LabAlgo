#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "p3_mergeSort.h"

void merge(int* arr, int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));
    assert(L);
    assert(R);

    for (int i = 0; i < n1; i++)
        L[i] = arr[low + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i++];
        } else {
            arr[k] = R[j++];
        }
        k++;
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }

    free(L);
    free(R);
}

//----------------------------------------------------------------------------------
void mergeSortIterative(int* arr, size_t n) {
    assert(arr);
    for (int i = 1; i < n; i *= 2) {
        for (int j = 0; j < n - i; j += 2 * i) {
            int mid = j + i - 1;
            int right_end = (j + 2 * i - 1 < n) ? j + 2 * i - 1 : n - 1;

            merge(arr, j, mid, right_end);
        }
    }
}
//----------------------------------------------------------------------------------

void mergeSortRecursive(int* arr, int low, int high) {
    assert(arr);
    if (low < high) {
        int mid = low + (high - low) / 2;

        mergeSortRecursive(arr, low, mid);
        mergeSortRecursive(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

void mergeSortRecursiveMain(int* arr, int n) {
    mergeSortRecursive(arr, 0, n - 1);
}
//----------------------------------------------------------------------------------
