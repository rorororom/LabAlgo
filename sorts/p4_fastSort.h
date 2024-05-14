#ifndef FS
#define FS

#include <stdlib.h>

void lomuto_sort_one_branch(int* arr, size_t n);
void hoare_sort_one_branch (int* arr, size_t n);
void thick_sort_one_branch (int* arr, size_t n);

void lomuto_sort(int* arr, size_t n);
void hoare_sort(int* arr, size_t n);
void thick_sort(int* arr, size_t n);
#endif
