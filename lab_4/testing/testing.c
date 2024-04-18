#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "testing.h"

#define PATH_MAX 256

float CallingFuncAndRecordingTime(int* arr, int i, HeapFunction heapFunc) {
    clock_t start_time, end_time;

    start_time = clock();
    heapFunc(arr, i);
    end_time = clock();
    return ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
}

void testing(const char *testFolder, HeapFunction heapFunc,
             const char *nameFileForTime, size_t from, size_t to, size_t step) {
    char filename[PATH_MAX];
    char filename_ans[PATH_MAX];
    int* arr = (int*)malloc(to * sizeof(int));

    assert(arr);

    snprintf(filename_ans, sizeof(filename_ans), "%s/%s.txt", "time", nameFileForTime);
    FILE* output_file = fopen(filename_ans, "w");
    if (output_file == NULL) {
        printf("Error opening output file: %s\n", filename_ans);
    }


    for (size_t i = from; i <= to; i += step) {
        snprintf(filename, sizeof(filename), "%s/%zu.in", testFolder, i);
        FILE* file = fopen(filename, "r");
        if (file == NULL) {
            printf("Error opening input file: %s\n", filename);
            continue;
        }
        for (size_t currentIndex = 0; currentIndex < i; currentIndex++) {
            if (fscanf(file, "%d", &arr[currentIndex]) != 1) {
                printf("Error reading from file: %s\n", filename);
                fclose(file);
                continue;
            }
        }
        fclose(file);

        float time = CallingFuncAndRecordingTime(arr, i, heapFunc);

        fprintf(output_file, "%zu %f\n", i, time);
    }
    fclose(output_file);
    free(arr);
}