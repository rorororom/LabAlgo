#define MODULE 1000

#include <math.h>

// Остаток от деления
unsigned int hash_remainder(unsigned int key) {
    return key % MODULE;
}

// Битовое представление
unsigned int hash_bitwise(unsigned int key) {
    return (key >> 16) % MODULE;
}

// Метод умножения с константой
unsigned int hash_multiplication(unsigned int key) {
    double A = 0.618033;
    int h = MODULE * fmod(key * A, 1);

    return h;
}


