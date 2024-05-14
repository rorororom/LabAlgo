#ifndef STACK_LIST_VOID
#define STACK_LIST_VOID

#include <stdlib.h>

typedef int Elem_t;
typedef int Status_t;

struct Node {
    void* data;
    struct Node* prev;
};

struct Stack{
    struct Node*  top;
    size_t size;
};

Status_t StackTop(struct Stack* stack, Elem_t* buffer);
Status_t PopStack     (struct Stack* stack);
Status_t PushStack    (struct Stack* stack, void* buffer, size_t size);

struct Stack* StackCtr(size_t size, size_t element_size);
struct Stack* StackDtr(struct Stack* stack);

#endif
