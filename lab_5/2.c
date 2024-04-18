#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000000
#define MAX_LENGTH 20
#define MODULE 1000

#include "string/hash_func.h"

int main() {
    FILE *file = fopen("array_tests/string.in", "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла.\n");
        return 1;
    }

    // Создаем массив строк максимальной длины 20
    char **strings = (char **)malloc(SIZE * sizeof(char *));
    if (strings == NULL) {
        printf("Ошибка при выделении памяти.\n");
        fclose(file);
        return 1;
    }

    // Считываем строки из файла
    for (int i = 0; i < SIZE; i++) {
        strings[i] = (char *)malloc((MAX_LENGTH + 1) * sizeof(char));
        if (strings[i] == NULL) {
            printf("Ошибка при выделении памяти.\n");
            // Освобождаем память выделенную для строк
            for (int j = 0; j < i; j++) {
                free(strings[j]);
            }
            free(strings);
            fclose(file);
            return 1;
        }
    }

    char line[MAX_LENGTH + 2]; // +2 для учета символа новой строки и символа конца строки
    int num_strings = 0;
    while (fgets(line, sizeof(line), file)) {
        // Удаляем символ новой строки, если он есть
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
        // Копируем строку в массив
        strncpy(strings[num_strings], line, MAX_LENGTH);
        strings[num_strings][MAX_LENGTH] = '\0'; // Убеждаемся, что строка заканчивается нулевым символом
        num_strings++;
        // Проверяем, не превышено ли максимальное количество строк
        if (num_strings >= SIZE) {
            break;
        }
    }

    // Массивы для хранения коллизий
    int collisions_length[MODULE] = {0};
    int collisions_summ_letters[MODULE] = {0};
    int collisions_polynomial[MODULE] = {0};
    int collisions_crc32[MODULE] = {0};

    // Тестирование хэш-функции по длине строки
    for (int i = 0; i < SIZE; i++) {
        int index = hash_length(strings[i]);
        collisions_length[index]++;
    }

    // Тестирование хэш-функции суммы кодов символов
    for (int i = 0; i < SIZE; i++) {
        int index = hash_summ_letters(strings[i]);
        collisions_summ_letters[index]++;
    }

    // Тестирование полиномиальной хэш-функции
    for (int i = 0; i < SIZE; i++) {
        int index = hash_polynomial(strings[i]);
        collisions_polynomial[index]++;
    }

    // Тестирование хэш-функции CRC32
    for (int i = 0; i < SIZE; i++) {
        int index = hash_crc32((unsigned char*)strings[i], strlen(strings[i]));
        collisions_crc32[index]++;
    }

    // Запись результатов в файлы
    FILE *file_length = fopen("res/collisions_length_string.txt", "w");
    for (int i = 0; i < MODULE; i++) {
        fprintf(file_length, "%d %d\n", i, collisions_length[i]);
    }
    fclose(file_length);

    FILE *file_summ_letters = fopen("res/collisions_summ_letters_string.txt", "w");
    for (int i = 0; i < MODULE; i++) {
        fprintf(file_summ_letters, "%d %d\n", i, collisions_summ_letters[i]);
    }
    fclose(file_summ_letters);

    FILE *file_polynomial = fopen("res/collisions_polynomial_string.txt", "w");
    for (int i = 0; i < MODULE; i++) {
        fprintf(file_polynomial, "%d %d\n", i, collisions_polynomial[i]);
    }
    fclose(file_polynomial);

    FILE *file_crc32 = fopen("res/collisions_crc32_string.txt", "w");
    for (int i = 0; i < MODULE; i++) {
        fprintf(file_crc32, "%d %d\n", i, collisions_crc32[i]);
    }
    fclose(file_crc32);

    // Освобождаем память, выделенную для строк
    for (int i = 0; i < SIZE; i++) {
        free(strings[i]);
    }

    return 0;
}
