#include <assert.h>

#include "common.h"
#include "p1_quadraticSort.h"

int compare(const void * a, const void * b) {
    return (*(int*)a - *(int*)b);
}

//сортировка вставками
void insertion_sort(int* arr, size_t n) {
    assert(arr);
    if (n == 0) {
        return;
    }
    size_t key = 0, j = 0;
    for (size_t i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

//сортировка пузырьком
void bubble_sort(int* arr, size_t n) {
    assert(arr);
    if (n == 0) {
        return;
    }
    for (size_t i = 0; i < n - 1; i++) {
        size_t j = 0;
        while (j < n - i - 1) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
            j++;
        }
    }
}

// сортировка выбором
void selection_sort(int* arr, size_t n) {
    assert(arr);
    if (n == 0) {
        return;
    }
    for (size_t i = 0; i < n - 1; i++) {
        int min = i;
        for (size_t j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        swap(&arr[i], &arr[min]);
    }
}

void shell_sort_knuth(int* arr, size_t n) {
    assert(arr);
    if (n == 0 || arr == NULL) {
        return;
    }

    int gap, i, j, temp;

    for (gap = 1; gap < n / 3; gap = gap * 3 + 1);

    while (gap > 0) {
        for (i = gap; i < n; i++) {
            temp = arr[i];
            j = i;

            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }

            arr[j] = temp;
        }

        gap = (gap - 1) / 3;
    }
}

