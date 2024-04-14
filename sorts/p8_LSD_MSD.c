#include "p8_LSD_MSD.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_BYTE 256
#define SHIFT_AMOUNT 8

static void MSD_sort(int *arr, size_t n, size_t shift, int *buff) {
    assert(arr);
    assert(shift < SHIFT_AMOUNT * sizeof(int));

    if (n <= 1)
        return;

    size_t pref_cnt[256] = {};

    for (size_t i = 0; i < n; i++)
        pref_cnt[(arr[i] >> shift) & 0xff]++;

    for (size_t i = 1; i < SIZE_BYTE; i++)
        pref_cnt[i] += pref_cnt[i - 1];

    for (size_t i = n; i; i--)
        buff[--pref_cnt[(arr[i - 1] >> shift) & 0xff]] = arr[i - 1];

    memcpy(arr, buff, n * sizeof(int));

    if (!shift) {
        return;
    }

    for (size_t i = 0; i < SIZE_BYTE - 1; i++) {
        MSD_sort(arr + pref_cnt[i], pref_cnt[i + 1] - pref_cnt[i], shift - SHIFT_AMOUNT, buff);
    }
    MSD_sort(arr + pref_cnt[SIZE_BYTE - 1], n - pref_cnt[SIZE_BYTE - 1], shift - SHIFT_AMOUNT, buff);
}

void MSDsort(int* arr, size_t n)
{
    assert(arr);
    if (n == 0) {
        return;
    }

    int *buff = calloc(n, sizeof(int));
    assert(buff);

    MSD_sort(arr, n, (sizeof(int) - 1) * SHIFT_AMOUNT, buff);

    free(buff);
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------
#define MAX 1000000

void LSD_sort(int* a, int* res, int n) {
    int pref_cnt[MAX];
    memset(pref_cnt, 0, sizeof(pref_cnt));

    for (int i = 0; i < n; ++i) {
        pref_cnt[a[i]]++;
    }

    for (int i = 1; i < MAX; ++i) {
        pref_cnt[i] += pref_cnt[i - 1];
    }

    for (int i = n - 1; i >= 0; --i) {
        res[--pref_cnt[a[i]]] = a[i];
    }
}

void LSDsort(int* arr, size_t n) {
    assert(arr);
    if (n == 0) {
        return;
    }

    int* res = (int*)calloc(n, sizeof(int));
    assert(res);
    LSD_sort(arr, res, n);

    memcpy(arr, res, n * sizeof(int));

    free(res);
}