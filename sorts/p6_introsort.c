#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "p1_quadraticSort.h"

void quickSort(int* arr, int low, int high) {
    assert(arr);
    if (low < high) {
        int pivot = arr[low], temp, i = low, j = high;
        while (i < j) {
            while (i < j && arr[j] >= pivot)
                j--;
            arr[i] = arr[j];
            while (i < j && arr[i] <= pivot)
                i++;
            arr[j] = arr[i];
        }
        arr[i] = pivot;
        quickSort(arr, low, i - 1);
        quickSort(arr, i + 1, high);
    }
}

void testSortingPerformance(int* arr, int n, int block_size, double* time) {
    assert(arr);
    clock_t start_time, end_time;
    start_time = clock();

    shellSortKnuth(arr, n);

    end_time = clock();
    *time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
}

void optimalBlockSize(int* arr, size_t n) {
    assert(arr);
    if (n == 0)
        return;
    for (int block_size = 1; block_size <= 100; block_size += 1) {
        double time;
        testSortingPerformance(arr, n, block_size, &time);
        printf("Block size: %d, Time taken: %.6f seconds\n", block_size, time);
    }
}

void ShellSort(int* arr, size_t size, int block_size) {
    assert(arr);
    for (int step = block_size; step > 0; step /= 2) {
        for (int i = step; i < size; i++) {
            int temp = arr[i];
            int j = i;
            while (j >= step && arr[j - step] > temp) {
                arr[j] = arr[j - step];
                j -= step;
            }
            arr[j] = temp;
        }
    }
}
