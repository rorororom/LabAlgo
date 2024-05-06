#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "sparse_table.h"

int min(int a, int b) {
    return (a < b) ? a : b;
}

int** buildTableRowMajor(int* arr, int n, int* log_table) {
    assert(log_table);
    assert(arr);
    assert(n >= 0);

    int** table1 = (int**)calloc(n, sizeof(int*));
    for (int i = 0; i < n; i++) {
        table1[i] = (int*)calloc(log_table[n] + 1, sizeof(int));
        table1[i][0] = arr[i];
    }
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; i + (1 << j) - 1 < n; i++) {
            table1[i][j] = min(table1[i][j - 1], table1[i + (1 << (j - 1))][j - 1]);
        }
    }
    return table1;
}

int** buildTableColumnMajor(int* arr, int n, int* log_table) {
    assert(log_table);
    assert(arr);
    assert(n >= 0);

    int** table2 = (int**)calloc(log_table[n] + 1, sizeof(int*));
    for (int i = 0; i <= log_table[n]; i++) {
        table2[i] = (int*)calloc(n, sizeof(int));
        for (int j = 0; j < n; j++) {
            if (i == 0) {
                table2[i][j] = arr[j];
            } else {
                if (j + (1 << (i - 1)) < n) {
                    table2[i][j] = min(table2[i - 1][j], table2[i - 1][j + (1 << (i - 1))]);
                }
            }
        }
    }
    return table2;
}

int** ctorTable(int* arr, int n, int* log_table, bool var) {
    if (var) {
        return buildTableRowMajor(arr, n, log_table);
    } else {
        return buildTableColumnMajor(arr, n, log_table);
    }
}

// предполагается, что отрезки будут искаться с индексации 1

int queryRowMajor(int** table_row_major, int l, int r, int* log_table) {
    assert(table_row_major);
    assert(log_table);

    int len = r - l + 1;
    int k = log_table[len];
    return min(table_row_major[l][k], table_row_major[r - (1 << k) + 1][k - 1]);
}

int queryColumnMajor(int** table_column_major, int l, int r, int* log_table) {
    assert(table_column_major);
    assert(log_table);

    int len = r - l + 1;
    int k = log_table[len];
    return min(table_column_major[k][l], table_column_major[k][r - (1 << k) + 1]);
}

int query(int** table, int l, int r, int* log_table, bool var) {
    assert(table);
    assert(log_table);

    if (var) {
        return queryRowMajor(table, l, r, log_table);
    } else {
        return queryColumnMajor(table, l, r, log_table);
    }
}

int* computeLogTable(int n) {
    assert(n >= 0);

    int* log = (int*)calloc(n + 1, sizeof(int));
    log[1] = 0;
    for (int i = 2; i <= n; i++) {
        log[i] = log[i/2] + 1;
    }

    return log;
}

void freeSparseTableRowMajor(int** table_row_major, int n) {
    if (table_row_major == NULL) return;

    for (int j = 1; (1 << j) <= n; j++) {
        free(table_row_major[j]);
    }

    free(table_row_major);
}

void freeSparseTableColumnMajor(int** table_column_major, int n, int* log_table) {
    if (table_column_major == NULL || log_table == NULL) return;

    for (int j = 0; j <= log_table[n]; j++) {
        free(table_column_major[j]);
    }

    free(table_column_major);
}

void freeSparseTable(int** table, int n, int* log_table, bool row_major) {
    if (row_major) {
        freeSparseTableRowMajor(table, n);
    } else {
        freeSparseTableColumnMajor(table, n, log_table);
    }
}
