#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILE_COUNT 10

int randomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

void createTestFile(int count) {
    char filename[50];
    sprintf(filename, "../array/test_%d.txt", count); // Создаем имя файла

    FILE *file = fopen(filename, "w"); // Открываем файл для записи

    if (file == NULL) {
        printf("Ошибка при создании файла %s\n", filename);
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d\n", randomInt(1, 1000000)); // Записываем случайное число в файл
    }

    fclose(file);
}

int main() {
    srand(time(NULL));

    for (int i = 1; i <= FILE_COUNT; i++) {
        int count = i * 100000;
        createTestFile(count);
        printf("Создан файл test_%d.txt с %d числами\n", count, count);
    }

    return 0;
}
