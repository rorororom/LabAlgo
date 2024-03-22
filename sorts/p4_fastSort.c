#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "p4_fastSort.h"
#include "common.h"
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
int lomutoPartition(int* arr, int low, int high) {
    assert(arr);
    int pivot = arr[low + (high - low) / 2];
    swap(&arr[low + (high - low) / 2], &arr[high]);
    int i = low;

    for (int j = low; j <= high; j++) {
        if (arr[j] < pivot) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[high]);
    return i;
}

void quicksortLomuto(int* arr, int low, int high) {
    assert(arr);
    if (low < high) {
        int pivot_index = lomutoPartition(arr, low, high);
        quicksortLomuto(arr, low, pivot_index);
        quicksortLomuto(arr, pivot_index + 1, high);
    }
}

void LomutoSort(int* arr, size_t n) {
    assert(arr);
    if (n == 0) {
        return;
    }

    quicksortLomuto(arr, 0, n - 1);
}

void quicksortLomutoOneBranch(int* arr, int low, int high) {
    assert(arr);
    while (low < high) {
        int pivot_index = lomutoPartition(arr, low, high);
        quicksortLomutoOneBranch(arr, low, pivot_index - 1);
        low = pivot_index + 1;
    }
}

void LomutoSortOneBranch(int* arr, size_t n) {
    assert(arr);
    if (n == 0) {
        return;
    }

    quicksortLomutoOneBranch(arr, 0, n - 1);
}
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
int hoarePartition(int* arr, int low, int high) {
    assert(arr);
    int pivot = arr[low + (high - low) / 2];
    int i = low - 1;
    int j = high + 1;

    while (1) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j)
            return j;

        swap(&arr[i], &arr[j]);
    }
}

void quicksortHoare(int* arr, int low, int high) {
    assert(arr);
    if (low < high) {
        int pivot_index = hoarePartition(arr, low, high);
        quicksortHoare(arr, low, pivot_index);
        quicksortHoare(arr, pivot_index + 1, high);
    }
}

void HoareSort(int* arr, size_t n) {
    assert(arr);
    if (n == 0) {
        return;
    }

    quicksortHoare(arr, 0, n - 1);
}

void quicksortHoareOneBranch(int* arr, int low, int high) {
    assert(arr);
    while (low < high) {
        int pivot_index = hoarePartition(arr, low, high);
        quicksortHoareOneBranch(arr, low, pivot_index);
        low = pivot_index + 1;
    }
}

void HoareSortOneBranch(int* arr, size_t n) {
    assert(arr);
    if (n == 0) {
        return;
    }

    quicksortHoareOneBranch(arr, 0, n - 1);
}
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
int thickPartition(int* arr, int low, int high) {
    assert(arr);
    int pivot_index = (low + high) / 2;
    int pivot = arr[pivot_index];

    swap(&arr[pivot_index], &arr[high]);

    int i = low;
    int j = high - 1;

    while (1) {
        while (arr[i] < pivot) {
            i++;
        }
        while (j > 0 && arr[j] > pivot) {
            j--;
        }
        if (i >= j) {
            break;
        }
        swap(&arr[i], &arr[j]);
        i++;
        j--;
    }

    swap(&arr[i], &arr[high]);

    return i;
}


void quicksortThick(int* arr, int low, int high) {
    assert(arr);
    if (low < high) {
        int pivot_index = thickPartition(arr, low, high);
        quicksortThick(arr, low, pivot_index);
        quicksortThick(arr, pivot_index + 1, high);
    }
}

void ThickSort(int* arr, size_t n) {
    assert(arr);
    if (n == 0) {
        return;
    }

    quicksortThick(arr, 0, n - 1);
}


void quicksortThickOneBranch(int* arr, int low, int high) {
    assert(arr);
    while (low < high) {
        int pivot_index = thickPartition(arr, low, high);
        quicksortThickOneBranch(arr, low, pivot_index - 1);
        low = pivot_index + 1;
    }
}

void ThickSortOneBranch(int* arr, size_t n) {
    assert(arr);
    if (n == 0) {
        return;
    }

    quicksortThickOneBranch(arr, 0, n - 1);
}

