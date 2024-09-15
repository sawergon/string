#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  bool flag = true;
  s21_size_t h_len = s21_strlen(haystack);
  s21_size_t n_len = s21_strlen(needle);
  char *result = S21_NULL;

  if (h_len < n_len) {
    flag = false;
  }
  for (s21_size_t i = 0; flag && i <= h_len - n_len; i++) {
    s21_size_t j;
    bool founded = true;
    for (j = 0; j < n_len; j++) {
      if (haystack[i + j] != needle[j]) {
        founded = false;
      }
    }
    if (founded) {
      result = (char *)(haystack + i);
      flag = false;
    }
  }
  return result;
}