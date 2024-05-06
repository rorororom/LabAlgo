#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FEN
// #define SEGMENT_TREE

#ifdef FEN
#include "../RSQ/Fenwik.h"
#endif

#ifdef SEGMENT_TREE
#include "../RSQ/SEGMENT_TREE.h"
#endif

const int N = 1000000;
const int CNT = 5;

typedef struct {
    int start;
    int end;
} Segment;

void measureTime(int* tree, int* arr, Segment* segments, int n) {
    clock_t start, end;
    double total_time = 0.0;

    for (int i = 0; i < n; i++) {
#ifdef FEN
        update(tree, i, arr[i], n);
#endif
    }

#ifdef SEGMENT_TREE
    build(tree, arr, 1, 0, N - 1);
#endif

    for (int j = 0; j < CNT; j++) {
        start = clock();
        for (int i = 0; i < n; i++) {
#ifdef FEN
            long long  sum = getSum(tree, segments[i].start, segments[i].end);
#endif
#ifdef SEGMENT_TREE
            long long sum = query(tree, 1, 0, n - 1, segments[i].start - 1, segments[i].end - 1);
            //printf("sum = %lld\n", sum);
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
        int res = fscanf(file, "%d %d", &segments[i].start, &segments[i].end);
        if (res != 2) {
            printf("не считалось\n");
            return 1;
        }
    }

    fclose(file);

    int* arr = (int*) calloc(N, sizeof(int));
    if (arr == NULL) {
        printf("Ошибка при выделении памяти для дерева отрезков\n");
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

    int* tree = NULL;
#ifdef SEGMENT_TREE
    tree = (int*) calloc(N * 4, sizeof(int));
#endif
#ifdef FEN
    tree = (int*) calloc(N + 1, sizeof(int));
#endif

    if (tree == NULL) {
        printf("Ошибка при выделении памяти для дерева отрезков\n");
        free(segments);
        return 1;
    }

    measureTime(tree, arr, segments, N);

    free(segments);
    free(tree);
    free(arr);

    return 0;
}
