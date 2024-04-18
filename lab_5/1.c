#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hash_table/hash_table.h"
#include "unsigned_int/hash_func.h"

#define SIZE 1000000

int main() {
    srand(42);  // Устанавливаем seed для генератора случайных чисел

    unsigned int keys[SIZE];
    for (int i = 0; i < SIZE; i++) {
        keys[i] = rand();  // Генерируем случайные ключи
    }

    int collisions_remainder[1000] = {0};  // Массив для хранения коллизий для хэш-функции остатка от деления
    int collisions_bitwise[1000] = {0};    // Массив для хранения коллизий для хэш-функции битового представления
    int collisions_multiplication[1000] = {0};  // Массив для хранения коллизий для хэш-функции метода умножения

    clock_t start, end;
    double cpu_time_used;

    // Тестирование хэш-функции остатка от деления
    start = clock();
    for (int i = 0; i < SIZE; i++) {
        int index = hash_remainder(keys[i]);
        collisions_remainder[index]++;
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken by hash_remainder: %f seconds\n", cpu_time_used);

    // Тестирование хэш-функции битового представления
    start = clock();
    for (int i = 0; i < SIZE; i++) {
        int index = hash_bitwise(keys[i]);
        collisions_bitwise[index]++;
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken by hash_bitwise: %f seconds\n", cpu_time_used);

    // Тестирование хэш-функции метода умножения
    start = clock();
    for (int i = 0; i < SIZE; i++) {
        int index = hash_multiplication(keys[i]);
        collisions_multiplication[index]++;
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken by hash_multiplication: %f seconds\n", cpu_time_used);

    // Запись результатов в файлы
    FILE *file_remainder = fopen("res/collisions_remainder.txt", "w");
    for (int i = 0; i < 1000; i++) {
        fprintf(file_remainder, "%d %d\n", i, collisions_remainder[i]);
    }
    fclose(file_remainder);

    FILE *file_bitwise = fopen("res/collisions_bitwise.txt", "w");
    for (int i = 0; i < 1000; i++) {
        fprintf(file_bitwise, "%d %d\n", i, collisions_bitwise[i]);
    }
    fclose(file_bitwise);

    FILE *file_multiplication = fopen("res/collisions_multiplication.txt", "w");
    for (int i = 0; i < 1000; i++) {
        fprintf(file_multiplication, "%d %d\n", i, collisions_multiplication[i]);
    }
    fclose(file_multiplication);

    return 0;
}
