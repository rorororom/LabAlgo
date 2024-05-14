#ifndef STACK_ARRAY_VOID
#define STACK_ARRAY_VOID

#include <stdlib.h>

typedef int Elem_t;
typedef int Status_t;

struct Stack{
    void** data;
    size_t  size;
    float  capacity;
};

Status_t PopStack     (struct Stack* stack);
Status_t PushStack    (struct Stack* stack, void* buffer, size_t size);
Status_t TopStack(struct Stack* stack, void* buffer);

struct Stack* StackCtr   (size_t size, size_t element_size);
struct Stack* StackDtr   (struct Stack* stack);
static void   StackRealloc(struct Stack *stack, size_t new_capacity);

#endif
