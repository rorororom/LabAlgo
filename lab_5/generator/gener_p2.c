#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TEST_STEP 10000
#define MAX_TEST_SIZE 1000000

typedef struct {
    char op;
    int key;
} Operation;

Operation* generate_operations_p2(int size) {
    Operation *operations = malloc(size * sizeof(Operation));
    for (int i = 0; i < size; i++) {
        operations[i].op = "+-?"[rand() % 3];
        operations[i].key = rand() % (size * 10);
    }
    return operations;
}

Operation* generate_operations_p3(int size) {
    Operation *operations = malloc(size * sizeof(Operation));
    for (int i = 0; i < size; i++) {
        int rand_num = rand() % 100; // Генерируем случайное число от 0 до 99

        // Вставка (вероятность 0.5)
        if (rand_num < 50) {
            operations[i].op = '+';
        }
        // Удаление (вероятность 0.25)
        else if (rand_num < 75) {
            operations[i].op = '-';
        }
        // Поиск (вероятность 0.25)
        else {
            operations[i].op = '?';
        }

        operations[i].key = rand() % (size * 10);
    }
    return operations;
}


void save_operations_to_file(const char *filename, Operation *operations, int size) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        fprintf(file, "%c %d\n", operations[i].op, operations[i].key);
    }
    fclose(file);
}

int main() {
    srand(time(NULL));

    int test_sizes_count = 1000000;
    for (int i = 10000; i <= 1000000; i += 10000) {
        int test_size = i;
        Operation *operations = generate_operations_p3(test_size);
        char filename[50];

        snprintf(filename, sizeof(filename), "../arr_tests/test2_%d.txt", i);

        save_operations_to_file(filename, operations, test_size); // Вызов функции для записи операций в файл

        free(operations);
    }

    return 0;
}
