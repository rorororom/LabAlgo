#define MODULE 1000

#include <math.h>
#include <stdio.h>

// Остаток от деления
unsigned int hash_remainder(unsigned int key) {
    return key % MODULE;
}

// Битовое представление
unsigned int hash_bitwise(unsigned int key) {
    if (key == 0) // Добавляем проверку на случай, если key равно 0
        return 0;

    unsigned int result = 0;
    int shift = 0;

    while (key > 0) {
        unsigned int bit = key % 2; // Определение текущего бита
        result |= bit << shift; // Установка бита в результате
        key /= 2;
        shift++; // Увеличение сдвига
    }

    return result % MODULE;
}


// Метод умножения с константой
unsigned int hash_multiplication(unsigned int key) {
    double A = 0.618033;
    int h = MODULE * fmod(key * A, 1);

    return h;
}


