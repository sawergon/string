#include "s21_string.h"

void *s21_to_lower(const char *str) {
  char *result = S21_NULL;
  if (str) {
    int len = (int)s21_strlen(str);
    result = (char *)malloc(len + 1);
    if (result) {
      s21_strncpy(result, str, len);
      result[len] = '\0';
      for (int i = 0; i < len; ++i) {
        if ('A' <= result[i] && result[i] <= 'Z') {
          result[i] += 32;
        }
      }
    }
  }
  return (void *)result;
}