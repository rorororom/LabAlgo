#include <stdio.h>
#include <stdlib.h>

//================Array Input/Output Functions===================
void InputArray(int** arr, size_t* n, FILE* input, FILE* output);
void PrintArray(int*  arr, size_t size);

//================Sorting and Selection Functions================
void   Qsort        (int* arr, size_t left, size_t right);
size_t GetPivot     (int* arr, size_t left, size_t right);
size_t Select       (int* arr, size_t left, size_t right, size_t n);
size_t Partition    (int* arr, size_t left, size_t right, size_t GetPivot);
void   InsertionSort(int* arr, size_t n);

//================Swap===========================================
void Swap(void* a, void* b, size_t size);

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
        size_t GetPivotIndex = GetPivot(arr, left, right);
        size_t newGetPivotIndex = Partition(arr, left, right, GetPivotIndex);

        Qsort(arr, left, newGetPivotIndex - 1);
        Qsort(arr, newGetPivotIndex + 1, right);
    }
}

void InsertionSort(int* arr, size_t n) {
    for (size_t i = 1; i < n; ++i) {
        int current = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > current) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = current;
    }
}

size_t Partition(int* arr, size_t left, size_t right, size_t GetPivot) {
    int GetPivotValue = arr[GetPivot];
    arr[GetPivot] = arr[right];
    arr[right] = GetPivotValue;

    size_t storeIndex = left;
    for (size_t i = left; i < right; ++i) {
        if (arr[i] < GetPivotValue) {
            Swap(&arr[i], &arr[storeIndex], sizeof(int));
            storeIndex++;
        }
    }

    Swap(&arr[storeIndex], &arr[right], sizeof(int));

    return storeIndex;
}

size_t Select(int* arr, size_t left, size_t right, size_t n) {
    while (1) {
        if (left == right) {
            return left;
        }
        size_t GetPivotIndex = (left + right) / 2;
        GetPivotIndex = Partition(arr, left, right, GetPivotIndex);
        if (n == GetPivotIndex) {
            return n;
        } else if (n < GetPivotIndex) {
            right = GetPivotIndex - 1;
        } else {
            left = GetPivotIndex + 1;
        }
    }
}

size_t GetPivot(int* arr, size_t left, size_t right) {
    if (right - left < 5) {
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
    size_t mid = (left + right) / 10;
    return Select(arr, left, left + (right - left) / 5, mid);
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
    uint8_t* ptr_a = (uint8_t*)a;
    uint8_t* ptr_b = (uint8_t*)b;

    uint64_t tmp64 = 0;
    uint32_t tmp32 = 0;
    uint16_t tmp16 = 0;

    while (size >= sizeof(uint64_t)) {
        tmp64 = *((uint64_t*)ptr_a);
        *((uint64_t*)ptr_a) = *((uint64_t*)ptr_b);
        *((uint64_t*)ptr_b) = tmp64;

        ptr_a += sizeof(uint64_t);
        ptr_b += sizeof(uint64_t);
        size -= sizeof(uint64_t);
    }

    while (size >= sizeof(uint32_t)) {
        tmp32 = *((uint32_t*)ptr_a);
        *((uint32_t*)ptr_a) = *((uint32_t*)ptr_b);
        *((uint32_t*)ptr_b) = tmp32;

        ptr_a += sizeof(uint32_t);
        ptr_b += sizeof(uint32_t);
        size -= sizeof(uint32_t);
    }

    while (size >= sizeof(uint16_t)) {
        tmp16 = *((uint16_t*)ptr_a);
        *((uint16_t*)ptr_a) = *((uint16_t*)ptr_b);
        *((uint16_t*)ptr_b) = tmp16;

        ptr_a += sizeof(uint16_t);
        ptr_b += sizeof(uint16_t);
        size -= sizeof(uint16_t);
    }

    while (size >= sizeof(uint8_t)) {
        uint8_t tmp8 = *ptr_a;
        *ptr_a = *ptr_b;
        *ptr_b = tmp8;

        ptr_a += sizeof(uint8_t);
        ptr_b += sizeof(uint8_t);
        size -= sizeof(uint8_t);
    }
}
