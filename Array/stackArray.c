#include <stdio.h>
#include <stdlib.h>

#include "stackArray.h"

const float  UP_KOEF   = 2;
const float  DOWN_KOEF = 0.5;

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
    if (stack->size >= stack->capacity) {
        float koef_capacity = UP_KOEF;
        StackRealloc(stack, koef_capacity);
    }

    if (stack == NULL || stack->data == NULL) {
        return 0;
    }
    if (stack->size   >= stack->capacity) {
        return 0;
    }

    stack->data[stack->size++] = value;
    return 1;
}

Elem_t Top(struct Stack* stack) {
    return stack->data[stack->size - 1];
}

int Pop(struct Stack* stack) {
    if (stack->size < (stack->capacity) / UP_KOEF) {
        float koef_capacity = DOWN_KOEF;
        StackRealloc(stack, koef_capacity);
    }

    if (stack->size > 0) {
        stack->data[stack->size - 1] = 0;
        stack->size--;
        return 1;
    }
    return 0;
}

static void StackRealloc(struct Stack *stack, float koef_capacity) {
    stack->capacity *= koef_capacity;

    stack->data      = (Elem_t*)realloc(stack->data, (stack->capacity + 2) * sizeof(Elem_t));
}

struct Stack* Stack_dtr(struct Stack* stack) {
    free(stack->data);
    free(stack);
    return NULL;
}
