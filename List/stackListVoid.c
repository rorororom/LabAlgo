#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stackListVoid.h"

struct Stack* Stack_ctr(size_t size, size_t element_size) {
    struct Stack* stack = (struct Stack*)calloc(1, sizeof(struct Stack));
    assert(stack);

    stack->top = NULL;
    stack->size = 0;
    return stack;
}

int Push(struct Stack* stack, void* buffer) {
    assert(stack);
    assert(buffer);
    struct Node* new_elem = (struct Node*)calloc(1, sizeof(struct Node));

    void* new = calloc(1, sizeof(*buffer));
    assert(new);

    void* newNode = memcpy(new, buffer, sizeof(*buffer));
    assert(newNode);

    new_elem->data = newNode;
    new_elem->prev = stack->top;

    stack->top = new_elem;
    stack->size++;

    return 1;
}

int Top(struct Stack* stack, Elem_t* buffer) {
    assert(stack);
    assert(buffer);

    if (stack->top == NULL) {
        abort();
    }

    void* data = stack->top->data;

    memcpy(buffer, data, sizeof(data));

    return 0;
}

int Pop(struct Stack* stack) {
    assert(stack);
    if (stack->top == NULL) {
        return 0;
    }

    struct Node* temp = stack->top->prev;
    free(stack->top->data);
    free(stack->top);

    stack->top = temp;
    stack->size--;

    return 1;
}

struct Stack* Stack_dtr(struct Stack* stack) {
    assert(stack);
    size_t size = stack->size;

    while (size--)
        Pop(stack);

    free(stack);

    return NULL;
}
