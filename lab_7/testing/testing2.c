#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "../RMQ/sparse_table.h"

const int N = 1000000;
const int CNT = 5;

// #define VAR1
#define VAR2

#ifdef VAR2
bool VAR = 1;
#endif

#ifdef VAR1
bool VAR = 0;
#endif

typedef struct {
    int start;
    int end;
} Segment;

void measureTime(int** table, int* arr, Segment* segments, int n, int* log_table) {
    clock_t start, end;
    double total_time = 0.0;

    for (int j = 0; j < CNT; j++) {
        start = clock();
        for (int i = 0; i < n; i++) {
            int result = query(table, segments[i].start, segments[i].end, log_table, VAR);
        }
        end = clock();
        total_time += ((double) (end - start)) / CLOCKS_PER_SEC;
    }

    printf("Среднее время ответа на запрос: %f секунд\n", total_time / CNT);
}

int main() {
    const char* filename = "../generator/test.txt";

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла %s\n", filename);
        return 1;
    }

    Segment* segments = (Segment*) malloc(N * sizeof(Segment));
    if (segments == NULL) {
        printf("Ошибка при выделении памяти для отрезков\n");
        fclose(file);
        return 1;
    }

    for (int i = 0; i < N; i++) {
        int res = fscanf(file, "%d %d", &segments[i].start, &segments[i].end);
        if (res != 2) {
            printf("не считалось\n");
            return 1;
        }
    }

    fclose(file);

    int* arr = (int*) calloc(N, sizeof(int));
    if (arr == NULL) {
        printf("Ошибка при выделении памяти для массива\n");
        free(segments);
        return 1;
    }

    filename = "../generator/random_numbers.txt";

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла %s\n", filename);
        return 1;
    }

    for (int i = 0; i < N; i++) {
        int res = fscanf(file, "%d", &arr[i]);
        if (res != 1) {
            printf("не считалось\n");
            return 1;
        }
    }
    fclose(file);

    int* log_table = computeLogTable(N);
    int** table = ctorTable(arr, N, log_table, VAR);

    if (table == NULL) {
        printf("Ошибка при построении Sparse Table\n");
        free(segments);
        free(arr);
        free(log_table);
        return 1;
    }

    measureTime(table, arr, segments, N, log_table);

    free(segments);
    free(arr);
    free(log_table);

    freeSparseTable(table, N, log_table, VAR);
    return 0;
}
