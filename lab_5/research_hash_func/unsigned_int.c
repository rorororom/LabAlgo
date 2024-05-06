#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "../unsigned_int/hash_func.h"

#define SIZE 1000000

void test_hash_function(unsigned int* keys, int* collisions, int (*hash_function)(unsigned int)) {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    for (int i = 0; i < SIZE; i++) {
        int index = hash_function(keys[i]);
        assert(index >= 0 && index < 1000); // Check that the index is within bounds
        collisions[index]++;
    }
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken by hash function: %f seconds\n", cpu_time_used);
}

void write_collisions_to_file(const char *filename, int collisions[]) {
    FILE *file = fopen(filename, "w");
    assert(file != NULL); // Check if file is opened successfully
    for (int i = 0; i < 1000; i++) {
        fprintf(file, "%d %d\n", i, collisions[i]);
    }

    fclose(file);
}

int main() {
    srand(42);

    unsigned int keys[SIZE];
    FILE *file = fopen("./array_tests/unsigned_int.txt", "r");
    assert(file != NULL); // Check if file is opened successfully
    for (int i = 0; i < SIZE; i++) {
        if (fscanf(file, "%u", &keys[i]) != 1) {
            printf("Error reading number from file.\n");
            fclose(file);
            return 1;
        }
    }
    fclose(file);

    int collisions_remainder[1000] = {0};
    int collisions_bitwise[1000] = {0};
    int collisions_multiplication[1000] = {0};

    test_hash_function(keys, collisions_remainder, hash_remainder);
    test_hash_function(keys, collisions_bitwise, hash_bitwise);
    test_hash_function(keys, collisions_multiplication, HashMultiplication);

    write_collisions_to_file("res/collisions_remainder.txt", collisions_remainder);
    write_collisions_to_file("res/collisions_bitwise.txt", collisions_bitwise);
    write_collisions_to_file("res/collisions_multiplication.txt", collisions_multiplication);

    return 0;
}
