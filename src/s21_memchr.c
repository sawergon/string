#include "s21_string.h"

//  поиск первого входжения символа в первых 'n' байтах блока памяти str, на
//  который указывает аргумент 'ptr'

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *p = (const unsigned char *)str;
  unsigned char val = (unsigned char)c;

  void *result = S21_NULL;
  bool flag = true;
  for (s21_size_t i = 0; flag && i < n; i++) {
    if (p[i] == val) {
      result = (void *)(p + i);
      flag = false;
    }
  }
  return result;
}
