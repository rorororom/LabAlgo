#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

#define NUMBERS_TO_READ 100000
#define SEARCH_ITERATIONS 10000000

#define IDEAL_HASH
// #define OPEN_HASH
// #define METHOD_CHAIN

#ifdef OPEN_HASH
#include "../implementation_hash_table/open_hash.h"
#endif
#ifdef IDEAL_HASH
#include "../implementation_hash_table/ideal_hash.h"
#endif
#ifdef METHOD_CHAIN
#include "../implementation_hash_table/metod_chain.h"
#endif

void testing(struct HashTable* ht, int* arr_search) {

    for (int i = 0; i < SEARCH_ITERATIONS; i++) {
#ifdef IDEAL_HASH
        bool result = HT_ID_Search(ht, arr_search[i]);
#endif
#ifdef OPEN_HASH
        int result = HT_SearchQuadratic(arr_search[i], ht);
#endif
#ifdef METHOD_CHAIN
        bool result = HT_CH_Search(arr_search[i], ht);
#endif
    }

}

int GenerSizeHT(int N) {
    int power = 1;
    while (power < N) {
        power <<= 1;
    }
    return power;
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    FILE* file = fopen("../arr_tests/int.txt", "r");
    if (file == NULL) {
        printf("Error opening input file");
        return 1;
    }

    int* arr = (int*)calloc(NUMBERS_TO_READ, sizeof(int));

    int key = 0;
    for (int i = 0; i < NUMBERS_TO_READ; i++) {
        if (fscanf(file, "%d", &key) != 1) {
            fprintf(stderr, "Error reading number from file\n");
            exit(EXIT_FAILURE);
        }
        arr[i] = key;
    }

    fclose(file);

    FILE* file_search = fopen("../arr_tests/int1.txt", "r");
    if (file_search == NULL) {
        printf("Error opening input file");
        return 1;
    }

    int* arr_search = (int*)calloc(SEARCH_ITERATIONS, sizeof(int));

    key = 0;
    for (int i = 0; i < SEARCH_ITERATIONS; i++) {
        if (fscanf(file_search, "%d", &key) != 1) {
            fprintf(stderr, "Error reading number from file\n");
            exit(EXIT_FAILURE);
        }
        arr_search[i] = key;
    }

    fclose(file_search);

#ifdef IDEAL_HASH
    int size = NearPowTwo(NUMBERS_TO_READ);

    HashTable hashTable;
    hashTable.size = size;
    hashTable.table = (HashTableLevelTwo*)malloc(size * sizeof(HashTableLevelTwo));
    assert(hashTable.table);

    BuildHashTable(&hashTable, arr, NUMBERS_TO_READ);
#endif
#ifdef OPEN_HASH
    int size = GenerSizeHT(NUMBERS_TO_READ);
    struct HashTable* hashTable = HT_Create(SQUARE, size);
    assert(hashTable);

    for (int i = 0; i < NUMBERS_TO_READ; i++) {
        HT_InsertSquare(arr[i], hashTable);
    }
#endif
#ifdef METHOD_CHAIN
    int size = GenerSizeHT(NUMBERS_TO_READ);
    struct HashTable* hashTable = HT_CH_Create(size);
    for (int i = 0; i < NUMBERS_TO_READ; i++) {
        HT_CH_Insert(arr[i], hashTable);
    }
#endif

    start = clock();
    testing(&hashTable, arr_search);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f\n", cpu_time_used);

    return 0;
}

