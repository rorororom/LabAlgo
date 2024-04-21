#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

#define NUMBERS_TO_READ 100000
#define SEARCH_ITERATIONS 10000000

// #include "../relizing_hash_table/open_hash.h"
#include "../implementation_hash_table/ideal_hash.h"
// #include "../relizing_hash_table/metod_chain.h"

void testing(struct arrHash2* ht) {

    for (int i = 0; i < SEARCH_ITERATIONS; i++) {
        int target = rand() % (NUMBERS_TO_READ * 10);
        bool result = search(ht, target);
    }

}

int main() {
    clock_t start, end;
    double cpu_time_used;

    FILE* file = fopen("../array_tests/p_last.txt", "r");
    if (file == NULL) {
        printf("Error opening input file: %s\n", file);
        return 1;
    }

    int* arr = (int*)calloc(SEARCH_ITERATIONS, sizeof(int));

    int key = 0;
    for (int i = 0; i < NUMBERS_TO_READ; i++) {
        if (fscanf(file, "%d", &key) != 1) {
            fprintf(stderr, "Error reading number from file\n");
            exit(EXIT_FAILURE);
        }
        arr[i] = key;
    }

    fclose(file);

    struct arrHash2* ht = (struct arrHash2*)calloc(SEARCH_ITERATIONS, sizeof(struct arrHash2));
    assert(ht);

    build_HT(arr, ht);

    start = clock();
    testing(ht);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f\n", cpu_time_used);

    return 0;
}

