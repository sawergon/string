#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  void *result = S21_NULL;

  if (src && str && start_index <= s21_strlen(src)) {
    s21_size_t src_len = s21_strlen(src);
    s21_size_t str_len = s21_strlen(str);
    s21_size_t new_len = src_len + str_len;

    char *new_str = (char *)malloc(new_len + 1);
    if (new_str) {
      s21_size_t i = 0, j = 0, k;

      for (; i < start_index; i++) {
        new_str[i] = src[i];
      }

      for (; j < str_len; j++, i++) {
        new_str[i] = str[j];
      }

      for (k = start_index; k < src_len; k++, i++) {
        new_str[i] = src[k];
      }

      new_str[new_len] = '\0';
      result = (void *)new_str;
    }
  }

  return result;
}