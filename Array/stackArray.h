#ifndef STACK_ARRAY
#define STACK_ARRAY

#include <stdlib.h>

typedef int Elem_t;

struct Stack{
    Elem_t* data;
    size_t  size;
    float  capacity;
};

int    Pop     (struct Stack* stack);
int    Push    (struct Stack* stack, Elem_t value);
Elem_t TopStack(struct Stack* stack);

struct Stack* Stack_ctr   (size_t size);
struct Stack* Stack_dtr   (struct Stack* stack);
static void   StackRealloc(struct Stack *stack, size_t new_capacity);

#endif
