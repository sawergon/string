#include "s21_string.h"

bool check_sign(char **curr);
void count_mantissa_nums(char **curr, int *mant_size, int *dec_pt);
bool check_nan_inf(char **end_ptr, bool is_neg, char *curr,
                   long double *fraction);
long double calc_fraction(int mant_size, char **curr);
void skim_exp(int frac_exp, char *exp_ptr, bool *flag, char **curr, int *exp);
long double generate_real_number_by_exp(long double fraction, long double *d,
                                        int exp);

void calc_mantissa(const char *input_str, int mant_size, int dec_pt, bool *flag,
                   long double *fraction, char **curr, int *frac_exp,
                   char **exp_ptr);

long double s21_strtold(const char *input_str, char **end_ptr) {
  bool is_neg, flag = true;
  long double fraction, *d = S21_NULL;
  char *curr = (char *)input_str;
  int exp = 0;
  int frac_exp;
  int mant_size = 0;
  int dec_pt = -1;
  char *exp_ptr;

  skip_w_spaces(&curr);
  is_neg = check_sign(&curr);
  flag = check_nan_inf(end_ptr, is_neg, curr, &fraction);

  if (flag) {
    count_mantissa_nums(&curr, &mant_size, &dec_pt);
    calc_mantissa(input_str, mant_size, dec_pt, &flag, &fraction, &curr,
                  &frac_exp, &exp_ptr);
    if (flag) {
      skim_exp(frac_exp, exp_ptr, &flag, &curr, &exp);
      if (flag) {
        fraction = generate_real_number_by_exp(fraction, d, exp);
      }
    }

    if (end_ptr != S21_NULL) {
      *end_ptr = curr;
    }
  }

  return is_neg ? -fraction : fraction;
}

void calc_mantissa(const char *input_str, int mant_size, int dec_pt, bool *flag,
                   long double *fraction, char **curr, int *frac_exp,
                   char **exp_ptr) {
  (*exp_ptr) = (*curr);
  (*curr) -= mant_size;
  if (dec_pt < 0) {
    dec_pt = mant_size;
  } else {
    mant_size--;
  }
  if (mant_size > 18) {
    (*frac_exp) = dec_pt - 18;
    mant_size = 18;
  } else {
    (*frac_exp) = dec_pt - mant_size;
  }
  if (mant_size == 0) {
    (*fraction) = 0.0;
    (*curr) = (char *)input_str;
    (*flag) = false;
  } else {
    (*fraction) = calc_fraction(mant_size, curr);
  }
}

long double generate_real_number_by_exp(long double fraction, long double *d,
                                        int exp) {
  long double powers_of_10[] = {10.,    100.,   1.0e4,   1.0e8,  1.0e16,
                                1.0e32, 1.0e64, 1.0e128, 1.0e256};
  int max_exp = 511;
  long double dbl_exp;
  bool exp_sign = false;

  if (exp < 0) {
    exp_sign = true;
    exp = -exp;
  } else {
    exp_sign = false;
  }
  if (exp > max_exp) {
    exp = max_exp;
  }
  dbl_exp = 1.0;
  for (d = powers_of_10; exp != 0; exp >>= 1, d++) {
    if (exp & 01) {
      dbl_exp *= *d;
    }
  }
  if (exp_sign) {
    fraction /= dbl_exp;
  } else {
    fraction *= dbl_exp;
  }
  return fraction;
}

void skim_exp(int frac_exp, char *exp_ptr, bool *flag, char **curr, int *exp) {
  bool exp_sign = false;
  (*curr) = exp_ptr;
  if ((*(*curr) == 'E') || (*(*curr) == 'e')) {
    (*curr)++;
    exp_sign = check_sign(curr);
    if (!isdigit(*(*curr))) {
      (*curr) = exp_ptr;
      (*flag) = false;
    }
    while ((*flag) && isdigit(*(*curr))) {
      (*exp) = (*exp) * 10 + (*(*curr) - '0');
      (*curr)++;
    }
  }

  if ((*flag)) {
    if (exp_sign) {
      (*exp) = frac_exp - (*exp);
    } else {
      (*exp) = frac_exp + (*exp);
    }
  }
}

long double calc_fraction(int mant_size, char **curr) {
  int frac1 = 0, frac2 = 0, ch;
  while (mant_size > 9) {
    ch = *(*curr);
    (*curr)++;
    if (ch == '.') {
      ch = *(*curr);
      (*curr)++;
    }
    frac1 = 10 * frac1 + (ch - '0');
    mant_size--;
  }

  while (mant_size > 0) {
    ch = *(*curr);
    (*curr) += 1;
    if (ch == '.') {
      ch = *(*curr);
      (*curr)++;
    }
    frac2 = 10 * frac2 + (ch - '0');
    mant_size--;
  }

  return (1.0e9 * frac1) + frac2;
}

bool check_nan_inf(char **end_ptr, bool is_neg, char *curr,
                   long double *fraction) {
  bool flag = true;
  if (curr && s21_strlen(curr) > 2) {
    char *lower_case_curr = (char *)s21_to_lower(curr);
    if ((lower_case_curr[0] == 'i' && lower_case_curr[1] == 'n' &&
         lower_case_curr[2] == 'f') ||
        (lower_case_curr[0] == 'n' && lower_case_curr[1] == 'a' &&
         lower_case_curr[2] == 'n')) {
      if (end_ptr != S21_NULL) {
        *end_ptr = curr + 3;
      }
      *fraction =
          (lower_case_curr[0] == 'i') ? (is_neg ? -INFINITY : INFINITY) : NAN;
      flag = false;
    }
    free(lower_case_curr);
  }
  return flag;
}

void count_mantissa_nums(char **curr, int *mant_size, int *dec_pt) {
  for ((*mant_size) = 0;; (*mant_size)++) {
    int ch = *(*curr);
    if (!isdigit(ch)) {
      if ((ch != '.') || ((*dec_pt) >= 0)) {
        break;
      }
      (*dec_pt) = (*mant_size);
    }
    (*curr)++;
  }
}

bool check_sign(char **curr) {
  bool is_neg = false;
  if (*(*curr) == '-') {
    is_neg = true;
    (*curr)++;
  } else {
    if (*(*curr) == '+') {
      (*curr)++;
    }
    is_neg = false;
  }
  return is_neg;
}
