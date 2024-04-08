#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    int value;
    int index;
} Node;

typedef struct {
    Node* heapArray;
    int capacity;
    int size;
} MinMaxHeap;

const int ERROR_SIZE = -1000;
const int MAX_LEN    = 256;

MinMaxHeap* InitHeap (int capacity);
void DestroyHeap     (MinMaxHeap* heap);
void ClearHeap       (MinMaxHeap* heap);

char* ReadCommand();
void InterpretCommand(MinMaxHeap* heap, char* command, int M);
void Insert          (MinMaxHeap* heap, int value);
void Swap            (Node* node1, Node* node2);

int GetMin           (MinMaxHeap* heap);
int GetMax           (MinMaxHeap* heap);
int ExtractMin       (MinMaxHeap* heap);
int ExtractMax       (MinMaxHeap* heap);

void SiftUp          (MinMaxHeap* heap, int index);
void SiftDown        (MinMaxHeap* heap, int index);
int GetMaxForGrandSon(MinMaxHeap* heap, int index);
int GetMinForGrandSon(MinMaxHeap* heap, int index);

int GetFather        (int index);
int GetLevel         (int index);
int LeftChildIndex   (int index);
int RightChildIndex  (int index);
int HasGrandparent   (int index);
int MinValue         (int a, int b);
int MaxValue         (int a, int b);
int GetDed           (int index);
int IsGrandchild     (int firstIndex, int secondIndex);


//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

int main() {
    int M = 0;
    int result = scanf("%d", &M);

    if (result != 1) {
        printf("Error: Input is not a valid integer.\n");
        return 1;
    }

    char* command = NULL;

    MinMaxHeap* heap = InitHeap(M);

    for (int i = 0; i < M; i++) {
        command = ReadCommand();

        InterpretCommand(heap, command, M);
    }

    DestroyHeap(heap);

    return 0;
}

MinMaxHeap* InitHeap(int capacity) {
    assert(capacity > 0);

    MinMaxHeap* heap = (MinMaxHeap*)malloc(sizeof(MinMaxHeap));
    heap->capacity   = capacity;
    heap->size       = 0;
    heap->heapArray  = (Node*)malloc(capacity * sizeof(Node));
    return heap;
}

int GetFather(int index) {
    assert(index >= 0);
    return (index - 1) / 2;
}

int LeftChildIndex(int index) {
    assert(index >= 0);
    return 2 * index + 1;
}

int RightChildIndex(int index) {
    assert(index >= 0);
    return 2 * index + 2;
}

int GetLevel(int index) {
    assert(index >= 0);
    return (int)floor(log2(index + 1)) % 2;
}

void Swap(Node* node1, Node* node2) {
    assert(node1);
    assert(node2);

    Node temp = *node1;
    *node1    = *node2;
    *node2    = temp;
}

int HasGrandparent(int index) {
    assert(index >= 0);
    return (index > 2);
}

int GetDed(int index) {
    assert(index >= 0);
    return GetFather(GetFather(index));
}
void SiftUp(MinMaxHeap* heap, int index) {
    assert(heap);

    int level = GetLevel(index);
    int father = GetFather(index);

    if (level % 2 == 0) {
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

        if (level % 2 == 0) {
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

    int ind[6] = {
        (2 * index + 1),
        (2 * index + 2),

        (2 * index + 1) * 2 + 1,
        (2 * index + 1) * 2 + 2,

        (2 * index + 2) * 2 + 1,
        (2 * index + 2) * 2 + 2
    };

    int max_index = index;
    for (size_t i = 0; i < 6; i++) {
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

    int ind[6] = {
        (2 * index + 1),
        (2 * index + 2),

        (2 * index + 1) * 2 + 1,
        (2 * index + 1) * 2 + 2,

        (2 * index + 2) * 2 + 1,
        (2 * index + 2) * 2 + 2
    };

    int min_index = index;
    for (size_t i = 0; i < 6; i++) {
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

int MinValue(int a, int b) {
    return (a < b) ? a : b;
}

int MaxValue(int a, int b) {
    return (a > b) ? a : b;
}

int IsGrandchild(int firstIndex, int secondIndex) {
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

        if (level % 2 == 0) {
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



void Insert(MinMaxHeap* heap, int value) {
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
        return ERROR_SIZE;
    }

    int min_value = heap->heapArray[0].value;

    if (heap->size == 1) {
        heap->size = 0;
        return min_value;
    }

    if (heap->size < 3) {
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
        return ERROR_SIZE;
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
        return ERROR_SIZE;
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
        return ERROR_SIZE;

    return heap->heapArray[0].value;
}

void DestroyHeap(MinMaxHeap* heap) {
    assert(heap);

    free(heap->heapArray);
    free(heap);
}

char* ReadCommand() {
    char* buffer = (char*)malloc(100 * sizeof(char));
    scanf("%s", buffer);

    return buffer;
}

void ClearHeap(MinMaxHeap* heap) {
    assert(heap);
    free(heap->heapArray);
    heap->heapArray = (Node*)malloc(heap->capacity * sizeof(Node));
    heap->size = 0;
}

void InterpretCommand(MinMaxHeap* heap, char* command, int M) {
    assert(heap);

    if (strcmp(command, "Insert") == 0) {
        int x = 0;
        scanf("%d", &x);
        Insert(heap, x);
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
        printf("неправильная команда\n");
    }
}
