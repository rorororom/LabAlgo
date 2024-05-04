#include "sparse_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int** buildTableVar1(int* arr, int n, int* log_table) {
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

int** buildTableVar2(int* arr, int n, int* log_table) {
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
        return buildTableVar2(arr, n, log_table);
    } else {
        return buildTableVar1(arr, n, log_table);
    }
}

// предполагается, что отрезки будут искаться с индексации 1

int queryVar1(int** table1, int l, int r, int* log_table) {
    assert(table1);
    assert(log_table);

    int len = r - l + 1;
    int k = log_table[len];
    return min(table1[l][k], table1[r - (1 << k) + 1][k - 1]);
}

int queryVar2(int** table2, int l, int r, int* log_table) {
    assert(table2);
    assert(log_table);

    int len = r - l + 1;
    int k = log_table[len];
    return min(table2[k][l], table2[k][r - (1 << k) + 1]);
}

int query(int** table, int l, int r, int* log_table, bool var) {
    assert(table);
    assert(log_table);

    if (var) {
        return queryVar2(table, l, r, log_table);
    } else {
        return queryVar1(table, l, r, log_table);
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

void freeSparseTableVar1(int** table1, int n) {
    if (table1 == NULL) return;

    for (int j = 1; (1 << j) <= n; j++) {
        free(table1[j]);
    }

    free(table1);
}

void freeSparseTableVar2(int** table2, int n, int* log_table) {
    if (table2 == NULL || log_table == NULL) return;

    for (int j = 0; j <= log_table[n]; j++) {
        free(table2[j]);
    }

    free(table2);
}

void freeSparseTable(int** table, int n, int* log_table, bool var) {
    if (var) {
        freeSparseTableVar2(table, n, log_table);
    } else {
        freeSparseTableVar1(table, n);
    }
}

