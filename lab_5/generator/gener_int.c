#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define CNT_ELEMENT 100000
#define MAX_NUMBER 10000000

void generate_numbers(int array[], int size) {
    for (int i = 0; i < CNT_ELEMENT; i++) {
        printf("%d\n", i);
    }
}

void generate_random_number(int min, int max) {
    for (int i = 0; i < MAX_NUMBER; i++) {
        printf("%d\n", min + rand() / (RAND_MAX / (max - min + 1) + 1));
    }
}


int main() {
    int numbers[CNT_ELEMENT];
    //generate_numbers(numbers, CNT_ELEMENT);
    generate_random_number(0, 300000);

    return 0;
}
