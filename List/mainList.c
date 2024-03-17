#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// #include "stackListVoid.h"
#include "stackList.h"
#include "../log.h"
#include "mainList.h"

#define ERROR 0

const int    VALUE              = 5;
const size_t FILE_WRITE_SIZE = 1000;
const size_t MILLISECONDS    = 1000;

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
            ans = Push(stack, VALUE);
            if (ans == ERROR)
                fprintf(LOG_FILE, "не удалось запушить элемент\n");
        }
        cntC /= 2;
        for(int i = 0; i < cntC; i++) {
            ans = Pop(stack);
            if (ans == ERROR)
                fprintf(LOG_FILE, "не удалось удалить элемент\n");
        }

        cntC += cntC / 2;
        for(int i = 0; i < cntC; i++) {
            ans = Push(stack, VALUE);
            if (ans == ERROR)
                fprintf(LOG_FILE, "не удалось запушить элемент\n");
        }
    }

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    fprintf(LOG_FILE, "Время выполнения программы \"Test1 for stack in list\": %f секунд\n", cpu_time_used);

    Stack_dtr(stack);
}

void Test2() {
    clock_t start_time, end_time;
    double cpu_time_used = 0;

    struct Stack* stack = Stack_ctr(1e6);
    assert(stack);

    start_time = clock();
    int ans = 0;

    for (size_t i = 0; i < 1e6; i++) {
        ans = Push(stack, VALUE);
        if (ans == ERROR)
            fprintf(LOG_FILE, "не удалось запушить элемент\n");
    }

    for (size_t i = 0; i < 100; i++) {
        for (size_t j = 0; j < 1e4; j++) {
            ans = Pop(stack);
            if (ans == ERROR)
                fprintf(LOG_FILE, "не удалось удалить элемент\n");
        }
    }

    for (size_t i = 0; i < 100; i++) {
        for (size_t j = 0; j < 1e4; j++) {
            ans = Push(stack, VALUE);
            if (ans == ERROR)
                fprintf(LOG_FILE, "не удалось запушить элемент\n");
        }
    }

    int cntC = 1e6;
    while (cntC >= 1e5) {
        for (int i = 0; i < cntC; i++) {
            ans = Push(stack, VALUE);
            if (ans == ERROR)
                fprintf(LOG_FILE, "не удалось запушить элемент\n");
        }
        cntC /= 2;
        for(int i = 0; i < cntC; i++) {
            ans = Pop(stack);
            if (ans == ERROR)
                fprintf(LOG_FILE, "не удалось удалить элемент\n");
        }

        cntC += cntC / 2;
        for(int i = 0; i < cntC; i++) {
            ans = Push(stack, VALUE);
            if (ans == ERROR)
                fprintf(LOG_FILE, "не удалось запушить элемент\n");
        }
    }

    for (size_t i = 0; i < 100; i++) {
        for (size_t j = 0; j < 1e4; j++) {
            ans = Pop(stack);
            if (ans == ERROR)
                fprintf(LOG_FILE, "не удалось удалить элемент\n");
        }
    }

    for (size_t i = 0; i < 100; i++) {
        for (size_t j = 0; j < 1e4; j++) {
            ans = Push(stack, VALUE);
            if (ans == ERROR)
                fprintf(LOG_FILE, "не удалось запушить элемент\n");
        }
    }

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    fprintf(LOG_FILE, "Время выполнения программы \"Test2 for stack in list\": %f секунд\n", cpu_time_used);

    Stack_dtr(stack);
}

void Test3() {
    clock_t start_time, end_time;
    double cpu_time_used = 0;
    int ans = 0;

    struct Stack* stack = Stack_ctr(1e7);
    assert(stack);

    for (size_t i = 0; i < 1e6; i++) {
        ans = Push(stack, VALUE);
        if (ans == ERROR)
                fprintf(LOG_FILE, "не удалось запушить элемент\n");
    }

    srand(time(NULL));

    start_time = clock();
    for (size_t i = 0; i < 1e6; i++) {
        int randomNumber = rand() % 2 + 1;
        if (randomNumber == 1) {
            ans = Push(stack, VALUE);
            if (ans == ERROR)
                fprintf(LOG_FILE, "не удалось запушить элемент\n");
        }
        else {
            ans = Pop(stack);
            if (ans == ERROR)
                fprintf(LOG_FILE, "не удалось удалить элемент\n");
        }
    }

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    fprintf(LOG_FILE, "Время выполнения программы \"Test3 for stack in list\": %f секунд\n", cpu_time_used);

    Stack_dtr(stack);
}

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
        ans = Push(stack, VALUE);
        if (ans == ERROR)
            fprintf(LOG_FILE, "не запушилось в стек\n");
        if (i % FILE_WRITE_SIZE == 0) {
            end_time = clock();
            cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
            fprintf(file, "%zu %f\n", i, cpu_time_used * MILLISECONDS);
        }
    }

    fclose(file);
    Stack_dtr(stack);
}
