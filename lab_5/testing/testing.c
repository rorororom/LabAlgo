#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "testing.h"

#include "../hash_table/hash_table.h"

float CallingSortAndRecordingTime(value_type* arr, size_t size, hash_function heapFunc, const char* nameFileForTime) {
    struct HashTable* ht = HT_Create();

    for (size_t i = 0; i < size; i++) {     // size = 1000;
        HT_Add(arr[i], ht);
    }

    char filename_ans[256];
    snprintf(filename_ans, sizeof(filename_ans), "%s/%s.txt", "colizion", nameFileForTime);
    FILE* output_file = fopen(filename_ans, "w");
    if (output_file == NULL) {
        printf("Error opening output file: %s\n", filename_ans);
    }

    for (size_t i = 0; i < size; i++) {
        fprintf(filename_ans, "%d %d", i, ht->array[i].length);
    }

    fclose(output_file);
}

void testing(const char *testFolder, hash_function hashFunc,
             const char *nameFileForTime, size_t size) {
    char filename[256];
    int* arr = (int*)calloc(size, sizeof(int));

    assert(arr);

    snprintf(filename, sizeof(filename), "%s/%zu.in", testFolder, size);
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening input file: %s\n", filename);
    }

    for (size_t q = 0; q < size; q++) {
        if (fscanf(file, "%d", &arr[q]) != 1) {
            printf("Error reading from file: %s\n", filename);
            fclose(file);
            continue;
        }
    }

    fclose(file);

    float time = CallingSortAndRecordingTime(arr, 1000, hashFunc, nameFileForTime);

    free(arr);
}
