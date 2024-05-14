#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main(int argc, char *argv[]) {
    srand(clock());
    if (argc != 3) {
        fprintf(stderr, "чет не то %s\n", argv[0]);
        return 1;
    }

    int size = atoi(argv[1]);
    int limit = atoi(argv[2]);

    if (size < 0 || limit < 0) {
        printf("числа должны быть положительными!!!!!!\n");
        return 1;
    }

    int *random_array = (int *)malloc(size * sizeof(int));
    if (random_array == NULL) {
        fprintf(stderr, "памяти нет\n");
        return 1;
    }

    for (int i = 0; i < size; i++) {
        printf("%d\n", rand() % (limit + 1));
    }

    return 0;
}
