#ifndef MS
#define MS

#include <stdlib.h>

void merge(int* arr, int low, int mid, int high, int* buff);
void merge_sort_recursive_main(int* arr, int n);
void merge_sort_iterative(int* arr, size_t n);
#endif
