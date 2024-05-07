#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SIZE 1000000
#define MODULE 1000

#include "../float/hash_func.h"

void read_numbers(FILE *file, float *numbers, int *num_numbers) {
    *num_numbers = 0;
    while (fscanf(file, "%f", &numbers[*num_numbers]) == 1) {
        (*num_numbers)++;
        if (*num_numbers >= SIZE) {
            break;
        }
    }
}

void test_hash_functions(float *numbers, int num_numbers, int *collisions, int (*hash_function)(float, int)) {
    for (int i = 0; i < num_numbers; i++) {
        int index = hash_function(numbers[i], MODULE);
        collisions[index]++;
    }
}

void write_collisions_to_file(const char *filename, int *collisions) {
    FILE *file = fopen(filename, "w");
    assert(file != NULL); 

    for (int i = 0; i < MODULE; i++) {
        fprintf(file, "%d %d\n", i, collisions[i]);
    }

    fclose(file);
}

int main() {
    FILE *file = fopen("array_tests/float.in", "r");
    assert(file != NULL);

    float *numbers = (float *)malloc(SIZE * sizeof(float));
    assert(numbers != NULL);

    int num_numbers;
    read_numbers(file, numbers, &num_numbers);

    int collisions_int_representation[MODULE] = {0};
    int collisions_bitwise[MODULE] = {0};
    int collisions_mantissa[MODULE] = {0};
    int collisions_exponent[MODULE] = {0};
    int collisions_mantissa_times_exponent[MODULE] = {0};

    test_hash_functions(numbers, num_numbers, collisions_int_representation, hash_int_representation);
    test_hash_functions(numbers, num_numbers, collisions_bitwise, hash_float_bitwise);
    test_hash_functions(numbers, num_numbers, collisions_mantissa, hash_mantissa);
    test_hash_functions(numbers, num_numbers, collisions_exponent, hash_exponent);
    test_hash_functions(numbers, num_numbers, collisions_mantissa_times_exponent, hash_mantissa_times_exponent);

    write_collisions_to_file("res/collisions_int_representation_float.txt", collisions_int_representation);
    write_collisions_to_file("res/collisions_bitwise_float.txt", collisions_bitwise);
    write_collisions_to_file("res/collisions_mantissa_float.txt", collisions_mantissa);
    write_collisions_to_file("res/collisions_exponent_float.txt", collisions_exponent);
    write_collisions_to_file("res/collisions_mantissa_times_exponent_float.txt", collisions_mantissa_times_exponent);

    free(numbers);
    fclose(file);

    return 0;
}
