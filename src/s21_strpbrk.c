#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = S21_NULL;
  if (str1 && str2) {
    s21_size_t str1_len = s21_strlen(str1);
    s21_size_t str2_len = s21_strlen(str2);

    bool flag = true;
    for (s21_size_t i = 0; flag && i < str1_len; i++) {
      for (s21_size_t j = 0; flag && j < str2_len; ++j) {
        if (str1[i] == str2[j]) {
          result = (char *)(str1 + i);
          flag = false;
        }
      }
    }
  }
  return result;
}