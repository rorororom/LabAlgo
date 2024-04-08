#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int Elem_t;
typedef int Status_t;

const int    SIZE          = 10;
const int    CAPACITY      = SIZE + 5;
const float  UP_COEFF      = 2;

struct Stack {
    Elem_t* data;
    int     capacity;
    int     size;
};

#define RIGHT 1
#define ERROR 0

char*         ReadCommand();
int           StackCheckSize  (struct Stack* stack);
void          InterpretCommand(struct Stack* stack, char* command)

struct Stack* StackCtr    (size_t size);
void          StackDtr(struct Stack* stack);
Status_t      PopStack    (struct Stack* stack);
Status_t      PushStack   (struct Stack* stack, Elem_t value);
void          StackRealloc(struct Stack *stack, size_t new_capacity);

void          CommandStackTop (struct Stack* stack);
void          CommandStackPop (struct Stack* stack);
void          CommandStackPush(struct Stack* stack);

//--------------------------------------------------------------------------------------

int main()
{
    struct Stack stack = {};
    StackCtr(CAPACITY);
    char* command = NULL;

    while (1) {
        command = ReadCommand();

        InterpretCommand(&stack, command);
        if (strcmp(command, "exit") == 0) {
            break;
        }
    }

    return 0;
    StackDtr(&stack);
}

void InterpretCommand(struct Stack* stack, char* command) {

    if (strcmp(command, "push")         == 0) {
        CommandStackPush(stack);

    } else if (strcmp(command, "pop")   == 0) {
        CommandStackPop(stack);

    } else if (strcmp(command, "size")  == 0) {
        printf("%d\n", stack->size);

    } else if (strcmp(command, "back")  == 0) {
        CommandStackTop(stack);

    } else if (strcmp(command, "exit")  == 0) {
        printf("bye\n");

    } else if (strcmp(command, "clear") == 0) {
        StackDtr(stack);
        StackCtr(CAPACITY);
        printf("ok\n");
    } else {
        abort();
    }
}

struct Stack* StackCtr(size_t size) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (stack == NULL) {
        return NULL;
    }

    stack->data = malloc(size * sizeof(int));
    if (stack->data == NULL) {
        free(stack);
        return NULL;
    }

    stack->size = 0;
    stack->capacity = size;

    return stack;
}

Status_t PushStack(struct Stack* stack, Elem_t value) {
    assert(stack);
    if (stack->size >= stack->capacity) {
        StackRealloc(stack, stack->capacity * UP_COEFF);
    }

    if (stack == NULL || stack->data == NULL) {
        return ERROR;
    }
    if (stack->size   >= stack->capacity) {
        return ERROR;
    }

    stack->data[stack->size++] = value;
    return RIGHT;
}

void StackRealloc(struct Stack *stack, size_t new_capacity) {
    assert(stack);

    if (new_capacity == 0) {
        new_capacity = 1;
    }

    Elem_t* new_data = (Elem_t*)realloc(stack->data, new_capacity * sizeof(Elem_t));

    if (new_data != NULL) {
        stack->data = new_data;
        stack->capacity = new_capacity;
    } else {
        fprintf(stderr, "Не удалось выделить память\n");
    }
}

Status_t PopStack(struct Stack* stack) {
    assert(stack);

    if (stack->size <=      stack->capacity / (UP_COEFF * UP_COEFF)) {
        StackRealloc(stack, stack->capacity / (UP_COEFF * UP_COEFF));
    }

    if (stack->size > 0) {
        stack->data[stack->size - 1] = 0;
        stack->size--;
        return RIGHT;
    }
    return ERROR;
}

void StackDtr(struct Stack* stack) {
    assert(stack);

    free(stack->data);
    free(stack);
}

void CommandStackTop(struct Stack* stack) {
    assert(stack);

    if (StackCheckSize(stack)) {
        printf("%d\n", stack->data[stack->size - 1]);

    } else {
        printf("error\n");
    }
}

void CommandStackPop(struct Stack* stack) {
    assert(stack);

    if (StackCheckSize(stack)) {
        int num = PopStack(stack);
        printf("%d\n", num);

    } else {
        printf("error\n");
    }
}

void CommandStackPush(struct Stack* stack) {
    assert(stack);

    int value = 0;
    int result = scanf("%d", &value);

    if (result != 1) {
        printf("Error: Input is not a valid integer.\n");
        return;
    }

    int res = PushStack(stack, value);
    printf("ok\n");
}

char* ReadCommand() {
    char* buffer = (char*)malloc(100 * sizeof(char));
    if (buffer == NULL) {
        printf("Error: Memory allocation failed.\n");
        return NULL;
    }

    if (scanf("%99s", buffer) != 1) {
        printf("Error: Failed to read input.\n");
        free(buffer);
        return NULL;
    }

    return buffer;
}

int StackCheckSize(struct Stack* stack) {
    assert(stack);

    return stack->size > 0;
}
