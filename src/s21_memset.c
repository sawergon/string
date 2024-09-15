#include "s21_string.h"

// заполнение определенного блока памяти определенным байтом

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *p = (unsigned char *)str;
  while (n--) {
    *p++ = (unsigned char)c;
  }
  return str;
}