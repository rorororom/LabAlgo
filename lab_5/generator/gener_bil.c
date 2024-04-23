#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_random_numbers(int *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 1000000 + 1;
    }
}

int main() {
    int size = 1000000;
    int *random_numbers = (int*)malloc(size * sizeof(int));

    srand(time(NULL));

    generate_random_numbers(random_numbers, size);

    for (int i = 0; i < size; i++) {
        printf("%d\n", random_numbers[i]);
    }

    free(random_numbers);

    return 0;
}
