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

void LSDsort(int* arr, size_t n)
{
    assert(arr);

    int *buff = calloc(n, sizeof(int));
    assert(buff);

    for (size_t shift = 0; shift < SHIFT_AMOUNT * sizeof(int); shift += SHIFT_AMOUNT)
    {
        size_t pref_cnt[SIZE_BYTE] = {};

        for (size_t i = 0; i < n; i++)
            pref_cnt[(arr[i] >> shift) & 0xff]++;

        for (size_t i = 1; i < SIZE_BYTE; i++)
            pref_cnt[i] += pref_cnt[i - 1];

        for (size_t i = n; i; i--)
            buff[--pref_cnt[(arr[i - 1] >> shift) & 0xff]] = arr[i - 1];

        memcpy(arr, buff, n * sizeof(int));
    }

    free(buff);
}
