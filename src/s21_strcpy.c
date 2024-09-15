#include "s21_string.h"

char *s21_strcpy(char *dest, const char *src) {
  char *start_dest = dest;
  if (dest == S21_NULL || src == S21_NULL) {
    start_dest = S21_NULL;
  } else {
    while (*src) {
      *dest = *src;
      dest++;
      src++;
    }
    *dest = '\0';
  }
  return start_dest;
}
