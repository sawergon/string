#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
  s21_size_t x = 0;
  if (str) {
    for (int i = 0; str[i]; i++) {
      x++;
    }
  }
  return x;
}