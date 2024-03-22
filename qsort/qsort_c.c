#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int *array = (int *)malloc(10000000 * sizeof(int));
    size_t size = 0;

    while (scanf("%d", &array[size]) != EOF) {
        size++;
    }

    if (size == 0)
        return 0;
    
    qsort(array, size, sizeof(int), compare);

    for (size_t i = 0; i < size; i++) {
        printf("%d\n", array[i]);
    }
    free(array);
}
