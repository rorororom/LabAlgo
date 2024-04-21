#ifndef HASH_FUNC_STRING_H
#define HASH_FUNC_STRING_H

unsigned int hash_length(char* s);
unsigned int hash_summ_letters(char* s);
unsigned int hash_polynomial(char* s);
unsigned int hash_crc32(const unsigned char *buf, int len);

#endif
