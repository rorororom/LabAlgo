#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "p1_quadraticSort.h"

#define CHILDREN 5

void heapify(int arr[], int n, int i) {
    int largest = i;
    int firstChild = 5 * i + 1;

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

void heapSortWith5Children(int arr[], int n) {
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

int medianOfThree(int a, int b, int c) {
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

int partition(int arr[], int low, int high) {
    int pivotIndex = medianOfThree(low, (low + high) / 2, high);
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


void introspectiveSortUtil(int arr[], int low, int high, int depth, int depthLimit) {
    int size = high - low + 1;

    if (size <= 1) {
        return;
    }

    if (size < 9) {
        shellSortKnuth(&arr[low], size);
        return;
    }

    if (depth >= depthLimit) {
        heapSortWith5Children(&arr[low], size);
        return;
    }

    int pivot = partition(arr, low, high);

    introspectiveSortUtil(arr, low, pivot, depth + 1, depthLimit);
    introspectiveSortUtil(arr, pivot + 1, high, depth + 1, depthLimit);
}

void introspectiveSort(int arr[], size_t n, int depthLimit) {
    if (n == 0 || arr == NULL) {
        return;
    }

    introspectiveSortUtil(arr, 0, n - 1, 0, depthLimit);
}

int* generate_random_array(size_t size) {
    int* arr = (int*)malloc(sizeof(int) * size);
    for (size_t i = 0; i < size; i++) {
        arr[i] = rand() % 1000;
    }
    return arr;
}

int main() {
    srand(time(NULL));

    int n = 1000000;
    int* arr = generate_random_array(n);
    FILE *file;

    file = fopen("example.txt", "w");

    if (file == NULL) {
        printf("Ошибка открытия файла.\n");
        return 1;
    }

    for (int depth = 1; depth <= 100; depth++) {
        clock_t start_time = clock();
        introspectiveSort(arr, n, depth);
        clock_t end_time = clock();
        double total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        fprintf(file, "%d %.6f \n", depth, total_time);
    }

    fclose(file);

    free(arr);

    return 0;
}
