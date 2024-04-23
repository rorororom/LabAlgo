#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

// #define METHOD_CHAIN
#define OPEN_HASH

#ifdef METHOD_CHAIN
    #include "../implementation_hash_table/metod_chain.h"
#endif
#ifdef OPEN_HASH
    #include "../implementation_hash_table/open_hash.h"
    #endif

#define INIT_CAPACITY 10000
#define SIZE_TESTS    1000000

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

void InserKeysFromFile(int* data, struct HashTable* ht, int method) {
    assert(data);
    assert(ht);

#ifdef OPEN_HASH
    for (size_t i = 0; i < SIZE_TESTS; i++) {
        // printf("%d ", i);
        if (method == LINEAR)
            HT_InsertLinear(data[i], ht);
        else if (method == SQUARE)
            HT_InsertSquare(data[i], ht);
        else
            HT_InsertTwoHash(data[i], ht);
    }
#endif

#ifdef METHOD_CHAIN
    for (size_t i = 0; i < SIZE_TESTS; i++) {
        HT_CH_Insert(data[i], ht);
    }
#endif
}

#ifdef OPEN_HASH
double MeasureInsertionTime(int* data, struct HashTable* ht, int method) {
    assert(data);
    assert(ht);

    clock_t start = clock();
    InserKeysFromFile(data, ht, method);
    clock_t end = clock();

    return ((double) (end - start)) / CLOCKS_PER_SEC;
}
#endif

#ifdef METHOD_CHAIN
double MeasureInsertionTime(int* data, struct HashTable* ht) {
    assert(data);
    assert(ht);

    clock_t start = clock();
    InserKeysFromFile(data, ht, 0);
    clock_t end = clock();

    return ((double) (end - start)) / CLOCKS_PER_SEC;
}
#endif

int* ReadDataFromFile(const char* filename) {
    FILE* data_file = OpenFile(filename, "r");

    int* data = (int*)calloc(SIZE_TESTS, sizeof(int));
    assert(data);

    for (size_t i = 0; i < SIZE_TESTS; i++) {
        int read_result = fscanf(data_file, "%d", &data[i]);
        if (read_result != 1) {
            if (feof(data_file)) {
                break;
            } else {
                printf("Error reading from data file.\n");
                exit(1);
            }
        }
    }

    CloseFile(data_file);
    return data;
}

int main() {
    FILE* results_file = OpenFile("open_hash_twohash.txt", "w");
    int* data = ReadDataFromFile("../arr_teste/coll.txt");

    float load_factor = 0.1;
    float cnt = 1.0;
    while (load_factor < cnt) {
#ifdef OPEN_HASH
        struct HashTable* ht = HT_Create(TWO_HASH, (int)(SIZE_TESTS / load_factor));
        double time_taken = MeasureInsertionTime(data, ht, LINEAR);
#endif

#ifdef METHOD_CHAIN
        struct HashTable* ht = HT_CH_Create((int)(SIZE_TESTS / load_factor));
        double time_taken = MeasureInsertionTime(data, ht);
#endif

        WriteResults(results_file, load_factor, time_taken);

#ifdef OPEN_HASH
        HT_Destroy(ht);
#endif
#ifdef METHOD_CHAIN
        HT_CH_Destroy(ht);
#endif
        load_factor += 0.05;
    }

    CloseFile(results_file);
    free(data);

    return 0;
}

