#include "hash_func.h"
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


size_t HashFunc(Coeff* c, int key, size_t size) {
    return ((c->A * key + c->B) % c->P) & (size - 1);
}

int hash_func_dreams(int key, int length) {
    int hash = (key + 1) % (length - 2);
    return hash;
}

int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

int GetRand(size_t left_border, size_t right_border) {
    return getRandomNumber(left_border, right_border) | 1;
}

struct Coeff* HashGetCoeff(size_t size) {
    struct Coeff* c = (struct Coeff*)malloc(sizeof(struct Coeff));
    if (c == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        exit(1);
    }

    c->A = 1;
    c->B = 0;
    c->P = 1;

    while (!(c->P % c->A))
    {
        c->P = GetRand(size, INT32_MAX);
        c->A = GetRand(3, c->P);
    }

    c->B = GetRand(0, c->P);

    return c;
}

int hash_multiplication(int key, int length) {
    double A = 0.618033; // константа предложена Кнутом (см. Томас Кормен стр. 296)
    int h = (int)(((long double)(length) * fmod(key * A, 1))) % (int)(length);

    return h;
}
