#include <stdio.h>
#include <stdlib.h>

void Swap                    (int* a,   int *b);
void InsertionSort           (int* arr, int n);
int  FindMedian              (int* arr, int n);
int  FindMedianOfMedians     (int* arr, int n);
void QsortWithMedianOfMedians(int* arr, int low, int high);

int main() {
    int N = 0;
    int result = scanf("%d", &N);
    if (result != 1) {
        printf("Error: Input is not a valid integer.\n");
        return 1;
    }

    int token[N];
    for (size_t i = 0; i < N; i++) {
        result = scanf("%d", &token[i]);
        if (result != 1) {
            printf("Error: Input is not a valid integer.\n");
            return 1;
        }
    }

    QsortWithMedianOfMedians(token, 0, N - 1);

    for (int i = 0; i < N; ++i) {
        printf("%d\n", token[i]);
    }

    return 0;
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
        return FindMedian(arr, n);
    }

    int num_groups = (n + 4) / 5;               // разбиваем на массивы по 5 элементов
                                                // делаем + 4, чтобы при делении с остатком засчитывался и остаток
                                                // то есть для 11 элементов нужно 3 массива
                                                // 2 элемента будут в отдельном массиве

    int medians[num_groups];                    // создаем массивы количеством num_groups

    for (int i = 0; i < num_groups; ++i) {
        int group_start = i * 5;
        int group_end = (group_start + 4 < n) ? group_start + 4 : n - 1; // eсли это условие истинно, то значение конца подмассива
                                                                         //будет group_start + 4.
                                                                         // eсли это условие ложно, то значение конца подмассива будет
                                                                         // n - 1.

        medians[i] = FindMedian(&arr[group_start], group_end - group_start + 1); // теперь каждый подмассив быстро сортруем сортировкой стававками
    }

    return FindMedianOfMedians(medians, num_groups);  // находим медиану медиан
}

void QsortWithMedianOfMedians(int arr[], int low, int high) {
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
                Swap(&arr[i], &arr[j]);
                i++;
                j--;
            }
        }

        QsortWithMedianOfMedians(arr, low, j);
        QsortWithMedianOfMedians(arr, j + 1, high);
    }
}

void Swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
