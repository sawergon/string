#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  bool flag = true;
  static char *pointer;
  char *token = S21_NULL;

  if (!str) {
    str = pointer;
  }

  str += s21_strspn(str, delim);
  if (!*str) {
    pointer = str;
    flag = false;
  }
  if (flag) {
    token = str;
    str = s21_strpbrk(str, delim);
    if (str) {
      *str = '\0';
      pointer = str + 1;
    } else {
      pointer = token + s21_strlen(token);
    }
  }
  return token;
}