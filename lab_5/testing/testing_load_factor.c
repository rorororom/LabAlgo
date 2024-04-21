#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "../implementation_hash_table/open_hash.h"

#define INIT_CAPACITY 10000

void WriteResults(FILE* file, float load_factor, double time_taken) {
    assert(file);

    fprintf(file, "%.2f %.6f\n", load_factor, time_taken);
}

FILE* OpenFile(const char* filename, const char* mode) {
    FILE* file = fopen(filename, mode);
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }
    return file;
}

void CloseFile(FILE* file) {
    fclose(file);
}

void InserKeysFromFile(FILE* data_file, struct HashTable* ht) {
    assert(data_file);
    assert(ht);

    int key = 0;
    for (size_t i = 0; i < 1000000; i++) {
        int read_result = fscanf(data_file, "%d", &key);
        if (read_result != 1) {
            if (feof(data_file)) {
                break;
            } else {
                printf("Error reading from data file.\n");
                exit(1);
            }
        }
        HT_InsertSquare(key, ht);
    }
}

double MeasureInsertionTime(FILE* data_file, struct HashTable* ht) {
    assert(data_file);
    assert(ht);

    clock_t start = clock();
    InserKeysFromFile(data_file, ht);
    clock_t end = clock();

    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

int main() {
    FILE* results_file = OpenFile("open_hash_line.txt", "w");
    FILE* data_file    = OpenFile("data.txt", "r");

    float load_factor = 1;
    struct HashTable* ht = HT_Create("line", INIT_CAPACITY);
    printf("len =%d\n", ht->length);

    double time_taken = MeasureInsertionTime(data_file, ht);

    WriteResults(results_file, load_factor, time_taken);
    HT_Destroy(ht);

    CloseFile(results_file);
    CloseFile(data_file);

    return 0;
}
