#ifndef STACK_LIST
#define STACK_LIST

#include <stdlib.h>

typedef int Elem_t;
typedef int Status_t;

struct Node {
    Elem_t data;
    struct Node* prev;
};

struct Stack{
    struct Node*  top;
    size_t size;
};

Status_t StackTop  (struct Stack* stack, Elem_t* buffer);
Status_t PopStack  (struct Stack* stack);
Status_t PushStack (struct Stack* stack, Elem_t value);

struct Stack* StackCtr();
struct Stack* StackDtr(struct Stack* stack);

#endif
