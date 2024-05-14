#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "stackList.h"

#define RIGHT 1
#define ERROR 0

struct Stack* StackCtr() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (stack == NULL) {
        return NULL;
    }
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

Status_t PushStack(struct Stack* stack, Elem_t value) {
    assert(stack);

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        return ERROR;
    }

    newNode->data = value;
    newNode->prev = stack->top;
    stack->top = newNode;
    stack->size++;

    return RIGHT;
}

Status_t StackTop(struct Stack* stack, Elem_t* buffer) {
    assert(stack);

    if (stack->top == NULL) {
        *buffer = ERROR;
        return ERROR;
    }

    *buffer = stack->top->data;
    return RIGHT;
}

Status_t PopStack(struct Stack* stack) {
    assert(stack);

    if (stack->top == NULL) {
        return 0;
    }
    if (stack->size == 1) {
        struct Node* temp = stack->top;
        free(temp);
        stack->top = NULL;
    } else {
        struct Node* temp = stack->top;
        stack->top = stack->top->prev;
        free(temp);
        stack->size--;
    }
    return RIGHT;
}

struct Stack* StackDtr(struct Stack* stack) {
    assert(stack);
    while (stack->top != NULL) {
        PopStack(stack);
    }
    free(stack);
    return NULL;
}
