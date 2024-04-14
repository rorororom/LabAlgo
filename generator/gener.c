#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main(int argc, char *argv[]) {
    srand(42);
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <size> <limit>\n", argv[0]);
        return 1;
    }

    int size = atoi(argv[1]);
    int limit = atoi(argv[2]);

    if (size < 0 || limit < 0) {
        printf("Size and limit must be positive!\n");
        return 1;
    }

    int *random_array = (int *)malloc(size * sizeof(int));
    if (random_array == NULL) {
        fprintf(stderr, "Out of memory\n");
        return 1;
    }

    for (int i = 0; i < size; i++) {
        random_array[i] = rand() % (limit + 1);
    }

    for (int i = 0; i < size; i++) {
        printf("%d\n", random_array[i]);
    }

    free(random_array);

    return 0;
}

