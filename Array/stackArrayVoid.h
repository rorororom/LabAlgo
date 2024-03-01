#ifndef STACK_ARRAY_VOID
#define STACK_ARRAY_VOID

#include <stdlib.h>

typedef int Elem_t;

struct Stack{
    void** data;
    size_t  size;
    float  capacity;
};

int  Pop (struct Stack* stack);
int  Push(struct Stack* stack, void* buffer);
void Top (struct Stack* stack, void* buffer);

struct Stack* Stack_ctr   (size_t size, size_t element_size);
struct Stack* Stack_dtr   (struct Stack* stack);
static void   StackRealloc(struct Stack *stack, float koef_capacity);

#endif
