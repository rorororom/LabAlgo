#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stackArrayVoid.h"

#define RIGHT 1
#define ERROR 0

const float  UP_COEFF = 2;

struct Stack* Stack_ctr(size_t size, size_t element_size) {
    struct Stack* stack = (struct Stack*) calloc(1, sizeof(struct Stack));
    assert(stack);

    void* data          = calloc(size, element_size);
    assert(data);

    stack->size = 0;
    stack->capacity = size;
    stack->data = data;

    return stack;
}

int Push(struct Stack* stack, void* buffer, size_t size) {
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

int TopStack(struct Stack* stack, void* buffer) {
    assert(stack);
    assert(buffer);

    void* value = stack->data[stack->size - 1];

    if (stack->size == 0) {
        return ERROR;
    } else {
        void* value = stack->data[stack->size - 1];
        memcpy(buffer, value, sizeof(value));
    }

}

int Pop(struct Stack* stack) {
    assert(stack);

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
        stack->capacity = 1;
    }
    else {
        stack->capacity = new_capacity;
    }

    void** data      = stack->data;
    void** temp      = (void**)realloc(data, stack->capacity * sizeof(void*));

    assert(temp);

    stack->data = temp;
}

struct Stack* Stack_dtr(struct Stack* stack) {
    assert(stack);

    for (int i = 0; i < stack->size; i++) {
        free(stack->data[i]);
    }

    free(stack->data);
    free(stack);

    return NULL;
}
