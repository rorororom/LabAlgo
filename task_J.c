#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    size_t value;
    size_t index;
} Node;

typedef struct {
    Node* heapArray;
    size_t capacity;
    size_t size;
} MinMaxHeap;

enum STATUS {
    OK = 0,
    ERROR = 1,
};

typedef int status_t;

const int DESCENDANTS = 6;
const int ONE_NODE_PER_MIN_LEVEL = 3;
const size_t SIZE_FOR_BUFFER = 100;

/**
 * @brief Инициализация кучи.
 *
 * @param capacity Ёмкость кучи.
 * @return Указатель на новую структуру кучи.
 */
MinMaxHeap* InitHeap(int capacity);

/**
 * @brief Уничтожение кучи и освобождение памяти.
 *
 * @param heap Указатель на структуру кучи.
 */
void DestroyHeap(MinMaxHeap* heap);

/**
 * @brief Очистка кучи (удаление всех элементов).
 *
 * @param heap Указатель на структуру кучи.
 */
void ClearHeap(MinMaxHeap* heap);

// ===================================================================================
// ====================== USER INPUT =================================================
// ===================================================================================

/**
 * @brief Чтение команды из ввода.
 *
 * @param input Файловый указатель на ввод.
 * @return Указатель на строку с командой.
 */
char* ReadCommand(FILE* input);

/**
 * @brief Интерпретация команды и выполнение соответствующих действий.
 *
 * @param heap Указатель на структуру кучи.
 * @param M Количество команд.
 * @param input Файловый указатель на ввод.
 * @param output Файловый указатель на вывод.
 * @return Статус выполнения команды (OK или ERROR).
 */
status_t InterpretCommand(MinMaxHeap* heap, int M, FILE* input, FILE* output);

// ===================================================================================
// ====================== MinMax Helpers =============================================
// ===================================================================================

/**
 * @brief Вставка нового элемента в кучу.
 *
 * @param heap Указатель на структуру кучи.
 * @param value Значение нового элемента.
 */
void InsertMinMaxHeap(MinMaxHeap* heap, int value);

/**
 * @brief Обменивает местами два узла в MinMax куче.
 *
 * @param node1 Указатель на первый узел.
 * @param node2 Указатель на второй узел.
 */
void Swap(Node* node1, Node* node2);

/**
 * @brief Получает минимальное значение из MinMax кучи без его извлечения.
 *
 * @param heap Указатель на структуру кучи.
 * @return Минимальное значение в куче или ERROR_SIZE, если куча пуста.
 */
int GetMin(MinMaxHeap* heap);

/**
 * @brief Получает максимальное значение из MinMax кучи без его извлечения.
 *
 * @param heap Указатель на структуру кучи.
 * @return Максимальное значение в куче или ERROR_SIZE, если куча пуста.
 */
int GetMax(MinMaxHeap* heap);

/**
 * @brief Извлекает минимальное значение из MinMax кучи.
 *
 * @param heap Указатель на структуру кучи.
 * @return Минимальное значение в куче или ERROR_SIZE, если куча пуста.
 */
int ExtractMin(MinMaxHeap* heap);

/**
 * @brief Извлекает максимальное значение из MinMax кучи.
 *
 * @param heap Указатель на структуру кучи.
 * @return Максимальное значение в куче или ERROR_SIZE, если куча пуста.
 */
int ExtractMax(MinMaxHeap* heap);

/**
 * @brief Поднимает элемент вверх по MinMax куче, чтобы восстановить её свойства.
 *
 * @param heap Указатель на структуру MinMax кучи.
 * @param index Индекс элемента, который нужно поднять.
 */
void SiftUp(MinMaxHeap* heap, int index);

/**
 * @brief Опускает элемент вниз по MinMax куче, чтобы восстановить её свойства.
 *
 * @param heap Указатель на структуру MinMax кучи.
 * @param index Индекс элемента, который нужно опустить.
 */
void SiftDown(MinMaxHeap* heap, int index);

/**
 * @brief Возвращает индекс максимального внука элемента в MinMax куче.
 *
 * @param heap Указатель на структуру MinMax кучи.
 * @param index Индекс элемента, у которого нужно найти максимального внука.
 * @return Индекс максимального внука.
 */
int GetMaxForGrandSon(MinMaxHeap* heap, int index);

/**
 * @brief Возвращает индекс минимального внука элемента в MinMax куче.
 *
 * @param heap Указатель на структуру MinMax кучи.
 * @param index Индекс элемента, у которого нужно найти минимального внука.
 * @return Индекс минимального внука.
 */
int GetMinForGrandSon(MinMaxHeap* heap, int index);

/**
 * @brief Возвращает индекс отца элемента в куче.
 *
 * @param index Индекс элемента.
 * @return Индекс отца элемента.
 */
inline size_t GetFather(int index);

/**
 * @brief Возвращает уровень элемента в куче.
 *
 * @param index Индекс элемента.
 * @return Уровень элемента.
 */
inline size_t GetLevel(int index);

/**
 * @brief Возвращает индекс левого потомка элемента в куче.
 *
 * @param index Индекс элемента.
 * @return Индекс левого потомка элемента.
 */
inline size_t LeftChildIndex(int index);

/**
 * @brief Возвращает индекс правого потомка элемента в куче.
 *
 * @param index Индекс элемента.
 * @return Индекс правого потомка элемента.
 */
inline size_t RightChildIndex(int index);

/**
 * @brief Проверяет, имеет ли элемент в куче дедушку.
 *
 * @param index Индекс элемента.
 * @return 1, если у элемента есть дедушка, иначе 0.
 */
inline size_t HasGrandparent(int index);

/**
 * @brief Возвращает минимальное значение из двух чисел.
 *
 * @param a Первое число.
 * @param b Второе число.
 * @return Минимальное значение из двух чисел.
 */
inline int MinValue(int a, int b);

/**
 * @brief Возвращает максимальное значение из двух чисел.
 *
 * @param a Первое число.
 * @param b Второе число.
 * @return Максимальное значение из двух чисел.
 */
inline int MaxValue(int a, int b);

/**
 * @brief Возвращает индекс дедушки элемента в куче.
 *
 * @param index Индекс элемента.
 * @return Индекс дедушки элемента.
 */
inline size_t GetDed(int index);

/**
 * @brief Проверяет, является ли второй индекс внуком первого индекса в куче.
 *
 * @param firstIndex Индекс первого элемента.
 * @param secondIndex Индекс второго элемента.
 * @return 1, если второй индекс является внуком первого, иначе 0.
 */
inline size_t IsGrandchild(int firstIndex, int secondIndex);


//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

int main() {
    FILE* output = stdout;
    FILE* input  = stdin;
    int M = 0;

    int result = fscanf(input, "%d", &M);

    if (result != 1) {
        printf("Error: Input is not a valid integer.\n");
        return 1;
    }

    MinMaxHeap* heap = InitHeap(M);

    char* command = NULL;

    for (int i = 0; i < M; i++) {
        int status = InterpretCommand(heap, M, input, output);
        if (status == ERROR) {
            break;
        }
    }

    DestroyHeap(heap);

    return 0;
}

MinMaxHeap* InitHeap(int capacity) {
    assert(capacity > 0);

    MinMaxHeap* heap = (MinMaxHeap*)malloc(sizeof(MinMaxHeap));
    assert(heap);

    heap->capacity   = capacity;
    heap->size       = 0;
    heap->heapArray  = (Node*)malloc(capacity * sizeof(Node));
    assert(heap->heapArray);

    return heap;
}

inline size_t GetFather(int index) {
    assert(index >= 0);
    return (index - 1) / 2;
}

inline size_t LeftChildIndex(int index) {
    assert(index >= 0);
    return 2 * index + 1;
}

inline size_t RightChildIndex(int index) {
    assert(index >= 0);
    return 2 * index + 2;
}

int Log2Floor(int n) {
    int log = 0;
    while (n >>= 1) {
        log++;
    }
    return log;
}

size_t GetLevel(int index) {
    assert(index >= 0);
    return (Log2Floor(index + 1)) % 2;
}

void Swap(Node* node1, Node* node2) {
    assert(node1);
    assert(node2);

    Node temp = *node1;
    *node1    = *node2;
    *node2    = temp;
}

inline size_t HasGrandparent(int index) {
    assert(index >= 0);
    return (index > 2);
}

inline int IsMaxLevel(int level) {
    return level % 2 != 0;
}

inline size_t GetDed(int index) {
    assert(index >= 0);
    return GetFather(GetFather(index));
}

void SiftUp(MinMaxHeap* heap, int index) {
    assert(heap);

    int level = GetLevel(index);
    int father = GetFather(index);

    if (IsMaxLevel(level)) {
        if (heap->heapArray[index].value < heap->heapArray[father].value) {
            Swap(&heap->heapArray[index], &heap->heapArray[father]);
            index = father;
        }
    } else {
        if (heap->heapArray[index].value > heap->heapArray[father].value) {
            Swap(&heap->heapArray[index], &heap->heapArray[father]);
            index = father;
        }
    }

    while (HasGrandparent(index)) {
        int ind_ded = GetDed(index);
        level = GetLevel(index);

        if (IsMaxLevel(level)) {
            if (heap->heapArray[index].value > heap->heapArray[ind_ded].value) {
                Swap(&heap->heapArray[index], &heap->heapArray[ind_ded]);
                index = ind_ded;
            } else {
                break;
            }
        } else {
            if (heap->heapArray[index].value < heap->heapArray[ind_ded].value) {
                Swap(&heap->heapArray[index], &heap->heapArray[ind_ded]);
                index = ind_ded;
            } else {
                break;
            }
        }
    }
}

int GetMaxForGrandSon(MinMaxHeap* heap, int index) {
    assert(heap);

    int ind[DESCENDANTS] = {
        (LeftChildIndex (index)),
        (RightChildIndex(index)),

        LeftChildIndex(LeftChildIndex(index)),
        LeftChildIndex(RightChildIndex(index)),

        RightChildIndex(LeftChildIndex(index)),
        RightChildIndex(RightChildIndex(index))
    };

    int max_index = index;
    for (size_t i = 0; i < DESCENDANTS; i++) {
        if (ind[i] < heap->size) {
            if (heap->heapArray[ind[i]].value > heap->heapArray[max_index].value) {
                max_index = ind[i];
            }
        } else {
            break;
        }
    }

    return max_index;
}

int GetMinForGrandSon(MinMaxHeap* heap, int index) {
    assert(heap);

    int ind[DESCENDANTS] = {
        (LeftChildIndex (index)),
        (RightChildIndex(index)),

        LeftChildIndex(LeftChildIndex(index)),
        LeftChildIndex(RightChildIndex(index)),

        RightChildIndex(LeftChildIndex(index)),
        RightChildIndex(RightChildIndex(index))
    };

    int min_index = index;
    for (size_t i = 0; i < DESCENDANTS; i++) {
        if (ind[i] < heap->size) {
            if (heap->heapArray[ind[i]].value < heap->heapArray[min_index].value) {
                min_index = ind[i];
            }
        } else {
            break;
        }
    }

    return min_index;
}

inline int MinValue(int a, int b) {
    return (a + b - abs(a - b)) / 2;
}

inline int MaxValue(int a, int b) {
    return (a + b + abs(a - b)) / 2;
}

inline size_t IsGrandchild(int firstIndex, int secondIndex) {
    int leftGrandSon  = LeftChildIndex (LeftChildIndex (firstIndex));
    int rightGrandSon = RightChildIndex(RightChildIndex(firstIndex));

    return (secondIndex >= leftGrandSon && secondIndex <= rightGrandSon);
}

void SiftDown(MinMaxHeap* heap, int index) {
    assert(heap);
    assert(index >= 0);

    while (index < heap->size - 1) {
        int left  = LeftChildIndex(index);
        int right = RightChildIndex(index);

        int level = GetLevel(index);

        if (IsMaxLevel(level)) {
            int min_m = GetMaxForGrandSon(heap, index);

            if (heap->heapArray[min_m].value > heap->heapArray[index].value) {
                Swap(&heap->heapArray[min_m], &heap->heapArray[index]);


                if (IsGrandchild(index, min_m)) {
                    index = min_m;
                    level = GetLevel(index);
                    int father = GetFather(index);
                    if (heap->heapArray[index].value < heap->heapArray[father].value) {
                        Swap(&heap->heapArray[index], &heap->heapArray[father]);
                    }
                } else {
                    break;
                }
            } else {
                break;
            }
        } else {
            int min_m = GetMinForGrandSon(heap, index);

            if (heap->heapArray[min_m].value < heap->heapArray[index].value) {
                Swap(&heap->heapArray[min_m], &heap->heapArray[index]);

                if (IsGrandchild(index, min_m)) {
                    index = min_m;
                    level = GetLevel(index);
                    int father = GetFather(index);
                    if (heap->heapArray[index].value > heap->heapArray[father].value) {
                        Swap(&heap->heapArray[index], &heap->heapArray[father]);
                    }
                } else {
                    break;
                }
            } else {
                break;
            }
    }
}
}



void InsertMinMaxHeap(MinMaxHeap* heap, int value) {
    assert(heap);

    int index = heap->size;
    heap->heapArray[index].value = value;
    heap->heapArray[index].index = index;

    heap->size++;

    SiftUp(heap, index);
}

int ExtractMin(MinMaxHeap* heap) {
    assert(heap);

    if (heap->size == 0) {
        return ERROR;
    }

    int min_value = heap->heapArray[0].value;

    if (heap->size == 1) {
        heap->size = 0;
        return min_value;
    }

    if (heap->size < ONE_NODE_PER_MIN_LEVEL) {
        min_value = heap->heapArray[1].value;
        heap->size--;
    } else {
        int min_child_index = (heap->heapArray[1].value < heap->heapArray[2].value) ? 1 : 2;
        min_value = heap->heapArray[min_child_index].value;

        heap->heapArray[min_child_index] = heap->heapArray[heap->size - 1];
        heap->size--;
        SiftDown(heap, min_child_index);
    }
    return min_value;
}


int ExtractMax(MinMaxHeap* heap) {
    assert(heap);

    if (heap->size == 0) {
        return ERROR;
    }

    int max_value = heap->heapArray[0].value;

    if (heap->size == 1) {
        heap->size = 0;
    } else {
        heap->heapArray[0] = heap->heapArray[heap->size - 1];
        heap->size--;

        SiftDown(heap, 0);
    }
    return max_value;
}

int GetMin(MinMaxHeap* heap) {
    assert(heap);

    if (heap->size == 0) {
        return ERROR;
    } else if (heap->size == 1) {
        return heap->heapArray[0].value;
    } else if (heap->size == 2) {
        return heap->heapArray[1].value;
    } else {
        int min1 = heap->heapArray[1].value;
        int min2 = heap->heapArray[2].value;
        return MinValue(min1, min2);
    }
}

int GetMax(MinMaxHeap* heap) {
    assert(heap);

    if (heap->size == 0)
        return ERROR;

    return heap->heapArray[0].value;
}

void DestroyHeap(MinMaxHeap* heap) {
    assert(heap);

    free(heap->heapArray);
    free(heap);
}

void ClearHeap(MinMaxHeap* heap) {
    assert(heap);

    free(heap->heapArray);
    heap->heapArray = (Node*)malloc(heap->capacity * sizeof(Node));
    assert(heap->heapArray);

    heap->size = 0;
}

char* ReadCommand(FILE* input) {
    static char buffer[SIZE_FOR_BUFFER];
    if (fscanf(input, "%99s", buffer) != 1) {
        fprintf(stderr, "Error: Failed to read input.\n");
        return NULL;
    }

    return buffer;
}

status_t InterpretCommand(MinMaxHeap* heap, int M, FILE* input, FILE* output) {
    char* command = ReadCommand(input);
    if (command == NULL) {
        return ERROR;
    }

    if (strcmp(command, "insert") == 0) {
        int x = 0;
        int result = scanf("%d", &x);
        if (result != 1) {
            printf("Error: Input is not a valid integer.\n");
            return 1;
        }

        InsertMinMaxHeap(heap, x);
        printf("ok\n");

    } else if (strcmp(command, "extract_min") == 0) {
        int min = ExtractMin(heap);
        if (min == ERROR_SIZE)
            printf("error\n");
        else
            printf("%d\n", min);

    } else if (strcmp(command, "extract_max") == 0) {
        int max = ExtractMax(heap);
        if (max == ERROR_SIZE)
            printf("error\n");
        else
            printf("%d\n", max);

    } else if (strcmp(command, "get_min") == 0) {
        int getValue = GetMin(heap);
        if (getValue == ERROR_SIZE)
            printf("error\n");
        else
            printf("%d\n", getValue);

    } else if (strcmp(command, "get_max") == 0) {
        int getValue = GetMax(heap);
        if (getValue == ERROR_SIZE)
            printf("error\n");
        else
            printf("%d\n", getValue);

    } else if (strcmp(command, "size") == 0) {
        printf("%d\n", heap->size);

    } else if (strcmp(command, "clear") == 0) {
        ClearHeap(heap);
        printf("ok\n");

    } else {
        printf("Error command\n");
        return ERROR;
    }

    return OK;
}
