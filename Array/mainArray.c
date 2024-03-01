#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "stackArrayVoid.h"
#include "mainArray.h"
#include "../log.h"

const char value           = 'a';
const size_t sizeForStack = 1e2;

void Test1() {
    clock_t start_time, end_time;
    double cpu_time_used = 0;

    int cntC = 1e6;
    int ans = 0;

    struct Stack* stack = Stack_ctr(sizeForStack);
    assert(stack);

    start_time = clock();
    while (cntC >= 1e5) {
        for (int i = 0; i < cntC; i++) {
            ans = Push(stack, value);
            if (ans == 0)
                fprintf(LOG_FILE, "элемент не был добавлен\n");
        }
        cntC /= 2;
        for(int i = 0; i < cntC; i++) {
            ans = Pop(stack);
            if (ans == 0)
                fprintf(LOG_FILE, "элемент не был удален\n");
        }

        cntC += cntC / 2;
        for(int i = 0; i < cntC; i++) {
            ans = Push(stack, value);
            if (ans == 0)
                fprintf(LOG_FILE, "элемент не был добавлен\n");
        }
    }

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    fprintf(LOG_FILE, "Время выполнения программы \"Test1 for stack in array\": %f секунд\n", cpu_time_used);

    Stack_dtr(stack);
}

//Первый запуск: 0.046055 секунд
//Второй запуск: 0.044092 секунд
//Третий запуск: 0.045024 секунд
//Среднее время: 0.045057 секунд

void Test2() {
    clock_t start_time, end_time;
    double cpu_time_used = 0;
    int ans = 0;

    struct Stack* stack = Stack_ctr(sizeForStack);
    assert(stack);
    start_time = clock();

    for (size_t i = 0; i < 1e6; i++) {
        ans = Push(stack, value);
        if (ans == 0)
            fprintf(LOG_FILE, "элемент не был добавлен\n");
    }

    for (size_t i = 0; i < 100; i++) {
        for (size_t j = 0; j < 1e4; j++) {
            ans = Pop(stack);
            if (ans == 0)
                fprintf(LOG_FILE, "элемент не был удален\n");
        }
    }

    for (size_t i = 0; i < 100; i++) {
        for (size_t j = 0; j < 1e4; j++) {
            ans = Push(stack, value);
            if (ans == 0)
                fprintf(LOG_FILE, "элемент не был добавлен\n");
        }
    }

    int cntC = 1e6;
    while (cntC >= 1e5) {
        for (int i = 0; i < cntC; i++) {
            ans = Push(stack, value);
            if (ans == 0)
                fprintf(LOG_FILE, "элемент не был добавлен\n");
        }
        cntC /= 2;
        for(int i = 0; i < cntC; i++) {
            ans = Pop(stack);
            if (ans == 0)
                fprintf(LOG_FILE, "элемент не был удален\n");
        }

        cntC += cntC / 2;
        for(int i = 0; i < cntC; i++) {
            ans = Push(stack, value);
            if (ans == 0)
                fprintf(LOG_FILE, "элемент не был добавлен\n");
        }
    }

    for (size_t i = 0; i < 100; i++) {
        for (size_t j = 0; j < 1e4; j++) {
            ans = Pop(stack);
            if (ans == 0)
                fprintf(LOG_FILE, "элемент не был удален\n");
        }
    }

    for (size_t i = 0; i < 100; i++) {
        for (size_t j = 0; j < 1e4; j++) {
            ans = Push(stack, value);
            if (ans == 0)
                fprintf(LOG_FILE, "элемент не был добавлен\n");
        }
    }

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    fprintf(LOG_FILE, "Время выполнения программы \"Test2 for stack in array\": %f секунд\n", cpu_time_used);

    Stack_dtr(stack);
}

// Первый запуск: 0.054606 секунд
// Второй запуск: 0.054672 секунд
// Третий запуск: 0.054729 секунд
// Среднее время: 0.054669 секунд


void Test3() {
    clock_t start_time, end_time;
    double cpu_time_used = 0;
    int ans = 0;

    struct Stack* stack = Stack_ctr(sizeForStack);
    assert(stack);

    for (size_t i = 0; i < 1e6; i++) {
        ans = Push(stack, value);
            if (ans == 0)
                fprintf(LOG_FILE, "элемент не был добавлен\n");
    }

    srand(time(NULL));

    start_time = clock();
    for (size_t i = 0; i < 1e6; i++) {
        int randomNumber = rand() % 2 + 1;
        if (randomNumber == 1) {
            ans = Push(stack, value);
            if (ans == 0)
                fprintf(LOG_FILE, "элемент не был добавлен\n");
        }
        else {
            ans = Pop(stack);
            if (ans == 0)
                fprintf(LOG_FILE, "элемент не был удален\n");
        }
    }

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    fprintf(LOG_FILE, "Время выполнения программы \"Test3 for stack in array\": %f секунд\n", cpu_time_used);

    Stack_dtr(stack);
}

// Первый запуск: 0.019376 секунд
// Второй запуск: 0.021874 секунд
// Третий запуск: 0.018992 секунд
// Среднее время: 0.020081 секунд

void Test4() {
    clock_t start_time, end_time;
    double cpu_time_used = 0;

    FILE *file;
    file = fopen("dataForGraph.txt", "w");

    if (file == NULL)
        printf("Ошибка открытия файла.\n");

    struct Stack* stack = Stack_ctr(sizeForStack);
    assert(stack);

    int ans = 0;
    start_time = clock();
    for (size_t i = 1; i < 1e6 + 1; i++) {
        ans = Push(stack, value);
        if (ans == 0)
            fprintf(LOG_FILE, "не запушился элемент\n");

        if (i % 1000 == 0) {
            end_time = clock();
            cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
            fprintf(file, "%zu %f\n", i, 1000 * cpu_time_used );
        }
    }

    fclose(file);

    Stack_dtr(stack);
}
