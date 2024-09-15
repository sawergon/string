#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t len = 0;
  bool found = false;

  while (*str1 != '\0' && !found) {
    const char *tmp = str2;

    while (!found && *tmp != '\0') {
      if (*str1 == *tmp) {
        found = true;
      }
      if (!found) {
        tmp++;
      }
    }

    if (!found) {
      len++;
    }

    str1++;
  }

  return len;
}
