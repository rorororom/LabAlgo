#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "stackArrayVoid.h"
#include "mainArray.h"
#include "../log.h"

#define ERROR 0

const char   VALUE           = 'a';
const size_t SIZE_FOR_STACK  = 1e2;
const size_t FILE_WRITE_SIZE = 1000;
const size_t ELEMENT_SIZE    = 1;
const size_t MILLISECONDS    = 1000;

void Test1() {
    clock_t start_time, end_time;
    double cpu_time_used = 0;

    int cntC = 1e6;
    int ans = 0;

    struct Stack* stack = Stack_ctr(SIZE_FOR_STACK, ELEMENT_SIZE);
    assert(stack);

    start_time = clock();
    while (cntC >= 1e5) {
        for (int i = 0; i < cntC; i++) {
             ans = Push(stack, &VALUE, sizeof(VALUE));
            if (ans == ERROR)
                fprintf(LOG_FILE, "элемент не был добавлен\n");
        }
        cntC /= 2;
        for(int i = 0; i < cntC; i++) {
            int ans = Pop(stack);
            if (ans == ERROR)
                fprintf(LOG_FILE, "элемент не был удален\n");
        }

        cntC += cntC / 2;
        for(int i = 0; i < cntC; i++) {
             ans = Push(stack, &VALUE, sizeof(VALUE));
            if (ans == ERROR)
                fprintf(LOG_FILE, "элемент не был добавлен\n");
        }
    }

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    fprintf(LOG_FILE, "Время выполнения программы \"Test1 for stack in array\": %f секунд\n", cpu_time_used);

    Stack_dtr(stack);
}

void Test2() {
    clock_t start_time, end_time;
    double cpu_time_used = 0;
    int ans = 0;

    struct Stack* stack = Stack_ctr(SIZE_FOR_STACK, ELEMENT_SIZE);
    assert(stack);
    start_time = clock();

    for (size_t i = 0; i < 1e6; i++) {
         ans = Push(stack, &VALUE, sizeof(VALUE));
        if (ans == ERROR)
            fprintf(LOG_FILE, "элемент не был добавлен\n");
    }

    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 1; j++) {
            ans = Pop(stack);
            if (ans == ERROR)
                fprintf(LOG_FILE, "элемент не был удален\n");
        }
    }

    for (size_t i = 0; i < 100; i++) {
        for (size_t j = 0; j < 1e4; j++) {
             ans = Push(stack, &VALUE, sizeof(VALUE));
            if (ans == ERROR)
                fprintf(LOG_FILE, "элемент не был добавлен\n");
        }
    }

    int cntC = 1e6;
    while (cntC >= 1e5) {
        for (int i = 0; i < cntC; i++) {
             ans = Push(stack, &VALUE, sizeof(VALUE));
            if (ans == ERROR)
                fprintf(LOG_FILE, "элемент не был добавлен\n");
        }
        cntC /= 2;
        for(int i = 0; i < cntC; i++) {
            ans = Pop(stack);
            if (ans == ERROR)
                fprintf(LOG_FILE, "элемент не был удален\n");
        }

        cntC += cntC / 2;
        for(int i = 0; i < cntC; i++) {
             ans = Push(stack, &VALUE, sizeof(VALUE));
            if (ans == ERROR)
                fprintf(LOG_FILE, "элемент не был добавлен\n");
        }
    }

    for (size_t i = 0; i < 100; i++) {
        for (size_t j = 0; j < 1e4; j++) {
            ans = Pop(stack);
            if (ans == ERROR)
                fprintf(LOG_FILE, "элемент не был удален\n");
        }
    }

    for (size_t i = 0; i < 100; i++) {
        for (size_t j = 0; j < 1e4; j++) {
             ans = Push(stack, &VALUE, sizeof(VALUE));
            if (ans == ERROR)
                fprintf(LOG_FILE, "элемент не был добавлен\n");
        }
    }

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    fprintf(LOG_FILE, "Время выполнения программы \"Test2 for stack in array\": %f секунд\n", cpu_time_used);

    Stack_dtr(stack);
}

void Test3() {
    clock_t start_time, end_time;
    double cpu_time_used = 0;
    int ans = 0;

    struct Stack* stack = Stack_ctr(SIZE_FOR_STACK, ELEMENT_SIZE);
    assert(stack);

    for (size_t i = 0; i < 1e6; i++) {
         ans = Push(stack, &VALUE, sizeof(VALUE));
            if (ans == ERROR)
                fprintf(LOG_FILE, "элемент не был добавлен\n");
    }

    srand(time(NULL));

    start_time = clock();
    for (size_t i = 0; i < 1e6; i++) {
        int randomNumber = rand() % 2 + 1;
        if (randomNumber == 1) {
             ans = Push(stack, &VALUE, sizeof(VALUE));
            if (ans == ERROR)
                fprintf(LOG_FILE, "элемент не был добавлен\n");
        }
        else {
            ans = Pop(stack);
            if (ans == ERROR)
                fprintf(LOG_FILE, "элемент не был удален\n");
        }
    }

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    fprintf(LOG_FILE, "Время выполнения программы \"Test3 for stack in array\": %f секунд\n", cpu_time_used);

    Stack_dtr(stack);
}

void Test4() {
    clock_t start_time, end_time;
    double cpu_time_used = 0;

    FILE *file;
    file = fopen("dataForGraph.txt", "w");

    if (file == NULL)
        printf("Ошибка открытия файла.\n");

    struct Stack* stack = Stack_ctr(SIZE_FOR_STACK, ELEMENT_SIZE);
    assert(stack);

    int ans = 0;
    start_time = clock();
    for (size_t i = 1; i < 1e6 + 1; i++) {
         ans = Push(stack, &VALUE, sizeof(VALUE));
        if (ans == ERROR)
            fprintf(LOG_FILE, "не запушился элемент\n");

        if (i % FILE_WRITE_SIZE == 0) {
            end_time = clock();
            cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
            fprintf(file, "%zu %f\n", i, MILLISECONDS * cpu_time_used );
        }
    }

    fclose(file);

    Stack_dtr(stack);
}
