#include "s21_sprintf.h"

int s21_sprintf(char *str, const char *format, ...) {
  char *str_start_point = str;

  va_list va;
  va_start(va, format);
  int error = 0;
  for (; *format != '\0' && error != -1;) {
    if (*format != '%') {
      *str++ = *format++;
    } else {
      format++;
      s21_options *options = s21_init_s21_options();
      format = s21_parse_flags(options, format);
      format = s21_parse_width(options, format, va);
      format = s21_parse_precision(options, format, va);
      format = s21_parse_length(options, format);
      options->specifier = *format++;
      if (options->specifier == S21_S_COUNTER) {
        int *n = va_arg(va, int *);
        *n = (int)(str - str_start_point);
      } else {
        char *result_str = s21_transform_value(options, va);
        if (result_str == NULL) {
          error = -1;
        } else {
          for (char *p = result_str; *p != '\0'; ++p) {
            *str++ = *p;
          }
          free(result_str);
        }
      }
      s21_free_s21_options(&options);
    }
  }
  *str = '\0';
  va_end(va);
  if (error == 0) {
    error = (int)(str - str_start_point);
  }
  return error;
}

char *s21_transform_value(s21_options *options, va_list va) {
  char *result = NULL;
  switch (options->specifier) {
    case S21_S_CHAR:
      result = s21_str_from_char(options, va);
      break;
    case S21_S_SDEC:
    case S21_S_SINT:
      result = s21_str_from_sint(options, va);
      break;
    case S21_S_SCI_MINI:
    case S21_S_SCI_BIG:
      result = s21_str_from_sci(options, va);
      break;
    case S21_S_FLOAT:
      result = s21_str_from_float(options, va);
      break;
    case S21_S_SHORTEST_MINI:
    case S21_S_SHORTEST_BIG:
      result = s21_str_from_shortest(options, va);
      break;
    case S21_S_OCT:
      result = s21_str_from_oct(options, va);
      break;
    case S21_S_STR:
      result = s21_str_from_str(options, va);
      break;
    case S21_S_UINT:
      result = s21_str_from_uint(options, va);
      break;
    case S21_S_HEX_MINI:
    case S21_S_HEX_BIG:
      result = s21_str_from_hex(options, va);
      break;
    case S21_S_POINTER:
      result = s21_str_from_pointer(options, va);
      break;
    case S21_S_COUNTER:
    case S21_S_PERCENT: {
      result = (char *)malloc(2);
      result[0] = '%';
      result[1] = '\0';
      break;
    }
  }
  switch (options->specifier) {
    case S21_S_HEX_BIG:
    case S21_S_SHORTEST_BIG:
    case S21_S_SCI_BIG: {
      char *tmp = s21_to_upper(result);
      free(result);
      result = tmp;
      break;
    }
  }
  return result;
}

int s21_count_main_num(long double val) {
  int count = 0;
  val = val < 0 ? -val : val;
  long double whole_part = 0;
  modfl(val, &whole_part);
  while (whole_part > 1) {
    count++;
    whole_part /= 10;
  }
  return count;
}

void s21_remove_zeroes(char *buff) {
  int len = (int)s21_strlen(buff);
  char *dot = s21_strchr(buff, '.');
  if (dot) {
    for (int i = len - 1; buff[i] == '0'; i--) {
      buff[i] = '\0';
    }
    if (dot[1] == '\0') dot[0] = '\0';
  }
}

char *s21_str_from_shortest(s21_options *options, va_list va) {
  long double value;
  if (options->length == S21_L_LONG_DOUBLE) {
    value = va_arg(va, long double);
  } else {
    value = va_arg(va, double);
  }
  if (!options->is_precision) {
    options->precision = 6;
  }
  long double cp_value = value;
  int pow = 0, main_numbers = s21_count_main_num(value);
  char sign = '+';
  s21_pow_sig_val(&pow, &sign, &cp_value);
  char *result = NULL;
  if (!options->precision) {
    options->precision++;
    if (pow > options->precision) {
      result = s21_double_to_str(options, cp_value);
      s21_reverse_str(result);
      s21_remove_zeroes(result);
      s21_reverse_str(result);
      result = s21_add_e(result, pow, sign);
    } else {
      options->precision -= main_numbers;
      result = s21_double_to_str(options, value);
    }
  } else {
    if (pow >= options->precision) {
      options->precision--;
      result = s21_double_to_str(options, cp_value);
      s21_reverse_str(result);
      s21_remove_zeroes(result);
      s21_reverse_str(result);
      result = s21_add_e(result, pow, sign);
    } else {
      options->precision -= main_numbers;
      result = s21_double_to_str(options, value);
    }
  }
  result = s21_processing_flags(options, result);
  s21_reverse_str(result);
  s21_remove_zeroes(result);
  return result;
}

char *s21_str_from_str(s21_options *options, va_list va) {
  char *result = NULL;
  if (options->length == S21_L_LONG_VAL) {
    const wchar_t *wstr = va_arg(va, wchar_t *);
    result = s21_processing_wstr(options, wstr);
  } else {
    const char *str = va_arg(va, char *);
    result = s21_processing_str(options, str);
  }
  return result;
}

void *s21_srealloc(char *src, unsigned long new_size) {
  char *reserve_src = (char *)malloc(new_size + 4);
  s21_strcpy(reserve_src, src);
  char *tmp = (char *)realloc(src, new_size + 4);
  if (NULL == tmp) {
    src = reserve_src;
  } else {
    src = tmp;
    free(reserve_src);
  }
  return src;
}

char *s21_processing_wstr(s21_options *options, const wchar_t *wstr) {
  int wstr_len = (int)wcslen(wstr);
  s21_size_t result_size = wstr_len * MB_CUR_MAX + 1;
  char *result = (char *)malloc(result_size);

  size_t converted = wcstombs(result, wstr, result_size);
  if (converted == (s21_size_t)-1) {
    free(result);
    result = S21_NULL;
  } else {
    result[converted] = '\0';
    if (options->is_precision && options->precision < (int)s21_strlen(result)) {
      result[options->precision] = '\0';
    }
    int str_len = (int)s21_strlen(result);
    if (options->width - str_len > 0) {
      if (options->flags->minus) {
        result = s21_srealloc(result, options->width + 2);
        s21_memset(result + str_len, ' ', options->width - str_len);
        result[options->width] = '\0';
      } else {
        char *buf = (char *)malloc(options->width + 2);
        s21_memset(buf, ' ', options->width - str_len);
        buf[options->width - str_len] = '\0';
        s21_strcpy(buf + (options->width - str_len), result);
        result = s21_srealloc(result, options->width + 2);
        result[0] = '\0';
        s21_strcpy(result, buf);
        free(buf);
      }
    }
  }
  return result;
}

char *s21_processing_str(s21_options *options, const char *str) {
  int str_len = (int)s21_strlen(str);
  char *result = (char *)malloc(str_len + 2);
  result[0] = '\0';
  s21_strcpy(result, str);
  if (options->is_precision && options->precision <= str_len) {
    result[options->precision] = '\0';
  }
  str_len = (int)s21_strlen(result);
  if (options->width - str_len > 0) {
    if (options->flags->minus) {
      result = s21_srealloc(result, options->width + 2);
      s21_memset(result + str_len, ' ', options->width - str_len);
      result[options->width] = '\0';
    } else {
      char *buf = (char *)malloc(options->width + 2);
      s21_memset(buf, ' ', options->width - str_len);
      buf[options->width - str_len] = '\0';
      s21_strcpy(buf + (options->width - str_len), result);
      result = s21_srealloc(result, options->width + 2);
      result[0] = '\0';
      s21_strcpy(result, buf);
      free(buf);
    }
  }
  return result;
}

void s21_pow_sig_val(int *pow, char *sign, long double *value) {
  *pow = 0;
  *sign = (int)*value == 0 ? '-' : '+';
  if (*value == 0) *sign = '+';
  while ((*sign == '+') ? (int)*value / 10 != 0 : (int)*value == 0) {
    (*pow)++;
    *value = (*sign == '+') ? *value / 10 : *value * 10;
  }
}

char *s21_str_from_sci(s21_options *options, va_list va) {
  long double value;
  if (options->length == S21_L_LONG_DOUBLE) {
    value = va_arg(va, long double);
  } else {
    value = va_arg(va, double);
  }
  int pow = 0;
  char sign = '+';
  s21_pow_sig_val(&pow, &sign, &value);
  if (!options->is_precision) {
    options->precision = 6;
  }
  char *result = s21_double_to_str(options, value);
  result = s21_add_e(result, pow, sign);
  result = s21_processing_flags(options, result);
  s21_reverse_str(result);
  return result;
}

char *s21_add_e(char *str, int pow, char sign) {
  int str_len = (int)s21_strlen(str);
  char *new_str = (char *)malloc(str_len + 6);
  int second = pow % 10, first = (pow / 10) % 10;
  new_str[0] = (char)(second + '0');
  new_str[1] = (char)(first + '0');
  new_str[2] = sign;
  new_str[3] = 'e';
  new_str[4] = '\0';
  s21_strncat(new_str, str, str_len);
  str = s21_srealloc(str, str_len + 3);
  s21_strcpy(str, new_str);
  free(new_str);
  return str;
}

char *s21_str_from_oct(s21_options *options, va_list va) {
  char *result = s21_sn_to_str(va_arg(va, int64_t), 8);
  result = s21_processing_precision(options, result);
  result = s21_processing_flags(options, result);
  if (options->flags->hash) {
    int len = (int)s21_strlen(result);
    result = s21_srealloc(result, len + 1);
    result[len++] = '0';
    result[len] = '\0';
  }
  s21_reverse_str(result);
  return result;
}

char *s21_str_from_float(s21_options *options, va_list va) {
  long double value;
  if (options->length == S21_L_LONG_DOUBLE) {
    value = va_arg(va, long double);
  } else {
    value = va_arg(va, double);
  }
  if (!options->is_precision) {
    options->precision = 6;
  }
  char *result = s21_double_to_str(options, value);
  result = s21_processing_flags(options, result);
  s21_reverse_str(result);
  return result;
}

char *s21_double_to_str(s21_options const *options, long double num) {
  int capacity = 1, len = 0;
  char *result = (char *)malloc(capacity);
  result[0] = '\0';
  bool neg = num < 0;
  num = neg ? num * -1 : num;
  long double whole_part = 0, fraction = modfl(num, &whole_part);
  if (!options->precision) {
    whole_part = roundl(num);
    fraction = 0;
  } else {
    free(result);
    long long unsigned int new_fraction =
        (fraction * powl(10, options->precision)) + (long double)0.5;
    if (new_fraction / powl(10, options->precision) >= 1.0) {
      whole_part++;
      new_fraction = 0;
    }
    result = s21_un_to_str((uint64_t)new_fraction, 10);
    if (new_fraction == 0 || fraction < 1.0) {
      result = s21_processing_precision(options, result);
    }
    capacity = len = (int)s21_strlen(result);
  }
  if ((options->is_precision && options->precision != 0) || (int)fraction ||
      (!options->is_precision && num == 0) || len) {
    result[len++] = '.';
  }
  result[len] = '\0';
  char *whole_part_str =
      s21_sn_to_str((int64_t)whole_part * (neg ? -1 : 1), 10);
  result = s21_srealloc(result, capacity + s21_strlen(whole_part_str) + 1);
  s21_strncat(result, whole_part_str, s21_strlen(whole_part_str));
  free(whole_part_str);
  return result;
}

char *s21_str_from_pointer(s21_options *options, va_list va) {
  uint64_t p = va_arg(va, uint64_t);
  char *result = NULL;
  if (p == 0) {
    const char str[] = "(nil)";
    result = (char *)malloc(6);
    for (int i = 0; i < 5; ++i) {
      result[i] = str[i];
    }
    result[5] = '\0';
  } else {
    result = s21_un_to_str(p, 16);
    result = s21_processing_precision(options, result);
    result = s21_add_ox(result);
    result = s21_processing_flags(options, result);
    s21_reverse_str(result);
  }
  return result;
}

char *s21_str_from_hex(s21_options *options, va_list va) {
  uint64_t value = va_arg(va, uint64_t);
  switch (options->length) {
    case S21_L_NO_LENGTH:
      value = (uint32_t)value;
      break;
    case S21_L_SHORT_INT:
      value = (uint16_t)value;
      break;
    case S21_L_LONG_VAL:
      break;
  }
  char *result = s21_un_to_str(value, 16);
  result = s21_processing_precision(options, result);
  if (options->flags->hash && value) {
    result = s21_add_ox(result);
  }
  result = s21_processing_flags(options, result);
  s21_reverse_str(result);
  return result;
}

char *s21_add_ox(char *str) {
  int str_len = (int)s21_strlen(str);
  if (str_len > 0) {
    str = (char *)s21_srealloc(str, str_len + 3);
    str[str_len++] = 'x';
    str[str_len++] = '0';
    str[str_len++] = '\0';
  }
  return str;
}

char *s21_str_from_uint(s21_options *options, va_list va) {
  uint64_t value = va_arg(va, uint64_t);
  switch (options->length) {
    case S21_L_NO_LENGTH:
      value = (uint32_t)value;
      break;
    case S21_L_SHORT_INT:
      value = (uint16_t)value;
      break;
    case S21_L_LONG_VAL:
      break;
  }
  char *result = s21_un_to_str(value, 10);
  result = s21_processing_precision(options, result);
  result = s21_processing_flags(options, result);
  s21_reverse_str(result);
  return result;
}

char *s21_un_to_str(uint64_t num, int base) {
  int capacity = 2, len = 0;
  char *result = (char *)malloc(capacity);
  if (num == 0) {
    result[0] = '0';
    len = 1;
  } else {
    while (num > 0) {
      result[len++] = S21_SC_HEX_NUM[num % base];
      num /= base;
      if (len >= capacity - 1) {
        capacity *= 2;
        result[len] = '\0';
        result = (char *)s21_srealloc(result, capacity);
      }
    }
  }
  result[len++] = '\0';
  return result;
}

char *s21_str_from_sint(s21_options *options, va_list va) {
  int64_t value = va_arg(va, int64_t);
  switch (options->length) {
    case S21_L_SHORT_INT:
      value = (int16_t)value;
      break;
    case S21_L_LONG_VAL:
      break;
    case S21_L_NO_LENGTH:
      value = (int32_t)value;
      break;
  }
  char *result = s21_sn_to_str(value, 10);
  if (value == 0 && options->is_precision && options->precision == 0) {
    result[0] = '\0';
  }
  result = s21_processing_precision(options, result);
  result = s21_processing_flags(options, result);
  s21_reverse_str(result);
  return result;
}

char *s21_processing_flags(s21_options *options, char *str) {
  int len = (int)s21_strlen(str), num_len = len;
  bool neg = (len > 0 && str[len - 1] == '-');
  if (options->flags->space && options->specifier != S21_S_UINT && !neg) {
    str = (char *)s21_srealloc(str, len + 2);
    str[len++] = ' ';
    str[len] = '\0';
  }
  if (options->width > len) {
    int error = 2, buf_len = options->width + error,
        quantity = options->width - len;
    char *buf_width = (char *)malloc(buf_len);
    if (options->flags->minus) {
      s21_memset(buf_width, ' ', quantity);
      s21_strcpy(buf_width + quantity, str);
    } else {
      s21_strcpy(buf_width, str);
      s21_memset(buf_width + len - (neg ? 1 : 0),
                 options->flags->zero ? '0' : ' ', quantity);
      if (neg) {
        buf_width[len + quantity - 1] = '-';
      }
      buf_width[len + quantity] = '\0';
    }
    str = (char *)s21_srealloc(str, buf_len);
    s21_strcpy(str, buf_width);
    free(buf_width);
  }
  if (options->flags->plus && options->specifier != S21_S_UINT) {
    if (!neg) {
      len = (int)s21_strlen(str);
      if (num_len == len) {
        str = (char *)s21_srealloc(str, len + 2);
        str[len++] = '+';
        str[len] = '\0';
      } else {
        str[num_len] = '+';
        str[len] = '\0';
      }
    }
  }
  return str;
}

char *s21_processing_precision(s21_options const *options, char *str) {
  int len = (int)s21_strlen(str);
  bool neg = str[len--] == '-';
  if (options->precision > len) {
    len++;
    str = (char *)s21_srealloc(str, options->precision + 4);
    for (; len < options->precision;) {
      str[len++] = '0';
    }
    if (neg) str[len++] = '-';
    str[len++] = '\0';
  }
  return str;
}

char *s21_sn_to_str(int64_t num, int base) {
  int capacity = 2, len = 0;
  char *result = (char *)malloc(capacity);
  bool neg = (num < 0);
  num = neg ? -num : num;
  if (num == 0) {
    result[0] = '0';
    len = 1;
  } else {
    while (num > 0) {
      result[len++] = S21_SC_HEX_NUM[num % base];
      num /= base;
      if (len >= capacity - 1) {
        capacity *= 2;
        result[len] = '\0';
        result = (char *)s21_srealloc(result, capacity);
      }
    }
  }
  if (neg) {
    result[len++] = '-';
  }
  if (len >= capacity) {
    capacity *= 2;
    result = (char *)s21_srealloc(result, capacity);
  }
  result[len++] = '\0';
  return result;
}

void s21_reverse_str(char *str) {
  int len = (int)s21_strlen(str);
  char *buf = (char *)malloc(len);
  for (int i = 0; i < len; ++i) {
    buf[i] = str[len - (i + 1)];
  }
  for (int i = 0; i < len; ++i) {
    str[i] = buf[i];
  }
  free(buf);
}

char *s21_str_from_char(s21_options *options, va_list va) {
  char *result = NULL;
  if (options->length == 'l') {
    wchar_t wch = va_arg(va, wchar_t);
    result = s21_processing_wchar(options, wch);
    if ((int)wch > 128) {
      free(result);
      result = NULL;
    }
  } else {
    char ch = va_arg(va, int);
    result = s21_processing_char(options, ch);
  }
  return result;
}

char *s21_processing_wchar(s21_options *options, wchar_t wch) {
  int len = (options->width > 2) ? options->width : 1;
  char *result = (char *)malloc(len + 1);
  result[0] = '\0';
  result[1] = '\0';
  const wchar_t w_str[2] = {wch, '\0'};
  if (!options->flags->minus && options->width) {
    char tmp[3] = {'\0'};
    wcstombs(tmp, w_str, 3);
    for (s21_size_t i = 0; i < options->width - s21_strlen(tmp); i++)
      result[i] = ' ';
    result[options->width - s21_strlen(tmp)] = '\0';
    s21_strncat(result, tmp, s21_strlen(tmp));
  } else if (options->width) {
    wcstombs(result, w_str, len);
    for (int i = (int)s21_strlen(result); i < options->width; i++)
      result[i] = ' ';
  } else {
    wcstombs(result, w_str, len);
  }
  result[len] = '\0';
  return result;
}

char *s21_processing_char(s21_options *options, char ch) {
  int len = (options->width) ? options->width : 1, start;
  char *result = (char *)malloc(len + 1);
  if (!options->flags->minus && options->width) {
    start = 0;
    result[len - 1] = ch;
  } else {
    result[0] = ch;
    start = 1;
  }
  for (int i = start; i < len - 1 + start; ++i) {
    result[i] = ' ';
  }
  result[len] = '\0';
  return result;
}

bool s21_is_length(char ch) {
  return (ch == S21_L_LONG_VAL || ch == S21_L_SHORT_INT ||
          ch == S21_L_LONG_DOUBLE);
}

const char *s21_parse_length(s21_options *options, const char *format) {
  if (s21_is_length(*format)) {
    options->length = *format++;
  }
  return format;
}

const char *s21_parse_precision(s21_options *options, const char *format,
                                va_list va) {
  if (*format == '.') {
    options->is_precision = true;
    format++;
    if (*format == '*') {
      format++;
      int precision = va_arg(va, int);
      options->precision = precision > 0 ? precision : 0;
    } else {
      options->precision = s21_getint(&format);
    }
  }
  return format;
}

const char *s21_parse_width(s21_options *options, const char *format,
                            va_list va) {
  if (*format == '*') {
    format++;
    int width = va_arg(va, int);
    options->width = width > 0 ? width : 0;
  } else {
    options->width = s21_getint(&format);
  }
  return format;
}

bool s21_is_digit(char ch) { return ('0' <= ch && ch <= '9'); }

int s21_getint(const char **format) {
  char buff[S21_BUF_SIZE];
  int cur_len = 0;
  for (; s21_is_digit(**format); (*format)++) {
    buff[cur_len++] = **format;
  }
  buff[cur_len++] = '\0';
  return (int)strtol(buff, NULL, 10);
}

const char *s21_parse_flags(s21_options *options, const char *format) {
  for (; s21_is_flag(*format); format++) {
    s21_set_flag_value(options, *format);
  }
  return format;
}
s21_options *s21_init_s21_options() {
  s21_options *options = (s21_options *)malloc(sizeof(s21_options));
  options->length = 0;
  options->width = 0;
  options->precision = 0;
  options->is_precision = false;
  options->specifier = 0;
  options->flags = (s21_flags *)malloc(sizeof(s21_flags));
  options->flags->minus = false;
  options->flags->plus = false;
  options->flags->hash = false;
  options->flags->zero = false;
  options->flags->space = false;
  return options;
}

void s21_free_s21_options(s21_options **options) {
  free((*options)->flags);
  free(*options);
}

bool s21_is_flag(char ch) {
  return (ch == S21_F_ZERO || ch == S21_F_SPACE || ch == S21_F_PLUS ||
          ch == S21_F_HASH || ch == S21_F_MINUS);
}

void s21_set_flag_value(s21_options *options, char flag) {
  switch (flag) {
    case S21_F_MINUS:
      options->flags->minus = true;
      break;
    case S21_F_PLUS:
      options->flags->plus = true;
      break;
    case S21_F_SPACE:
      options->flags->space = true;
      break;
    case S21_F_HASH:
      options->flags->hash = true;
      break;
    case S21_F_ZERO:
      options->flags->zero = true;
      break;
    default:
      break;
  }
}
