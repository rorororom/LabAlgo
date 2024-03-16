#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "stackArray.h"

#define RIGHT 1
#define ERROR 0

const float  UP_COEFF = 2;

struct Stack* Stack_ctr(size_t size) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (stack == NULL) {
        return NULL;
    }

    stack->data = malloc(size * sizeof(int));
    if (stack->data == NULL) {
        free(stack);
        return NULL;
    }

    stack->size = 0;
    stack->capacity = size;

    return stack;
}

int Push(struct Stack* stack, Elem_t value) {
    assert(stack);
    if (stack->size >= stack->capacity) {
        StackRealloc(stack, stack->capacity * UP_COEFF);
    }

    if (stack == NULL || stack->data == NULL) {
        return ERROR;
    }
    if (stack->size   >= stack->capacity) {
        return ERROR;
    }

    stack->data[stack->size++] = value;
    return RIGHT;
}

Elem_t TopStack(struct Stack* stack) {
    assert(stack);

    if (stack->size == 0)
        return ERROR;
    else
        return stack->data[stack->size - 1];
}

int Pop(struct Stack* stack) {
    assert(stack);

    if (stack->size > 0) {
        stack->data[stack->size - 1] = 0;
        stack->size--;
        return RIGHT;
    }
    return ERROR;
}

static void StackRealloc(struct Stack *stack, size_t new_capacity) {
    assert(stack);

    if (new_capacity == 0) {
        stack->capacity = 1;
    } else {
        stack->capacity = new_capacity;
    }

    stack->data      = (Elem_t*)realloc(stack->data, stack->capacity * sizeof(Elem_t));
    assert(stack->data);
}

struct Stack* Stack_dtr(struct Stack* stack) {
    assert(stack);

    free(stack->data);
    free(stack);
    return NULL;
}
