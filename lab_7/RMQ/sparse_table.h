#ifndef SPARSE_TABLE_H
#define SPARSE_TABLE_H

int** buildTable1(int* arr, int n, int* log_table);
int** buildTable2(int* arr, int n, int* log_table);
int   query1     (int** table1, int l, int r, int* log_table);
int   query2     (int** table2, int l, int r, int* log_table);

int* computeLogTable(int n);

void freeSparseTable1(int** table1, int n);
void freeSparseTable2(int** table2, int n, int* log_table);

#endif
