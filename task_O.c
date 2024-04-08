#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long long int value;
    int index;
    int index_Insert;
} Node;

typedef struct {
    Node* heapArray;
    Node** indexArray;
    int capacity;
    int size;
} MinHeap;

MinHeap* InitHeap(int capacity);
void     DestroyHeap(MinHeap* heap);

void Swap(MinHeap* heap, int index1, int index2);

int  ParentIndex    (int index);
int  LeftChildIndex (int index);
int  RightChildIndex(int index);

void SiftUp     (MinHeap* heap, int index);
void SiftDown   (MinHeap* heap, int index);
void Insert     (MinHeap* heap, int value, int i);
void ExtractMin (MinHeap* heap);
void DecreaseKey(MinHeap* heap, int index, int delta);
void GetMin     (MinHeap* heap);
char* ReadCommand();

void InterpretCommand(MinHeap* heap, char* command, int index);

//--------------------------------------------------------------------
//--------------------------------------------------------------------

int main() {
    int q = 0;
    int result = scanf("%d", &q);

    if (result != 1) {
        printf("Error: Input is not a valid integer.\n");
        return 1;
    }

    char* command = NULL;

    MinHeap* heap = InitHeap(q);

    for (int i = 0; i < q; i++) {
        command = ReadCommand();

        InterpretCommand(heap, command, i + 1);
        if (strcmp(command, "exit") == 0) {
            break;
        }
    }

    DestroyHeap(heap);
    return 0;
}

MinHeap* InitHeap(int capacity) {
    assert(capacity  > 0);
    MinHeap* heap    = (MinHeap*)malloc(                 sizeof(MinHeap));
    heap->capacity   = capacity;
    heap->size       = 0;
    heap->heapArray  = (Node*)   malloc( capacity      * sizeof(Node));
    heap->indexArray = (Node**)  malloc((capacity + 1) * sizeof(Node*));

    return heap;
}

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


int ParentIndex(int index) {
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

void SiftUp(MinHeap* heap, int index) {
    assert(heap);
    while (index > 0 && heap->heapArray[index].value < heap->heapArray[ParentIndex(index)].value) {
        Swap(heap, index, ParentIndex(index));
        index = ParentIndex(index);
    }
}

void Insert(MinHeap* heap, int value, int i) {
    assert(heap);

    if (heap->size == heap->capacity) {
        printf("Куча заполнена\n");
        return;
    }

    int index                            = heap->size;
    heap->heapArray[index].value        = value;
    heap->heapArray[index].index        = index;
    heap->heapArray[index].index_Insert = i;
    heap->indexArray[i]                 = &heap->heapArray[index];

    heap->size++;

    SiftUp(heap, index);
}

void SiftDown(MinHeap* heap, int index) {
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

    assert(heap);

    int heapIndex                     = heap->indexArray[index]->index;
    heap->heapArray[heapIndex].value -= delta;

    if (delta > 0) {
        SiftUp(heap, heapIndex);
    } else {
        SiftDown(heap, heapIndex);
    }
}

void GetMin(MinHeap* heap) {
    assert(heap);

    if (heap->size <= 0) {
        printf("Куча пуста\n");
        return;
    }

    printf("%lld\n", heap->heapArray[0].value);
}

void DestroyHeap(MinHeap* heap) {
    assert(heap);

    free(heap->heapArray);
    free(heap);
}

char* ReadCommand() {
    char* buffer = (char*)malloc(100 * sizeof(char));
    scanf("%s", buffer);

    return buffer;
}

void InterpretCommand(MinHeap* heap, char* command, int index) {
    assert(heap);
    assert(command);

    if (strcmp(command, "Insert") == 0) {
        int x = 0;
        scanf("%d", &x);
        Insert(heap, x, index);

    } else if (strcmp(command, "DecreaseKey") == 0) {
        int i = 0, del_x = 0;
        scanf("%d %d", &i, &del_x);
        DecreaseKey(heap, i, del_x);

    } else if (strcmp(command, "ExtractMin") == 0) {
        ExtractMin(heap);

    } else if (strcmp(command, "GetMin") == 0) {
        GetMin(heap);
    } else {
        abort();
    }
}
