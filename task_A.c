#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int Elem_t;
typedef int Status_t;

const size_t CAPACITY        = 16;
const size_t SIZE_FOR_BUFFER = 100;
const float  UP_COEFF        = 2;
const float  DOWN_COEFF      = 0.25;

struct Stack {
    Elem_t* data;
    size_t  capacity;
    size_t  size;
};

typedef enum {
    RIGHT = 0,
    ERROR = 1,
    EXIT
} Status;

typedef enum {
    STACK_EMPTY = 0,
    STACK_NOT_EMPTY = 1
} StackStatus;

char*         ReadCommand(FILE* input);
int           InterpretCommand(struct Stack* stack, FILE* input, FILE* output);

/**
 * @brief Создает новый стек и возвращает указатель на него.
 *
 * @param initial_capacity Начальная емкость стека.
 * @return Указатель на новый стек или NULL, если не удалось выделить память.
 */
struct Stack* StackCtr(size_t initial_capacity);

/**
 * @brief Освобождает память, занятую стеком.
 *
 * @param stack Указатель на стек.
 */
void StackDtr(struct Stack* stack);

/**
 * @brief Удаляет последний элемент из стека.
 *
 * @param stack Указатель на стек.
 * @return RIGHT в случае успеха, ERROR если стек пуст.
 */
Status_t PopStack(struct Stack* stack);

/**
 * @brief Добавляет новый элемент в стек.
 *
 * @param stack Указатель на стек.
 * @param value Значение для добавления в стек.
 * @return RIGHT в случае успеха, ERROR если не удалось добавить элемент.
 */
Status_t PushStack(struct Stack* stack, Elem_t value);

/**
 * @brief Устанавливает новую емкость для стека.
 *
 * @param stack Указатель на стек.
 * @param new_capacity Новая емкость стека.
 * @return RIGHT в случае успеха, ERROR если не удалось перевыделить память.
 */
Status_t StackRealloc(struct Stack *stack, size_t new_capacity);

/**
 * @brief Очищает стек, освобождает выделенную память и создает новый пустой стек с начальной емкостью CAPACITY.
 *
 * @param stack Указатель на стек, который нужно очистить.
 */
void ClearStack(struct Stack* stack);

/**
 * @brief Проверяет, пуст ли стек.
 *
 * @param stack Указатель на стек.
 * @return STACK_EMPTY если стек пуст, STACK_NOT_EMPTY если стек не пуст.
 */
StackStatus StackEmpty(const struct Stack* stack);

/**
 * @brief Возвращает текущий размер стека.
 *
 * @param stack Указатель на стек.
 * @return Размер стека.
 */
Elem_t StackSize(const struct Stack* stack);

Status_t      CommandStackTop (const struct Stack* stack);
void          CommandStackPop(struct Stack* stack, FILE* output);
Status_t      CommandStackPush(struct Stack* stack, FILE* input, FILE* output);

//===========================================================
//===================== Main Function =======================
//===========================================================

int main() {
    struct Stack* stack = StackCtr(CAPACITY);

    FILE* output = stdout;
    FILE* input  = stdin;

    char* command = NULL;

    while (1) {
        int res = InterpretCommand(stack, input, output);
        if (res == ERROR || res == EXIT) {
            break;
        }
    }

    StackDtr(stack);
    return 0;
}

//===========================================================
//================== Stack Functions =======================
//===========================================================

struct Stack* StackCtr(size_t initial_capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (stack == NULL) {
        return NULL;
    }

    stack->data = malloc(initial_capacity * sizeof(int));
    if (stack->data == NULL) {
        free(stack);
        return NULL;
    }

    stack->size = 0;
    stack->capacity = initial_capacity;

    return stack;
}

void ClearStack(struct Stack* stack) {
    assert(stack);

    StackDtr(stack);
    stack = StackCtr(CAPACITY);
}

Status_t PushStack(struct Stack* stack, Elem_t value) {
    assert(stack);
    if (stack->size >= stack->capacity) {
        Status_t status = StackRealloc(stack, stack->capacity * UP_COEFF);
        if (status == ERROR) {
            return ERROR;
        }
    }

    if (stack->size   >= stack->capacity) {
        return ERROR;
    }

    stack->data[stack->size++] = value;
    return RIGHT;
}

Status_t StackRealloc(struct Stack *stack, size_t new_capacity) {
    assert(stack);

    if (new_capacity == 0) {
        new_capacity = CAPACITY;
    }

    Elem_t* new_data = (Elem_t*)realloc(stack->data, new_capacity * sizeof(Elem_t));

    if (new_data != NULL) {
        stack->data = new_data;
        stack->capacity = new_capacity;
    } else {
        return ERROR;
    }

    return RIGHT;
}

Status_t PopStack(struct Stack* stack) {
    assert(stack);

    if (stack->size <=      stack->capacity / (UP_COEFF * UP_COEFF)) {
        Status_t status = StackRealloc(stack, stack->capacity * DOWN_COEFF);
        if (status == ERROR) {
            return ERROR;
        }
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

StackStatus StackEmpty(const struct Stack* stack) {
    assert(stack);

    if (stack->size > 0)
        return STACK_EMPTY;

    return STACK_NOT_EMPTY;
}

Elem_t StackSize(const struct Stack* stack) {
    assert(stack);

    return stack->size;
}

//=========================================================
//=================== Command Handlers ===================
//=========================================================

Status_t CommandStackTop(const struct Stack* stack) {
    assert(stack);

    if (StackSize(stack) > 0) {
        return RIGHT;
    } else {
        return ERROR;
    }
}

void CommandStackPop(struct Stack* stack, FILE* output) {
    assert(stack);
    assert(output);

    if (StackEmpty(stack)) {
        fprintf(output, "error\n");
    } else {
        int num = PopStack(stack);
        fprintf(output, "%d\n", num);
    }
}

Status_t CommandStackPush(struct Stack* stack, FILE* input, FILE* output) {
    assert(stack);
    assert(input);
    assert(output);

    int value = 0;
    int result = fscanf(input, "%d", &value);

    if (result != 1) {
        fprintf(output, "Error: Input is not a valid integer.\n");
        return ERROR;
    }

    int status = PushStack(stack, value);
    if (status) {
        return ERROR;
    } else {
        return RIGHT;
    }
}

//===========================================================
//================== Utility Functions ======================
//===========================================================

char* ReadCommand(FILE* input) {
    static char buffer[SIZE_FOR_BUFFER];
    if (fscanf(input, "%99s", buffer) != 1) {
        fprintf(stderr, "Error: Failed to read input.\n");
        return NULL;
    }

    return buffer;
}

int InterpretCommand(struct Stack* stack, FILE* input, FILE* output) {
    char* command = ReadCommand(input);
    if (command == NULL) {
        return ERROR;
    }

    if (strcmp(command, "push") == 0) {
        Status_t status = CommandStackPush(stack, input, output);
        if (status) {
            fprintf(output, "error\n");
        } else {
            fprintf(output, "ok\n");
        }
    } else if (strcmp(command, "pop") == 0) {
        CommandStackPop(stack, output);
    } else if (strcmp(command, "size") == 0) {
        fprintf(output, "%d\n", StackSize(stack));
    } else if (strcmp(command, "back") == 0) {
        int status = CommandStackTop(stack);
        if (status) {
            fprintf(output, "error\n");
        } else {
            fprintf(output, "%d\n", stack->data[stack->size - 1]);
        }
    } else if (strcmp(command, "clear") == 0) {
        ClearStack(stack);
        fprintf(output, "ok\n");
    } else if (strcmp(command, "exit") == 0) {
        fprintf(output, "bye\n");
        return EXIT;
    } else {
        return ERROR;
    }

    return RIGHT;
}
