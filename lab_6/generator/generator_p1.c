#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100000
#define ARRAY_SIZE_S 1000000

void generateNumbers(int* numbers) {
    srand(time(NULL));

    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        numbers[i] = rand() % (10000003);
    }
}

void generateNumbersSort(int* numbers) {
    for (size_t i = 0; i < ARRAY_SIZE_S; i++) {
        numbers[i] = i;
    }
}

int main() {
    int numbers[ARRAY_SIZE_S];

    generateNumbersSort(numbers);

    for (int i = 0; i < ARRAY_SIZE_S; ++i) {
        printf("%d\n", numbers[i]);
    }

    return 0;
}
