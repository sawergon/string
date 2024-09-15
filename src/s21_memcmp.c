#include "s21_string.h"

// сравнение двух блоков памяти побайтово

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int result = 0;
  bool flag = true;
  const unsigned char *p1 = (const unsigned char *)str1;
  const unsigned char *p2 = (const unsigned char *)str2;

  while (flag && n--) {
    if (*p1 != *p2) {
      result = (int)(*p1) - (int)(*p2);
      flag = false;
    }
    if (flag) {
      p1++;
      p2++;
    }
  }
  return result;
}