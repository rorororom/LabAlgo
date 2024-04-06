#include <assert.h>

#include "p3_mergeSort.h"
#include "p3_mergeSort.h"

void merge(int* arr, int low, int mid, int high, int* buff) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    // Используем buff для временных массивов L и R
    int* L = buff;
    int* R = buff + n1;

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
}

void merge_sort_recursive(int* arr, int low, int high, int* buff) {
    if (low < high) {
        int mid = low + (high - low) / 2;

        merge_sort_recursive(arr, low, mid, buff);
        merge_sort_recursive(arr, mid + 1, high, buff);

        merge(arr, low, mid, high, buff);
    }
}

void merge_sort_recursive_main(int* arr, int n) {
    int* buff = (int*)malloc(n * sizeof(int));
    assert(buff);

    merge_sort_recursive(arr, 0, n - 1, buff);

    free(buff);
}

void merge_sort_iterative(int* arr, size_t n) {
    int* buff = (int*)malloc(n * sizeof(int));
    assert(buff);

    for (int i = 1; i < n; i *= 2) {
        for (int j = 0; j < n - i; j += 2 * i) {
            int mid = j + i - 1;
            int right_end = (j + 2 * i - 1 < n) ? j + 2 * i - 1 : n - 1;

            merge(arr, j, mid, right_end, buff);
        }
    }

    free(buff);
}
