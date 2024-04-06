#include <assert.h>

#include "common.h"

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
int median_of_three(int* arr, int low, int high) {
    assert(arr);
    int mid = (low + high) / 2;

    if (arr[low] > arr[mid])
        swap(&arr[low], &arr[mid]);
    if (arr[low] > arr[high])
        swap(&arr[low], &arr[high]);
    if (arr[mid] > arr[high])
        swap(&arr[mid], &arr[high]);

    return mid;
}
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
int median_of_three_random(int* arr, int low, int high) {
    assert(arr);
    int mid1 = low + rand() % (high - low + 1);
    int mid2 = low + rand() % (high - low + 1);
    int mid3 = low + rand() % (high - low + 1);

    return median_of_three(arr, median_of_three(arr, mid1, mid2), mid3);
}

//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
int choose_pivot(int* arr, int low, int high, int method_pivot) {
    assert(arr);
    switch (method_pivot) {
        case 1: // Центральный элемент
            return (low + high) / 2;
        case 2: // Медиана 3
            return median_of_three(arr, low, high);
        case 3: // Случайный элемент
            return low + rand() % (high - low + 1);
        case 4: // Медиана трех случайных
            return median_of_three_random(arr, low, high);
        default: // центральный элемент
            return (low + high) / 2;
    }
}
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
int partitionP5(int* arr, int low, int high, int method_pivot) {
    assert(arr);
    int pivot_index = choose_pivot(arr, low, high, method_pivot);
    int pivot = arr[pivot_index];
    swap(&arr[pivot_index], &arr[high]);

    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quicksort(int* arr, int low, int high, int method_pivot) {
    assert(arr);
    if (low < high) {
        int pi = partitionP5(arr, low, high, method_pivot);
        quicksort(arr, low, pi - 1, method_pivot);
        quicksort(arr, pi + 1, high, method_pivot);
    }
}
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
void sort_center_element(int* arr, size_t n) {
    assert(arr);
    quicksort(arr, 0, n - 1, 1);
}

void sort_median_of_three(int* arr, size_t n) {
    assert(arr);
    quicksort(arr, 0, n - 1, 2);
}

void sort_random_element(int* arr, size_t n) {
    assert(arr);
    quicksort(arr, 0, n - 1, 3);
}

void sort_median_of_three_random(int* arr, size_t n) {
    assert(arr);
    quicksort(arr, 0, n - 1, 2);
}


