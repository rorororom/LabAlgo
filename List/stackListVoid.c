#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stackListVoid.h"

#define RIGHT 1
#define ERROR 0

struct Stack* StackCtr(size_t size, size_t element_size) {
    struct Stack* stack = (struct Stack*)calloc(1, sizeof(struct Stack));
    assert(stack);

    stack->top = NULL;
    stack->size = ERROR;
    return stack;
}

Status_t PushStack(struct Stack* stack, void* buffer, size_t size) {
    assert(stack);
    assert(buffer);

    struct Node* new_elem = (struct Node*)calloc(1, sizeof(struct Node));
    assert(new_elem);

    void* new = calloc(1, sizeof(size));
    assert(new);

    void* newNode = memcpy(new, buffer, sizeof(size));
    assert(newNode);

    new_elem->data = newNode;
    new_elem->prev = stack->top;

    stack->top = new_elem;
    stack->size++;

    return RIGHT;
}

Status_t StackTop(struct Stack* stack, Elem_t* buffer) {
    assert(stack);
    assert(buffer);

    if (stack->top == NULL) {
        *buffer = ERROR;
        return ERROR;
    }

    *buffer = stack->top->data; // Копируем данные из вершины стека в буфер

    return RIGHT;
}

Status_t PopStack(struct Stack* stack) {
    assert(stack);
    if (stack->top == NULL) {
        return ERROR;
    }

    struct Node* temp = stack->top->prev;
    free(stack->top->data);
    free(stack->top);

    stack->top = temp;
    stack->size--;

    return RIGHT;
}

struct Stack* StackDtr(struct Stack* stack) {
    assert(stack);
    size_t size = stack->size;

    while (size--)
        PopStack(stack);

    free(stack);

    return NULL;
}
