#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stackArrayVoid.h"

#define RIGHT 1
#define ERROR 0

const float  UP_COEFF = 2;

struct Stack* StackCtr(size_t size, size_t element_size) {
    struct Stack* stack = (struct Stack*) calloc(1, sizeof(struct Stack));
    assert(stack);

    void* data          = calloc(size, element_size);
    assert(data);

    stack->size = 0;
    stack->capacity = size;
    stack->data = data;

    return stack;
}

Status_t PushStack(struct Stack* stack, void* buffer, size_t size) {
    assert(stack);
    assert(buffer);

    if (stack->size >= stack->capacity) {
        StackRealloc(stack, stack->capacity * UP_COEFF);
    }

    if (stack == NULL || stack->data == NULL) {
        return ERROR;
    }
    if (stack->size   >= stack->capacity) {
        return ERROR;
    }

    void* data = calloc(1, sizeof(size));
    assert(data);
    data = memcpy(data, buffer, sizeof(size));
    assert(data);

    stack->data[stack->size] = data;
    stack->size++;
    return RIGHT;
}

Status_t TopStack(struct Stack* stack, void* buffer) {
    assert(stack);
    assert(buffer);

    void* value = stack->data[stack->size - 1];

    if (stack->size == 0) {
        return ERROR;
    } else {
        void* value = stack->data[stack->size - 1];
        memcpy(buffer, value, sizeof(value));
        return RIGHT;
    }

}

Status_t PopStack(struct Stack* stack) {
    assert(stack);

    if (stack->size <= stack->capacity / (UP_COEFF * UP_COEFF)) {
        StackRealloc(stack, stack->capacity / (UP_COEFF * UP_COEFF));
    }

    if (stack->size == 0) {
        return ERROR;
    } else {
        void* elem = stack->data[--(stack->size)];
        free(elem);
        stack->data[stack->size] = NULL;
        return RIGHT;
    }

    return ERROR;
}

static void StackRealloc(struct Stack *stack, size_t new_capacity) {
    assert(stack);

    if (new_capacity == 0) {
        new_capacity = 1;
    }

    void** temp = (void**)realloc(stack->data, new_capacity * sizeof(void*));

    if (temp != NULL) {
        stack->data = temp;
        stack->capacity = new_capacity;
    } else {
        fprintf(stderr, "Не удалось выделить память\n");
    }
}

struct Stack* StackDtr(struct Stack* stack) {
    assert(stack);

    for (int i = 0; i < stack->size; i++) {
        free(stack->data[i]);
    }

    free(stack->data);
    free(stack);

    return NULL;
}
