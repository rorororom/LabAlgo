#include <stdio.h>
#include <stdlib.h>

void Swap                    (void* a, void* b, size_t size);
void InsertionSort           (int* arr, int n);
int  FindMedian              (int* arr, int n);
int  FindMedianOfMedians     (int* arr, int n);
void QsortImpl               (int* arr, int low, int high);
void Qsort                   (int* arr, int n);

void ReadInput               (int** arr, int* n, FILE* input, FILE* output);
void PrintArray              (int* arr, int n, FILE* output);

int main() {
    FILE* input = stdin;
    FILE* output = stdout;

    int N = 0;
    int* token = NULL;

    ReadInput(&token, &N, input, output);

    Qsort(token, N);

    PrintArray(token, N, output);

    free(token);

    return 0;
}

void ReadInput(int** arr, int* n, FILE* input, FILE* output) {
    int result = fscanf(input, "%d", n);
    if (result != 1) {
        fprintf(output, "Error: Input is not a valid integer.\n");
        exit(1);
    }

    *arr = (int*)calloc(*n, sizeof(int));
    if (*arr == NULL) {
        fprintf(output, "Error: Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < *n; ++i) {
        if (fscanf(input, "%d", &(*arr)[i]) != 1) {
            fprintf(output, "Error: Input is not a valid integer.\n");
            exit(1);
        }
    }
}

void PrintArray(int* arr, int n, FILE* output) {
    for (int i = 0; i < n; ++i) {
        fprintf(output, "%d\n", arr[i]);
    }
}

void InsertionSort(int arr[], int n) {
    for (int i = 1; i < n; ++i) {
        int current = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > current) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = current;
    }
}

int FindMedian(int arr[], int n) {
    InsertionSort(arr, n);          // если длина массива <= 5, то можно быстро отсортировать массив,
                                    // используя сортировку вставками
    return arr[n / 2];              // возвращаем медиану
}

int FindMedianOfMedians(int arr[], int n) {
    if (n <= 5) {
        printf("n = %d\n", n);
        return FindMedian(arr, n);
    }

    printf("aaa\n");

    int num_groups = (n + 4) / 5;               // разбиваем на массивы по 5 элементов
                                                // делаем + 4, чтобы при делении с остатком засчитывался и остаток
                                                // то есть для 11 элементов нужно 3 массива
                                                // 2 элемента будут в отдельном массиве

    for (int i = 0; i < num_groups; i++) {
        int group_start = i * 5;
        int group_end = (group_start + 4 < n) ? group_start + 4 : n - 1; // eсли это условие истинно, то значение конца подмассива
                                                                         //будет group_start + 4.
                                                                         // eсли это условие ложно, то значение конца подмассива будет
                                                                         // n - 1.

        InsertionSort(arr + group_start, group_end - group_start + 1);
        int medianIndex = group_start + (group_end - group_start) / 2;
        Swap(&arr[i], &arr[medianIndex], sizeof(int));
    }

    return FindMedianOfMedians(arr, num_groups);  // находим медиану медиан
}

void Qsort(int* arr, int n) {
    QsortImpl(arr, 0, n - 1);
}

void QsortImpl(int arr[], int low, int high) {
    if (low < high) {
        int pivot = FindMedianOfMedians(&arr[low], high - low + 1);

        int i = low;
        int j = high;

        while (i <= j) {
            while (arr[i] < pivot) {
                i++;
            }

            while (arr[j] > pivot) {
                j--;
            }

            if (i <= j) {
                Swap(&arr[i], &arr[j], sizeof(int));
                i++;
                j--;
            }
        }

        QsortImpl(arr, low, j);
        QsortImpl(arr, j + 1, high);
    }
}

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
