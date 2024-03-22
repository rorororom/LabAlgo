#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "../sorts/p1_quadraticSort.h"
#include "../sorts/p2_heapSort.h"
#include "../sorts/p3_mergeSort.h"
#include "../sorts/p4_fastSort.h"
#include "../sorts/p5_quickSortDifferPivot.h"
#include "../sorts/p6_introSort.h"
#include "../sorts/p7_introspectiveSort.h"
#include "../sorts/p8_LSD_MSD.h"

#include "testing.h"

void CallingSortAndRecordingTime(float* arr_time, int* arr, int i, int j, SortFunction sortFunc) {
    clock_t start_time, end_time;

    start_time = clock();
    sortFunc(arr, i);
    end_time = clock();
    arr_time[j] = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
}

void testing(const char *testFolder, SortFunction sortFunc, const char *resultPath,
             const char *nameFileForTime, size_t from, size_t to, size_t step, size_t k) {
    char filename[256];
    char filename_ans[256];
    int* arr = (int*)malloc(to * sizeof(int));
    float* arr_time = (float*)malloc(k * sizeof(float));

    assert(arr);
    assert(arr_time);

    snprintf(filename_ans, sizeof(filename_ans), "%s/%s.txt", "time", nameFileForTime);
    FILE* output_file_bubble = fopen(filename_ans, "w");
    if (output_file_bubble == NULL) {
        printf("Error opening output file: %s\n", filename_ans);
    }


    for (size_t i = from; i <= to; i += step) {
        for (size_t j = 0; j < k; j++) {
            snprintf(filename, sizeof(filename), "%s/%zu_%zu.in", testFolder, i, j);
            FILE* file = fopen(filename, "r");
            if (file == NULL) {
                printf("Error opening input file: %s\n", filename);
                continue;
            }
            for (size_t q = 0; q < i; q++) {
                if (fscanf(file, "%d", &arr[q]) != 1) {
                    printf("Error reading from file: %s\n", filename);
                    fclose(file);
                    continue;
                }
            }
            fclose(file);

            CallingSortAndRecordingTime(arr_time, arr, i, j, sortFunc);

            snprintf(filename_ans, sizeof(filename_ans), "%s/%zu_%zu.out", resultPath, i, j);
            FILE* output_file = fopen(filename_ans, "w");
            if (output_file == NULL) {
                printf("Error opening output file: %s\n", filename_ans);
                continue;
            }

            for (size_t q = 0; q < i; q++) {
                fprintf(output_file, "%d\n", arr[q]);
            }
            fclose(output_file);

            snprintf(filename, sizeof(filename), "%s/%zu_%zu.out", testFolder, i, j);
            compareFiles(filename, filename_ans);
        }

        float time = 0;
        for (size_t q = 0; q < k; q++) {
            time += arr_time[q];
        }
        time = time / k;

        fprintf(output_file_bubble, "%zu %f\n", i, time);
    }
    fclose(output_file_bubble);
    free(arr);
    free(arr_time);
}

void compareFiles(const char* file1, const char* file2) {
    FILE* f1 = fopen(file1, "r");
    FILE* f2 = fopen(file2, "r");

    if (f1 == NULL || f2 == NULL) {
        fprintf(stderr, "Error opening files\n");
        return;
    }

    int num1 = 0, num2 = 0;
    size_t position = 0;

    while (fscanf(f1, "%d", &num1) == 1 && fscanf(f2, "%d", &num2) == 1) {
        position++;
        if (num1 != num2) {
            fprintf(stderr, "Files do not match at position %zu\n", position);
            printf("%d %d\n", num1, num2);
            assert(false);
            fclose(f1);
            fclose(f2);
            return;
        }
    }

    if (fscanf(f1, "%d", &num1) == 1 || fscanf(f2, "%d", &num2) == 1) {
        fprintf(stderr, "Files are of different lengths\n");
        assert(false);
    }


    fclose(f1);
    fclose(f2);
}


