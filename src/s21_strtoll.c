#include "s21_string.h"

void get_sign(const char **tmp_str, unsigned char *ch, int *neg);
void skip_w_spaces_const(const char **tmp_str, unsigned char *ch);
void get_base(int *base, const char **tmp_str, unsigned char *ch);

long long s21_strtoll(const char *str, char **end_ptr, int base) {
  const char *tmp_str = str;
  long long result;
  unsigned char ch;
  long long cut_off;
  long long cut_limit;
  int neg = 0, any;

  skip_w_spaces_const(&tmp_str, &ch);
  get_sign(&tmp_str, &ch, &neg);
  get_base(&base, &tmp_str, &ch);

  cut_off = (long long)LLONG_MAX / (long long)base;
  cut_limit = (long long)LLONG_MAX % (long long)base;
  bool flag = true;
  for (result = 0, any = 0; flag; ch = *tmp_str++) {
    if (isdigit(ch)) {
      ch -= '0';
    } else if (isalpha(ch)) {
      ch -= isupper(ch) ? 'A' - 10 : 'a' - 10;
    } else {
      flag = false;
    }
    if (flag && ch >= base) {
      flag = false;
    }
    if (flag) {
      if (any < 0 || result > cut_off ||
          (result == cut_off && ch > cut_limit)) {
        any = -1;
      } else {
        any = 1;
        result *= base;
        result += ch;
      }
    }
  }
  if (any < 0) {
    if (neg) {
      result = LLONG_MIN;
    } else {
      result = LLONG_MAX;
    }
  } else if (neg) {
    result = -result;
  }
  if (end_ptr != 0) {
    *end_ptr = (char *)(any ? tmp_str - 1 : str);
  }
  return (result);
}

void get_base(int *base, const char **tmp_str, unsigned char *ch) {
  if (((*base) == 0 || (*base) == HEX) && (*ch) == '0' &&
      (*(*tmp_str) == 'x' || *(*tmp_str) == 'X')) {
    (*ch) = (*tmp_str)[1];
    (*tmp_str) += 2;
    (*base) = 16;
  }
  if ((*base) == 0) {
    (*base) = (*ch) == '0' ? OCT : DEC;
  }
}

void skip_w_spaces_const(const char **tmp_str, unsigned char *ch) {
  do {
    (*ch) = *(*tmp_str)++;
  } while (isspace((*ch)));
}

void get_sign(const char **tmp_str, unsigned char *ch, int *neg) {
  if ((*ch) == '-') {
    (*neg) = 1;
    (*ch) = *(*tmp_str)++;
  } else if ((*ch) == '+') {
    (*ch) = *(*tmp_str)++;
  }
}
