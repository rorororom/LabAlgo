#ifndef STACK_LIST_VOID
#define STACK_LIST_VOID

#include <stdlib.h>

typedef int Elem_t;

struct Node {
    void* data;
    struct Node* prev;
};

struct Stack{
    struct Node*  top;
    size_t size;
};

int Top(struct Stack* stack, Elem_t* buffer);
int  Pop (struct Stack* stack);
int Push(struct Stack* stack, void* buffer);

struct Stack* Stack_ctr(size_t size, size_t element_size);
struct Stack* Stack_dtr(struct Stack* stack);

#endif
