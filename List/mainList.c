#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// #include "stackListVoid.h"
#include "stackList.h"
#include "../log.h"
#include "mainList.h"

const int value = 5;

void Test1() {
    clock_t start_time, end_time;
    double cpu_time_used = 0;

    int cntC = 1e6;

    struct Stack* stack = Stack_ctr();
    assert(stack);
    int ans = 0;

    start_time = clock();
    while (cntC >= 1e5) {
        for (int i = 0; i < cntC; i++) {
            ans = Push(stack, value);
            if (ans == 0)
                fprintf(LOG_FILE, "не удалось запушить элемент\n");
        }
        cntC /= 2;
        for(int i = 0; i < cntC; i++) {
            ans = Pop(stack);
            if (ans == 0)
                fprintf(LOG_FILE, "не удалось удалить элемент\n");
        }

        cntC += cntC / 2;
        for(int i = 0; i < cntC; i++) {
            ans = Push(stack, value);
            if (ans == 0)
                fprintf(LOG_FILE, "не удалось запушить элемент\n");
        }
    }

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    fprintf(LOG_FILE, "Время выполнения программы \"Test1 for stack in list\": %f секунд\n", cpu_time_used);

    Stack_dtr(stack);
}

//Первый запуск: 0.489526 секунд
//Второй запуск: 0.460030 секунд
//Третий запуск: 0.470482 секунд
//Среднее время: 0.473346 секунд

void Test2() {
    clock_t start_time, end_time;
    double cpu_time_used = 0;

    struct Stack* stack = Stack_ctr(1e6);
    assert(stack);

    start_time = clock();
    int ans = 0;

    for (size_t i = 0; i < 1e6; i++) {
        ans = Push(stack, value);
        if (ans == 0)
            fprintf(LOG_FILE, "не удалось запушить элемент\n");
    }

    for (size_t i = 0; i < 100; i++) {
        for (size_t j = 0; j < 1e4; j++) {
            ans = Pop(stack);
            if (ans == 0)
                fprintf(LOG_FILE, "не удалось удалить элемент\n");
        }
    }

    for (size_t i = 0; i < 100; i++) {
        for (size_t j = 0; j < 1e4; j++) {
            ans = Push(stack, value);
            if (ans == 0)
                fprintf(LOG_FILE, "не удалось запушить элемент\n");
        }
    }

    int cntC = 1e6;
    while (cntC >= 1e5) {
        for (int i = 0; i < cntC; i++) {
            ans = Push(stack, value);
            if (ans == 0)
                fprintf(LOG_FILE, "не удалось запушить элемент\n");
        }
        cntC /= 2;
        for(int i = 0; i < cntC; i++) {
            ans = Pop(stack);
            if (ans == 0)
                fprintf(LOG_FILE, "не удалось удалить элемент\n");
        }

        cntC += cntC / 2;
        for(int i = 0; i < cntC; i++) {
            ans = Push(stack, value);
            if (ans == 0)
                fprintf(LOG_FILE, "не удалось запушить элемент\n");
        }
    }

    for (size_t i = 0; i < 100; i++) {
        for (size_t j = 0; j < 1e4; j++) {
            ans = Pop(stack);
            if (ans == 0)
                fprintf(LOG_FILE, "не удалось удалить элемент\n");
        }
    }

    for (size_t i = 0; i < 100; i++) {
        for (size_t j = 0; j < 1e4; j++) {
            ans = Push(stack, value);
            if (ans == 0)
                fprintf(LOG_FILE, "не удалось запушить элемент\n");
        }
    }

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    fprintf(LOG_FILE, "Время выполнения программы \"Test2 for stack in list\": %f секунд\n", cpu_time_used);

    Stack_dtr(stack);
}

//Первый запуск: 0.760849 секунд
//Второй запуск: 0.766572 секунд
//Третий запуск: 0.750747 секунд
//Среднее время: 0.759389 секунд

void Test3() {
    clock_t start_time, end_time;
    double cpu_time_used = 0;
    int ans = 0;

    struct Stack* stack = Stack_ctr(1e7);
    assert(stack);

    for (size_t i = 0; i < 1e6; i++) {
        ans = Push(stack, value);
        if (ans == 0)
                fprintf(LOG_FILE, "не удалось запушить элемент\n");
    }

    srand(time(NULL)); // Инициализация генератора псевдослучайных чисел

    start_time = clock();
    for (size_t i = 0; i < 1e6; i++) {
        int randomNumber = rand() % 2 + 1;
        if (randomNumber == 1) {
            ans = Push(stack, value);
            if (ans == 0)
                fprintf(LOG_FILE, "не удалось запушить элемент\n");
        }
        else {
            ans = Pop(stack);
            if (ans == 0)
                fprintf(LOG_FILE, "не удалось удалить элемент\n");
        }
    }

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    fprintf(LOG_FILE, "Время выполнения программы \"Test3 for stack in list\": %f секунд\n", cpu_time_used);

    Stack_dtr(stack);
}

//Первый запуск: 0.065311 секунд
//Второй запуск: 0.067212 секунд
//Третий запуск: 0.063152 секунд
//Среднее время: 0.065225 секунд

void Test4() {
    clock_t start_time, end_time;
    double cpu_time_used = 0;

    FILE *file;
    file = fopen("dataForGraph1.txt", "w");

    if (file == NULL) {
        printf("Ошибка открытия файла.\n");
    }

    struct Stack* stack = Stack_ctr(1e6);
    assert(stack);

    int ans = 0;
    start_time = clock();
    for (size_t i = 1; i < 1e6 + 1; i++) {
        ans = Push(stack, value);
        if (ans == 0)
            fprintf(LOG_FILE, "не запушилось в стек\n");
        if (i % 1000 == 0) {
            end_time = clock();
            cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
            fprintf(file, "%zu %f\n", i, cpu_time_used * 1000);
        }
    }

    fclose(file);
    Stack_dtr(stack);
}
