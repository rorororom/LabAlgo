#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define CNT_ELEMENT 100000
#define MAX_NUMBER 1000000

void generate_numbers(int array[], int size) {
    srand(time(NULL));

    bool generated[MAX_NUMBER] = {false}; // Массив флагов для отслеживания сгенерированных чисел

    for (int i = 0; i < size; ++i) {
        int num;
        do {
            num = rand() % MAX_NUMBER; // Генерация случайного числа
        } while (generated[num]); // Повторять, пока не будет сгенерировано уникальное число
        array[i] = num;
        generated[num] = true; // Пометить число как сгенерированное
    }
}

int main() {
    int numbers[CNT_ELEMENT];
    generate_numbers(numbers, CNT_ELEMENT);
    for (int i = 0; i < CNT_ELEMENT; ++i) {
        printf("%d\n", numbers[i]);
    }
    printf("\n");

    return 0;
}
