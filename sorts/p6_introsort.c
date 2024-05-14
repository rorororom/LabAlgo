#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "p1_quadraticSort.h"

void quick_sort(int* arr, int low, int high) {
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
        quick_sort(arr, low, i - 1);
        quick_sort(arr, i + 1, high);
    }
}

void test_sorting_performance(int* arr, int n, int block_size, double* time) {
    assert(arr);
    clock_t start_time, end_time;
    start_time = clock();

    shell_sort_knuth(arr, n);

    end_time = clock();
    *time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
}

void optimal_block_size(int* arr, size_t n) {
    assert(arr);
    if (n == 0)
        return;
    for (int block_size = 1; block_size <= 100; block_size += 1) {
        double time;
        test_sorting_performance(arr, n, block_size, &time);
        printf("Block size: %d, Time taken: %.6f seconds\n", block_size, time);
    }
}

void shell_sort(int* arr, size_t size, int block_size) {
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
