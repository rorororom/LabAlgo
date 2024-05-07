#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define SIZE 1000000
#define MAX_LENGTH 20
#define MODULE 1000

#include "../string/hash_func.h"

void count_collisions(char **strings, int collisions[], int (*hash_func)(char *)) {
    for (int i = 0; i < SIZE; i++) {
        int index = hash_func(strings[i]);
        assert(index >= 0 && index < MODULE); // Check that the index is within bounds
        collisions[index]++;
    }
}

void write_collisions_to_file(const char *filename, int collisions[]) {
    FILE *file = fopen(filename, "w");
    assert(file != NULL); // Check if file is opened successfully
    for (int i = 0; i < MODULE; i++) {
        fprintf(file, "%d %d\n", i, collisions[i]);
    }
    fclose(file);
}

char **initialize_strings(FILE *file) {
    char **strings = (char **)malloc(SIZE * sizeof(char *));
    assert(strings != NULL);

    for (int i = 0; i < SIZE; i++) {
        strings[i] = (char *)malloc((MAX_LENGTH + 1) * sizeof(char));
        assert(strings[i] != NULL);
    }

    char line[MAX_LENGTH + 2];
    int num_strings = 0;
    while (fgets(line, sizeof(line), file)) {
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
        strncpy(strings[num_strings], line, MAX_LENGTH);
        strings[num_strings][MAX_LENGTH] = '\0';
        num_strings++;
        if (num_strings >= SIZE) {
            break;
        }
    }

    return strings;
}

void free_strings(char **strings) {
    for (int i = 0; i < SIZE; i++) {
        free(strings[i]);
    }
    free(strings);
}

int main() {
    FILE *file = fopen("array_tests/string.in", "r");
    assert(file != NULL);

    char **strings = initialize_strings(file);

    int collisions_length[MODULE] = {0};
    int collisions_summ_letters[MODULE] = {0};
    int collisions_polynomial[MODULE] = {0};
    int collisions_crc32[MODULE] = {0};

    count_collisions(strings, collisions_length, hash_length);
    count_collisions(strings, collisions_summ_letters, hash_summ_letters);
    count_collisions(strings, collisions_polynomial, hash_polynomial);
    count_collisions(strings, collisions_crc32, hash_crc32);

    write_collisions_to_file("res/collisions_length_string.txt", collisions_length);
    write_collisions_to_file("res/collisions_summ_letters_string.txt", collisions_summ_letters);
    write_collisions_to_file("res/collisions_polynomial_string.txt", collisions_polynomial);
    write_collisions_to_file("res/collisions_crc32_string.txt", collisions_crc32);

    free_strings(strings);

    return 0;
}
