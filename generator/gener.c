#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEFAULT_SEED 42

void printUsage(char *programName) {
    fprintf(stderr, "Usage: %s <size> <limit>\n", programName);
}

int* generateRandomArray(int size, int limit) {
    int *random_array = (int *)malloc(size * sizeof(int));
    if (random_array == NULL) {
        fprintf(stderr, "Out of memory\n");
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        random_array[i] = rand() % (limit + 1);
    }

    return random_array;
}

void printArray(int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d\n", array[i]);
    }
}

int main(int argc, char *argv[]) {
    srand(DEFAULT_SEED);

    if (argc != 3) {
        printUsage(argv[0]);
        return 1;
    }

    int size = atoi(argv[1]), limit = atoi(argv[2]);

    if (size < 0 || limit < 0) {
        printf("Size and limit must be positive!\n");
        return 1;
    }

    int *random_array = generateRandomArray(size, limit);
    if (random_array == NULL) {
        return 1;
    }

    printArray(random_array, size);
    free(random_array);

    return 0;
}
