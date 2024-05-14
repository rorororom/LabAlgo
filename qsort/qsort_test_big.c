#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void sort(int* arr, size_t n) {

    qsort(arr, n, sizeof(int), compare);
}
