#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../RMQ/sparse_table.h"

const int N = 1000000;
const int CNT = 5;

// #define VAR1
#define VAR2

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
#ifdef VAR1
            int result = query1(table, segments[i].start, segments[i].end, log_table);
#endif
#ifdef VAR2
            int result = query2(table, segments[i].start, segments[i].end, log_table);
#endif
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
        fscanf(file, "%d %d", &segments[i].start, &segments[i].end);
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
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);

    int* log_table = computeLogTable(N);

    int** table = NULL;
#ifdef VAR1
    table = buildTable1(arr, N, log_table);
#endif
#ifdef VAR2
    table = buildTable2(arr, N, log_table);
#endif

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

#ifdef VAR1
    freeSparseTable1(table, N);
#endif
#ifdef VAR2
    freeSparseTable2(table, N, log_table);
#endif

    return 0;
}
