#include "s21_string.h"

int is_trim_char(char ch, const char *trim_chars);
s21_size_t find_left_trim(const char *src, const char *trim_chars,
                          s21_size_t start);
s21_size_t find_right_trim(const char *src, const char *trim_chars,
                           s21_size_t end);

void *s21_trim(const char *src, const char *trim_chars) {
  char *result = S21_NULL;

  if (src && trim_chars) {
    if (trim_chars[0]) {
      s21_size_t begin = find_left_trim(src, trim_chars, 0);
      s21_size_t last = find_right_trim(src, trim_chars, s21_strlen(src));

      if (begin <= last) {
        result = calloc(last - begin + 1, sizeof(char));

        for (s21_size_t i = 0; begin < last; i++, begin++) {
          result[i] = src[begin];
        }
      } else {
        result = calloc(1, sizeof(char));
        result[0] = '\0';
      }
    } else {
      while (is_trim_char(src[0], "\t\n ")) {
        src++;
      }

      s21_size_t len = s21_strlen(src);
      while (len > 0 && is_trim_char(src[len - 1], "\t\n ")) {
        len--;
      }

      result = calloc(len + 1, sizeof(char));
      s21_strncpy(result, src, len);
    }
  }
  return result;
}

int is_trim_char(char ch, const char *trim_chars) {
  bool flag = true;
  int result = 0;
  int size = (int)s21_strlen(trim_chars);
  for (int i = 0; flag && i < size; i++) {
    if (ch == trim_chars[i]) {
      result = 1;
      flag = false;
    }
  }
  return result;
}

s21_size_t find_left_trim(const char *src, const char *trim_chars,
                          s21_size_t start) {
  while (is_trim_char(src[start], trim_chars)) {
    start++;
  }
  return start;
}

s21_size_t find_right_trim(const char *src, const char *trim_chars,
                           s21_size_t end) {
  while (end > 0 && is_trim_char(src[end - 1], trim_chars)) {
    end--;
  }
  return end;
}
