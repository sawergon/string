#include "s21_string.h"

// копирование блоков памяти из одного места в другое

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *d = (unsigned char *)dest;
  const unsigned char *s = (const unsigned char *)src;

  while (n--) {
    *d++ = *s++;
  }
  return dest;
}