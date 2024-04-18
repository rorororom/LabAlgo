#define MODULE 1000

//Битовое представление
unsigned int hash_int_representation(float key) {
    unsigned int int_representation = *(unsigned int*)&key;

    return int_representation % MODULE;
}


unsigned int hash_float_bitwise(float key) {
    if (key == 0.0f) // Добавляем проверку на случай, если key равно 0
        return 0;

    unsigned int result = 0;
    int shift = 0;

    unsigned int key_as_int = *(unsigned int *)&key; // Преобразуем float в его битовое представление

    while (key_as_int > 0) {
        unsigned int bit = key_as_int % 2; // Определение текущего бита
        result |= bit << shift; // Установка бита в результате
        key_as_int /= 2;
        shift++; // Увеличение сдвига
    }

    return result % MODULE;
}


// Извлечение мантиссы
unsigned int hash_mantissa(unsigned int key, unsigned int table_size) {
    unsigned int mantissa_mask = 0x007FFFFF;
    unsigned int mantissa = key & mantissa_mask;
    return mantissa % MODULE;
}

// Извлечение экспоненты
unsigned int hash_exponent(unsigned int key, unsigned int table_size) {
    unsigned int exponent_mask = 0x7F800000;
    unsigned int exponent = (key & exponent_mask) >> 23;
    return exponent % MODULE;
}

// Произведение мантиссы на экспоненту.
unsigned int hash_mantissa_times_exponent(unsigned int key, unsigned int table_size) {
    unsigned int mantissa_mask = 0x007FFFFF;
    unsigned int mantissa = key & mantissa_mask;

    unsigned int exponent_mask = 0x7F800000;
    unsigned int exponent = (key & exponent_mask) >> 23;

    return (mantissa * exponent) % MODULE;
}
