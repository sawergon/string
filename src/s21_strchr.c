#include "s21_string.h"

// Выполняет поиск первого вхождения символа c (беззнаковый тип) в строке, на
// которую указывает аргумент str.

char *s21_strchr(const char *str, int c) {
  char *ch = S21_NULL;
  bool flag = true;
  while (flag && *str != '\0') {
    if (*str == c) {
      ch = (char *)str;
      flag = false;
    }
    if (flag) {
      str++;
    }
  }
  return ch;
}
