#include "s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t len_1 = s21_strlen(str1);
  s21_size_t len_2 = s21_strlen(str2);
  s21_size_t result = 0;

  if (len_2 != 0) {
    int collision[BUFF_SIZE] = {0};
    for (s21_size_t i = 0; i < BUFF_SIZE; i++) {
      collision[i] = 0;
    }

    for (s21_size_t i = 0; i < len_2; i++) {
      collision[(int)str2[i]] = 1;
    }

    bool flag = true;
    for (s21_size_t i = 0; flag && i < len_1; i++) {
      if (collision[(int)str1[i]] != 1) {
        flag = false;
      }
      if (flag) {
        result++;
      }
    }
  } else {
    result = 0;
  }

  return result;
}
