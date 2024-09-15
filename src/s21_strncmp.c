#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  if (str1 && str2) {
    s21_size_t i = 0;
    while (n > 0 && str1[i] && str1[i] == str2[i]) {
      i++;
      n--;
    }
    if (n > 0) {
      result = (unsigned char)str1[i] - (unsigned char)str2[i];
    }
  }
  return result;
}
