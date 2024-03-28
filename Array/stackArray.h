#ifndef STACK_ARRAY
#define STACK_ARRAY

#include <stdlib.h>

typedef int Elem_t;
typedef int Status_t;
struct Stack{
    Elem_t* data;
    size_t  size;
    float  capacity;
};

Status_t PopStack     (struct Stack* stack);
Status_t PushStack    (struct Stack* stack, Elem_t value);
Status_t TopStack     (struct Stack* stack, Elem_t* buffer);

struct Stack* StackCtr   (size_t size);
struct Stack* StackDtr   (struct Stack* stack);
static void   StackRealloc(struct Stack *stack, size_t new_capacity);

#endif
