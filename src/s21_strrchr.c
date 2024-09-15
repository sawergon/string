#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  bool flag = true;
  char *result = S21_NULL;
  int str_len = (int)s21_strlen(str);

  for (int i = str_len; flag && i >= 0; i--) {
    if (str[i] == c) {
      result = ((char *)str) + i;
      flag = false;
    }
  }

  return result;
}