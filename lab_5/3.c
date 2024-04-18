#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000000
#define MODULE 1000

#include "float/hash_func.h"

int main() {
    FILE *file = fopen("array_tests/float.in", "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла.\n");
        return 1;
    }

    // Создаем массив чисел типа float
    float *numbers = (float *)malloc(SIZE * sizeof(float));
    if (numbers == NULL) {
        printf("Ошибка при выделении памяти.\n");
        fclose(file);
        return 1;
    }

    // Считываем числа из файла
    int num_numbers = 0;
    while (fscanf(file, "%f", &numbers[num_numbers]) == 1) {
        num_numbers++;
        // Проверяем, не превышено ли максимальное количество чисел
        if (num_numbers >= SIZE) {
            break;
        }
    }

    // Массивы для хранения коллизий
    int collisions_int_representation[MODULE] = {0};
    int collisions_mantissa[MODULE] = {0};
    int collisions_exponent[MODULE] = {0};
    int collisions_mantissa_times_exponent[MODULE] = {0};

    // Тестирование хэш-функции для целочисленного представления числа
    for (int i = 0; i < num_numbers; i++) {
        int index = hash_int_representation(numbers[i]);
        collisions_int_representation[index]++;
    }

    // Тестирование хэш-функции для мантиссы числа
    for (int i = 0; i < num_numbers; i++) {
        int index = hash_mantissa(*(unsigned int*)&numbers[i], MODULE);
        collisions_mantissa[index]++;
    }

    // Тестирование хэш-функции для экспоненты числа
    for (int i = 0; i < num_numbers; i++) {
        int index = hash_exponent(*(unsigned int*)&numbers[i], MODULE);
        collisions_exponent[index]++;
    }

    // Тестирование хэш-функции для произведения мантиссы и экспоненты числа
    for (int i = 0; i < num_numbers; i++) {
        int index = hash_mantissa_times_exponent(*(unsigned int*)&numbers[i], MODULE);
        collisions_mantissa_times_exponent[index]++;
    }

    // Запись результатов в файлы
    FILE *file_int_representation = fopen("res/collisions_bit_representation_float.txt", "w");
    for (int i = 0; i < MODULE; i++) {
        fprintf(file_int_representation, "%d %d\n", i, collisions_int_representation[i]);
    }
    fclose(file_int_representation);

    FILE *file_mantissa = fopen("res/collisions_mantissa_float.txt", "w");
    for (int i = 0; i < MODULE; i++) {
        fprintf(file_mantissa, "%d %d\n", i, collisions_mantissa[i]);
    }
    fclose(file_mantissa);

    FILE *file_exponent = fopen("res/collisions_exponent_float.txt", "w");
    for (int i = 0; i < MODULE; i++) {
        fprintf(file_exponent, "%d %d\n", i, collisions_exponent[i]);
    }
    fclose(file_exponent);

    FILE *file_mantissa_times_exponent = fopen("res/collisions_mantissa_times_exponent_float.txt", "w");
    for (int i = 0; i < MODULE; i++) {
        fprintf(file_mantissa_times_exponent, "%d %d\n", i, collisions_mantissa_times_exponent[i]);
    }
    fclose(file_mantissa_times_exponent);

    // Освобождаем память, выделенную для массива чисел
    free(numbers);

    fclose(file);
    return 0;
}
