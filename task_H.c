#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SWAP(unitxx_t, tmpxx)                          \
    while (size >= sizeof(unitxx_t)) {                 \
        tmpxx = *((unitxx_t*)ptr_a);                   \
        *((unitxx_t*)ptr_a) = *((unitxx_t*)ptr_b);     \
        *((unitxx_t*)ptr_b) = tmpxx;                   \
                                                       \
        ptr_a += sizeof(unitxx_t);                     \
        ptr_b += sizeof(unitxx_t);                     \
        size -= sizeof(unitxx_t);                      \
    }

//================Array Input/Output Functions===================
void InputArray(int** arr, size_t* n, FILE* input, FILE* output);
void PrintArray(int*  arr, size_t size);

//================Sorting and Selection Functions================
void   Qsort         (int* arr, size_t left, size_t right);
size_t HoarePartition(int* arr, size_t left, size_t right);
size_t GetPivot      (int* arr, size_t left, size_t right);
size_t Select        (int* arr, size_t left, size_t right, size_t n);
void   InsertionSort (int* arr, int left, int right);

//================Swap===========================================
void Swap(void* a, void* b, size_t size);
// void Swap(int* a, int* b);

int main() {
    FILE* input = stdin;
    FILE* output = stdout;

    size_t N = 0;
    int* token = NULL;
    InputArray(&token, &N, input, output);

    Qsort(token, 0, N - 1);

    PrintArray(token, N);

    return 0;
}

//===============================================================
//================Sorting and Selection Functions================
//===============================================================

void Qsort(int* arr, size_t left, size_t right) {
    if (left < right) {
        size_t pivotIndex = HoarePartition(arr, left, right);
        Qsort(arr, left, pivotIndex);
        Qsort(arr, pivotIndex + 1, right);
    }
}

size_t HoarePartition(int* arr, size_t left, size_t right) {
    int pivot = arr[GetPivot(arr, left, right)];
    size_t i = left - 1;
    size_t j = right + 1;
    while (1) {
        do {
            i++;
        } while (arr[i] < pivot);
        do {
            j--;
        } while (arr[j] > pivot);
        if (i >= j) {
            return j;
        }
        Swap(&arr[i], &arr[j], sizeof(int));
    }
}

size_t GetPivot(int* arr, size_t left, size_t right) {
    if (right - left < 5) {
        InsertionSort(arr, left, right);
        return (left + right) / 2;
    }
    for (size_t i = left; i <= right; i += 5) {
        size_t subRight = i + 4;
        if (subRight > right) {
            subRight = right;
        }
        size_t median5 = (i + subRight) / 2;
        Swap(&arr[median5], &arr[left + (i - left) / 5], sizeof(int));
    }
    size_t mid = (right - left) / 10 + left + 1;
    return Select(arr, left, left + (right - left) / 5, mid);
}


void InsertionSort(int* arr, int left, int right) {
    for (size_t i = left + 1; i < right; ++i) {
        int current = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > current) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = current;
    }
}

size_t Select(int* arr, size_t left, size_t right, size_t n) {
    assert(arr);
    while (1) {
        if (left == right) {
            return left;
        }
        size_t pivotIndex = GetPivot(arr, left, right);
        pivotIndex = HoarePartition(arr, left, right);
        if (n == pivotIndex) {
            return n;
        } else if (n < pivotIndex) {
            right = pivotIndex - 1;
        } else {
            left = pivotIndex + 1;
        }
    }
}

//===============================================================
//================Array Input/Output Functions===================
//===============================================================

void PrintArray(int* arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void InputArray(int** arr, size_t* n, FILE* input, FILE* output) {
    int result = fscanf(input, "%zu", n);
    if (result != 1) {
        fprintf(output, "Error: Input is not a valid integer.\n");
        exit(1);
    }

    *arr = (int*)calloc(*n, sizeof(int));
    if (*arr == NULL) {
        fprintf(output, "Error: Memory allocation failed.\n");
        exit(1);
    }

    for (size_t i = 0; i < *n; ++i) {
        if (fscanf(input, "%d", &(*arr)[i]) != 1) {
            fprintf(output, "Error: Input is not a valid integer.\n");
            exit(1);
        }
    }
}

//===============================================================
//================Swap===========================================
//===============================================================

void Swap(void* a, void* b, size_t size) {
    assert(a);
    assert(b);
    uint8_t* ptr_a = (uint8_t*)a;
    uint8_t* ptr_b = (uint8_t*)b;

    uint64_t tmp64 = 0;
    uint32_t tmp32 = 0;
    uint16_t tmp16 = 0;
    uint8_t  tmp8  = 0;

    SWAP(uint64_t, tmp64);
    SWAP(uint32_t, tmp32);
    SWAP(uint16_t, tmp16);
    SWAP(uint8_t, tmp8);
}
