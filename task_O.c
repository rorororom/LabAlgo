#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long long int value;
    size_t index;
    size_t index_Insert;
} Node;

typedef struct {
    Node* heapArray;
    Node** indexArray;
    size_t capacity;
    size_t size;
} MinHeap;

enum STATUS {
    OK = 0,
    ERROR = 1,
    EXIT
};

typedef int status_t;

const size_t SIZE_FOR_BUFFER = 100;

/**
 * @brief Инициализирует кучу с заданной начальной емкостью.
 *
 * @param capacity Начальная емкость кучи.
 * @return Указатель на новую кучу или NULL, если не удалось выделить память.
 */
MinHeap* InitHeap(int capacity);

/**
 * @brief Освобождает память, занятую кучей.
 *
 * @param heap Указатель на кучу, которую нужно уничтожить.
 */
void DestroyHeap(MinHeap* heap);

/**
 * @brief Выполняет восходящую коррекцию кучи, начиная с заданного индекса.
 *
 * @param heap Указатель на кучу.
 * @param index Индекс элемента, с которого начинается коррекция.
 */
void SiftUp(MinHeap* heap, int index);

/**
 * @brief Выполняет нисходящую коррекцию кучи, начиная с заданного индекса.
 *
 * @param heap Указатель на кучу.
 * @param index Индекс элемента, с которого начинается коррекция.
 */
void SiftDown(MinHeap* heap, size_t index);

/**
 * @brief Вставляет новый элемент в кучу.
 *
 * @param heap Указатель на кучу.
 * @param value Значение для вставки.
 * @param i Индекс вставки.
 * @return OK в случае успеха, ERROR если не удалось вставить элемент.
 */
status_t Insert(MinHeap* heap, int value, size_t i);

/**
 * @brief Извлекает минимальный элемент из кучи.
 *
 * @param heap Указатель на кучу.
 */
void ExtractMin(MinHeap* heap);

/**
 * @brief Проверяет, есть ли в куче минимальный элемент.
 *
 * @param heap Указатель на кучу.
 * @return OK если минимальный элемент есть, ERROR если куча пуста.
 */
status_t GetMin(MinHeap* heap);

/**
 * @brief Уменьшает значение ключа элемента в куче по заданному индексу.
 *
 * @param heap Указатель на кучу.
 * @param index Индекс элемента.
 * @param delta Величина уменьшения ключа.
 */
void DecreaseKey(MinHeap* heap, int index, int delta);

/**
 * @brief Обменивает значения двух элементов кучи по их индексам.
 *
 * @param heap Указатель на кучу.
 * @param index1 Индекс первого элемента.
 * @param index2 Индекс второго элемента.
 */
void Swap(MinHeap* heap, int index1, int index2);

/**
 * @brief Возвращает индекс родительского элемента для заданного индекса.
 *
 * @param index Индекс элемента.
 * @return Индекс родительского элемента.
 */
size_t ParentIndex(int index);

/**
 * @brief Возвращает индекс левого потомка для заданного индекса.
 *
 * @param index Индекс элемента.
 * @return Индекс левого потомка.
 */
size_t LeftChildIndex(int index);

/**
 * @brief Возвращает индекс правого потомка для заданного индекса.
 *
 * @param index Индекс элемента.
 * @return Индекс правого потомка.
 */
size_t RightChildIndex(int index);

/**
 * @brief Читает следующую команду из входного потока.
 *
 * @param input Входной поток.
 * @param buffer Буфер для сохранения команды.
 * @return Указатель на считанную команду или NULL в случае ошибки.
 */
char* ReadCommand(FILE* input, char* buffer);

/**
 * @brief Интерпретирует команду и выполняет соответствующие действия над кучей.
 *
 * @param heap Указатель на кучу.
 * @param index Индекс операции (номер команды).
 * @param input Входной поток.
 * @param output Выходной поток.
 * @param buffer Буфер для чтения команды.
 * @return OK в случае успешного выполнения, ERROR при возникновении ошибки, EXIT если выполнение программы должно завершиться.
 */
status_t InterpretCommand(MinHeap* heap, int index, FILE* input, FILE* output, char* buffer);

//===========================================================
//===================== Main Function =======================
//===========================================================

int main() {
    FILE* output = stdout;
    FILE* input  = stdin;

    int N = 0;
    int result = scanf("%d", &N);
    if (result != 1) {
        fprintf(output, "Error: Input is not a valid integer.\n");
        return 1;
    }

    MinHeap* heap = InitHeap(N);

    char* buffer = (char*)calloc(SIZE_FOR_BUFFER , sizeof(char));
    assert(buffer);

    for (int i = 0; i < N; i++) {
        int status = InterpretCommand(heap, i + 1, input, output, buffer);
        if (status == ERROR || status == EXIT) {
            break;
        }
    }

    DestroyHeap(heap);
    return 0;
}

//===========================================================
//===================== Heap Function =======================
//===========================================================

MinHeap* InitHeap(int capacity) {
    assert(capacity  > 0);

    MinHeap* heap    = (MinHeap*)malloc(                 sizeof(MinHeap));
    assert(heap);

    heap->capacity   = capacity;
    heap->size       = 0;

    heap->heapArray  = (Node*)   malloc( capacity      * sizeof(Node));
    assert(heap->heapArray);

    heap->indexArray = (Node**)  malloc((capacity + 1) * sizeof(Node*));
    assert(heap->indexArray);

    return heap;
}

void SiftUp(MinHeap* heap, int index) {
    assert(heap);
    while (index > 0 && heap->heapArray[index].value < heap->heapArray[ParentIndex(index)].value) {
        Swap(heap, index, ParentIndex(index));
        index = ParentIndex(index);
    }
}

status_t Insert(MinHeap* heap, int value, size_t i) {
    assert(heap);

    if (heap->size == heap->capacity) {
        return ERROR;
    }

    int index                            = heap->size;
    heap->heapArray[index].value        = value;
    heap->heapArray[index].index        = index;
    heap->heapArray[index].index_Insert = i;
    heap->indexArray[i]                 = &heap->heapArray[index];

    heap->size++;

    SiftUp(heap, index);
    return OK;
}

void SiftDown(MinHeap* heap, size_t index) {
    assert(heap);

    while (1) {
        int left     = LeftChildIndex(index);
        int right    = RightChildIndex(index);
        int smallest = index;

        if (left  < heap->size && heap->heapArray[left].value  < heap->heapArray[smallest].value) {
            smallest = left;
        }
        if (right < heap->size && heap->heapArray[right].value < heap->heapArray[smallest].value) {
            smallest = right;
        }

        if (smallest != index) {
            Swap(heap, index, smallest);
            index = smallest;
        } else {
            break;
        }
    }
}

void ExtractMin(MinHeap* heap) {
    assert(heap);

    if (heap->size == 1) {
        heap->size--;
        return;
    }

    Swap(heap, 0, heap->size - 1);
    heap->size--;

    SiftDown(heap, 0);
}

void DecreaseKey(MinHeap* heap, int index, int delta) {
    assert(heap);

    int heapIndex                     = heap->indexArray[index]->index;
    heap->heapArray[heapIndex].value -= delta;

    if (delta > 0) {
        SiftUp(heap, heapIndex);
    } else {
        SiftDown(heap, heapIndex);
    }
}

status_t GetMin(MinHeap* heap) {
    assert(heap);

    if (heap->size <= 0) {
        return ERROR;
    }

    return OK;
}

void DestroyHeap(MinHeap* heap) {
    assert(heap);

    free(heap->heapArray);
    free(heap);
}

//=========================================================
//=================== Get Index Functions =================
//=========================================================

size_t ParentIndex(int index) {
    assert(index >= 0);

    return (index - 1) / 2;
}

size_t LeftChildIndex(int index) {
    assert(index >= 0);

    return 2 * index + 1;
}

size_t RightChildIndex(int index) {
    assert(index >= 0);

    return 2 * index + 2;
}

//=========================================================
//=================== Swap ================================
//=========================================================

void Swap(MinHeap* heap, int index1, int index2) {
    assert(heap);

    long long int value1                 = heap->heapArray[index1].value;
    long long int value2                 = heap->heapArray[index2].value;

    int index_Insert1                    = heap->heapArray[index1].index_Insert;
    int index_Insert2                    = heap->heapArray[index2].index_Insert;

    heap->heapArray[index1].value        = value2;
    heap->heapArray[index2].value        = value1;

    heap->heapArray[index1].index_Insert = index_Insert2;
    heap->heapArray[index2].index_Insert = index_Insert1;

    heap->indexArray[index_Insert1]      = &heap->heapArray[index2];
    heap->indexArray[index_Insert2]      = &heap->heapArray[index1];
}

//=========================================================
//=================== Command Handlers ====================
//=========================================================

char* ReadCommand(FILE* input, char* buffer) {
    assert(input);

    if (fscanf(input, "%99s", buffer) != 1) {
        fprintf(stderr, "Error: Failed to read input.\n");
        return NULL;
    }

    return buffer;
}

status_t InterpretCommand(MinHeap* heap, int index, FILE* input, FILE* output, char* buffer) {
    assert(heap);
    assert(input);
    assert(output);

    char* command = ReadCommand(input, buffer);
    if (command == NULL) {
        return ERROR;
    }

    if (strcmp(command, "insert") == 0) {
        int x = 0;
        int result = fscanf(input, "%d", &x);
        if (result != 1) {
            return ERROR;
        }

        int status = Insert(heap, x, index);
        if (status) {
            fprintf(output, "Failed to insert element\n");
        }
        getchar();

    } else if (strcmp(command, "decreaseKey") == 0) {
        int i = 0, del_x = 0;
        int result = fscanf(input, "%d %d", &i, &del_x);
        if (result != 2) {
            return ERROR;
        }

        DecreaseKey(heap, i, del_x);

    } else if (strcmp(command, "extractMin") == 0) {
        ExtractMin(heap);

    } else if (strcmp(command, "getMin") == 0) {
        if (GetMin(heap) == OK) {
            fprintf(output, "%lld\n", heap->heapArray[0].value);
        }

    } else if (strcmp(command, "exit") == 0) {
        return EXIT;

    } else {
        return ERROR;
    }

    return OK;
}
