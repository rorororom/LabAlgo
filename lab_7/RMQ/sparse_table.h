#ifndef SPARSE_TABLE_H
#define SPARSE_TABLE_H

int** ctorTable(int* arr, int n, int* log_table, bool var);
int   query(int** table, int l, int r, int* log_table, bool var);
int*  computeLogTable(int n);
void  freeSparseTable(int** table, int n, int* log_table, bool var);

#endif
