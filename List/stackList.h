#ifndef STACK_LIST
#define STACK_LIST

#include <stdlib.h>

typedef int Elem_t;

struct Node {
    Elem_t data;
    struct Node* prev;
};

struct Stack{
    struct Node*  top;
    size_t size;
};

void Top (struct Stack* stack, Elem_t* buffer);
int  Pop (struct Stack* stack);
int  Push(struct Stack* stack, Elem_t value);

struct Stack* Stack_ctr();
struct Stack* Stack_dtr(struct Stack* stack);

#endif
