#ifndef MS
#define MS

#include <stdlib.h>

void merge             (int* arr, int low, int mid, int high);
void mergeSortRecursive(int* arr, int low, int high         );
void mergeSortIterative(int*  arr, size_t n                 );
#endif
