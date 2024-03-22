#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 256

void SortStep(int *source, unsigned int *dest, int *offset, const int num, int size) {
    unsigned int temp;
    int i, k;

    for (i = size - 1; i >= 0; i--) {
        temp = source[i];
        k = (temp >> num) & 0xFF;
        offset[k]--;
        dest[offset[k]] = temp;
    }
}

void LSDsort(int* arr, int n) {
    int s[4][256] = {0};
    int i;
    unsigned int *m_temp = (unsigned int *)malloc(n * sizeof(unsigned int));
    int *offset = (int *)arr;

    for (i = 0; i < n; i++) {
        int k = arr[i];
        s[0][(k >> 0) & 0xFF]++;
        s[1][(k >> 8) & 0xFF]++;
        s[2][(k >> 16) & 0xFF]++;
        s[3][(k >> 24) & 0xFF]++;
    }

    for (i = 1; i < 256; i++) {
        s[0][i] += s[0][i - 1];
        s[1][i] += s[1][i - 1];
        s[2][i] += s[2][i - 1];
        s[3][i] += s[3][i - 1];
    }

    SortStep(arr, m_temp, s[0], 0, n);
    SortStep(m_temp, arr, s[1], 8, n);
    SortStep(arr, m_temp, s[2], 16, n);
    SortStep(m_temp, arr, s[3], 24, n);

    free(m_temp);
}

void MSDsort(int* arr, int n) {
    int s[4][256] = {0};
    int i;
    unsigned int *m_temp = (unsigned int *)malloc(n * sizeof(unsigned int));
    int offset[256] = {0};

    for (i = 0; i < n; i++) {
        unsigned int k = arr[i];
        s[0][(k >> 24) & 0xFF]++;
        s[1][(k >> 16) & 0xFF]++;
        s[2][(k >> 8) & 0xFF]++;
        s[3][(k >> 0) & 0xFF]++;
    }

    for (i = 1; i < 256; i++) {
        s[0][i] += s[0][i - 1];
        s[1][i] += s[1][i - 1];
        s[2][i] += s[2][i - 1];
        s[3][i] += s[3][i - 1];
    }

    SortStep(arr, m_temp, s[3], 0, n);
    SortStep(m_temp, arr, s[2], 8, n);
    SortStep(arr, m_temp, s[1], 16, n);
    SortStep(m_temp, arr, s[0], 24, n);

    free(m_temp);
}

int getMax(int* arr, int n) {
    assert(arr);
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

void LSD_notBit(int* arr, int* res, int n) {
    assert(arr);
    int *pref_cnt = (int*)malloc(MAX * sizeof(int));
    assert(pref_cnt);

    for (int shift = 0; shift < 32; shift += 8) {
        for (int i = 0; i < MAX; i++) {
            pref_cnt[i] = 0;
        }

        for (int i = 0; i < n; i++) {
            pref_cnt[(arr[i] >> shift) & 0xFF]++;
        }

        for (int i = 1; i < MAX; ++i) {
            pref_cnt[i] += pref_cnt[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            res[--pref_cnt[(arr[i] >> shift) & 0xFF]] = arr[i];
        }

        int *temp = arr;
        arr = res;
        res = temp;
    }

    free(pref_cnt);
}


void LSDsort_notBit(int* arr, size_t n) {
    assert(arr);

    int* res = (int*)calloc(n, sizeof(int));
    assert(res);

    LSD_notBit(arr, res, n);
    free(res);
}
