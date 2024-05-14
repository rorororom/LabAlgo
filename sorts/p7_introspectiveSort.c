#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "p1_quadraticSort.h"
#include "p7_introspectiveSort.h"

#define CHILDREN 5

void heapify(int* arr, int n, int i) {
    assert(arr);
    int largest = i;
    int firstChild = CHILDREN * i + 1;

    for (int j = 1; j <= CHILDREN; j++) {
        int child = firstChild + j - 1;
        if (child < n && arr[child] > arr[largest]) {
            largest = child;
        }
    }

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heap_sort_with_5_children(int* arr, int n) {
    assert(arr);
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

int find_median_of_three(int a, int b, int c) {
    if (a < b) {
        if (b < c)
            return b;
        else if (a < c)
            return c;
        else
            return a;
    } else {
        if (a < c)
            return a;
        else if (b < c)
            return c;
        else
            return b;
    }
}

int partition(int* arr, int low, int high) {
    assert(arr);
    int pivotIndex = find_median_of_three(low, (low + high) / 2, high);
    int pivotValue = arr[pivotIndex];
    int i = low - 1;
    int j = high + 1;

    while (1) {
        do {
            i++;
        } while (arr[i] < pivotValue);

        do {
            j--;
        } while (arr[j] > pivotValue);

        if (i >= j) {
            return j;
        }

        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}


void introspective_sort_util(int* arr, int low, int high, int depth) {
    assert(arr);
    int size = high - low + 1;

    if (size <= 1) {
        return;
    }

    if (size < 9) {
        shell_sort_knuth(&arr[low], size);
        return;
    }

    if (depth >= 16) {
        heap_sort_with_5_children(&arr[low], size);
        return;
    }

    int pivot = partition(arr, low, high);

    introspective_sort_util(arr, low, pivot, depth + 1);
    introspective_sort_util(arr, pivot + 1, high, depth + 1);
}

void introspective_sort(int* arr, size_t n) {
    assert(arr);
    if (n == 0 || arr == NULL) {
        return;
    }

    introspective_sort_util(arr, 0, n - 1, 0);
}

void introspect_sort(int* arr, size_t n) {
    assert(arr);
    introspective_sort(arr, n);
}
