#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "p4_fastSort.h"
#include "common.h"
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
int lomuto_partition(int* arr, int low, int high) {
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

void quicksort_lomuto(int* arr, int low, int high) {
    assert(arr);
    if (low < high) {
        int pivot_index = lomuto_partition(arr, low, high);
        quicksort_lomuto(arr, low, pivot_index);
        quicksort_lomuto(arr, pivot_index + 1, high);
    }
}

void lomuto_sort(int* arr, size_t n) {
    assert(arr);
    if (n == 0) {
        return;
    }

    quicksort_lomuto(arr, 0, n - 1);
}

void quicksort_lomuto_one_branch(int* arr, int low, int high) {
    assert(arr);
    while (low < high) {
        int pivot_index = lomuto_partition(arr, low, high);
        quicksort_lomuto_one_branch(arr, low, pivot_index - 1);
        low = pivot_index + 1;
    }
}

void lomuto_sort_one_branch(int* arr, size_t n) {
    assert(arr);
    if (n == 0) {
        return;
    }

    quicksort_lomuto_one_branch(arr, 0, n - 1);
}
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
int hoare_partition(int* arr, int low, int high) {
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

void quicksort_hoare(int* arr, int low, int high) {
    assert(arr);
    if (low < high) {
        int pivot_index = hoare_partition(arr, low, high);
        quicksort_hoare(arr, low, pivot_index);
        quicksort_hoare(arr, pivot_index + 1, high);
    }
}

void hoare_sort(int* arr, size_t n) {
    assert(arr);
    if (n == 0) {
        return;
    }

    quicksort_hoare(arr, 0, n - 1);
}

void quicksort_hoare_one_branch(int* arr, int low, int high) {
    assert(arr);
    while (low < high) {
        int pivot_index = hoare_partition(arr, low, high);
        quicksort_hoare_one_branch(arr, low, pivot_index);
        low = pivot_index + 1;
    }
}

void Hoare_sort_one_branch(int* arr, size_t n) {
    assert(arr);
    if (n == 0) {
        return;
    }

    quicksort_hoare_one_branch(arr, 0, n - 1);
}
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
int thick_partition(int* arr, int low, int high) {
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


void quicksort_thick(int* arr, int low, int high) {
    assert(arr);
    if (low < high) {
        int pivot_index = thick_partition(arr, low, high);
        quicksort_thick(arr, low, pivot_index);
        quicksort_thick(arr, pivot_index + 1, high);
    }
}

void thick_sort(int* arr, size_t n) {
    assert(arr);
    if (n == 0) {
        return;
    }

    quicksort_thick(arr, 0, n - 1);
}


void quicksort_thick_one_branch(int* arr, int low, int high) {
    assert(arr);
    while (low < high) {
        int pivot_index = thick_partition(arr, low, high);
        quicksort_thick_one_branch(arr, low, pivot_index - 1);
        low = pivot_index + 1;
    }
}

void thick_sort_one_branch(int* arr, size_t n) {
    assert(arr);
    if (n == 0) {
        return;
    }

    quicksort_thick_one_branch(arr, 0, n - 1);
}

