#include "s21_sscanf.h"

int s21_sscanf(const char *str, const char *format, ...) {
  int result;

  if ((str && format) && check_is_valid_str(str)) {
    argument args[BUFF_SIZE];
    va_list va;
    va_start(va, format);

    int args_count = preparing_arguments(format, args, va);
    result = processing_arguments(str, args, args_count);

    va_end(va);
  } else if (format && check_is_valid_format(format)) {
    result = 0;
  } else {
    result = -1;
  }

  return result;
}

int processing_arguments(const char *str, argument *args, int args_count) {
  int result = 0;
  char *mut_str = (char *)str;
  char const *start_ptr = mut_str;
  bool flag = true;
  for (int i = 0; flag && i < args_count; i++) {
    char spec = args[i].spec;
    switch (spec) {
      case 'c':
        flag = processing_c(&mut_str, &args[i], &result);
        break;
      case 'd':
        flag = processing_d(&mut_str, &args[i], &result);
        break;
      case 'i':
      case 'p':
        flag = processing_i_p(&mut_str, &args[i], &result);
        break;
      case 'g':
      case 'f':
      case 'e':
      case 'E':
      case 'G':
        processing_f(&mut_str, &args[i], &result);
        break;
      case 's':
        flag = processing_s(&mut_str, &args[i], &result);
        break;
      case 'u':
        flag = processing_u(&mut_str, &args[i], &result);
        break;
      case 'x':
      case 'X':
        processing_o_x_X(&mut_str, &args[i], &result, HEX);
        break;
      case 'o':
        processing_o_x_X(&mut_str, &args[i], &result, OCT);
        break;
      case 'n':
        *((unsigned *)args[i].va_arg) = mut_str - start_ptr;
        break;
      case W_SPACE:
        while (isspace(*mut_str)) {
          mut_str++;
        }
        break;
      case 'b':
        flag = skip_matching_chars(&mut_str, &args[i]);
        break;
      default:
        flag = false;
        result = 0;
    }
  }
  return result;
}

bool processing_s(char **str, argument *arg, int *result) {
  bool flag = false;
  char buff[BUFF_SIZE] = {'\0'};
  unsigned int i = 0;

  while (**str != '\0' && !flag) {
    if (!isspace(**str)) {
      flag = true;
      while (**str != '\0') {
        buff[i] = **str;
        i++;
        if (arg->width == STATIC && i >= arg->width_value) {
          break;
        }
        (*str)++;
        if (isspace(**str)) {
          (*str)--;
          break;
        }
      }
    }
    (*str)++;
  }

  if (arg->width != DYNAMIC && flag) {
    s21_strcpy((char *)arg->va_arg, buff);
    (*result)++;
  }
  return flag;
}

bool processing_c(char **str, argument *arg, int *result) {
  bool flag = false;
  while (**str) {
    flag = true;
    if (arg->width == DYNAMIC) {
      (*str)++;
      break;
    } else {
      *(char *)arg->va_arg = **str;
      (*str)++;
      (*result)++;
      break;
    }
  }
  return flag;
}

bool processing_u(char **str, argument *arg, int *result) {
  bool flag = false;
  char buff[BUFF_SIZE] = {'\0'};

  skip_w_spaces(str);
  if (s21_strspn(*str, U_DIGITS)) {
    s21_size_t sign = s21_strspn(*str, "+-");
    if (!((sign > 1 || (sign && (arg->width_value <= 1 && arg->width))))) {
      flag = true;
      buff[0] = **str;
      (*str)++;

      insert_chars_in_arg_result(str, DIGITS, buff, arg->width_value, 1);

      if (arg->width != DYNAMIC) {
        (*result)++;
      }
    }
  }

  if (arg->width != DYNAMIC && flag) {
    long long int result_parsing = s21_strtoll(buff, S21_NULL, DEC);
    insert_unsigned_number_in_arg_result(arg, result_parsing, 1);
  }

  if (arg->width != STATIC) {
    insert_chars_in_arg_result(str, DIGITS, S21_NULL, 0, 0);
  }
  return flag;
}

void processing_f(char **str, argument *arg, int *result) {
  unsigned check;
  if (arg->spec == 'f') {
    check = s21_strspn(*str, U_DIGITS);
  } else {
    check = s21_strspn(*str, EXTENDED_R_DIGITS);
  }

  if (check) {
    int sign = (int)s21_strspn(*str, "+-");
    if (!(sign > 1 || (sign && (arg->width_value <= 1 && arg->width)))) {
      char buff[BUFF_SIZE] = {'\0'};
      int index = 0;
      if (sign) {
        buff[0] = **str;
        index = 1;
        (*str)++;
      }

      if (arg->spec == 'f' && (int)s21_strspn(*str, "eE")) {
        insert_chars_in_arg_result(str, U_R_DIGITS, buff, arg->width_value,
                                   index);
      } else {
        insert_chars_in_arg_result(str, EXTENDED_R_DIGITS, buff,
                                   arg->width_value, index);
      }

      if (arg->width != DYNAMIC) {
        long double result_parsing = s21_strtold(buff, S21_NULL);
        insert_real_number_in_arg_result(arg, result_parsing);
        (*result)++;
      }
    }
  }

  if (arg->width != STATIC) {
    if (arg->spec == 'f')
      insert_chars_in_arg_result(str, R_DIGITS, S21_NULL, 0, 0);
    else
      insert_chars_in_arg_result(str, EXTENDED_R_DIGITS, S21_NULL, 0, 0);
  }
}

bool processing_o_x_X(char **str, argument *arg, int *res, int base) {
  bool flag = true;

  if (arg->spec == 'p') {
    base = HEX;
  }
  skip_w_spaces(str);

  if (base == HEX && **str == '0' &&
      (*(*str + 1) == 'x' || *(*str + 1) == 'X')) {
    arg->width_value -= 2;
  }

  char tmp_buff[BUFF_SIZE] = {'\0'};
  if (arg->width == STATIC && arg->width_value < s21_strlen(*str)) {
    s21_strncpy(tmp_buff, *str, arg->width_value);
  } else {
    s21_strcpy(tmp_buff, *str);
  }

  char *end_ptr;
  long long int result = s21_strtoll(tmp_buff, &end_ptr, base);
  if (end_ptr != tmp_buff) {
    if (arg->width != DYNAMIC) {
      (*res)++;
      if (arg->spec == 'p')
        *(int *)arg->va_arg = (int)result;
      else {
        insert_unsigned_number_in_arg_result(arg, result, 1);
      }
    }
  } else {
    flag = false;
  }
  unsigned int max = (unsigned int)s21_strspn(*str, X_HEX_AND_OCT);

  if (arg->width != STATIC) {
    *str += max;
  } else {
    *str += max < arg->width_value ? max : arg->width_value;
  }
  return flag;
}

bool processing_d(char **str, argument *arg, int *result) {
  bool flag = false;
  char buff[BUFF_SIZE] = {'\0'};

  skip_w_spaces(str);
  if (s21_strspn(*str, U_DIGITS)) {
    int sign = (int)s21_strspn(*str, "+-");
    if (!(sign > 1 || (sign && (arg->width_value <= 1 && arg->width)))) {
      buff[0] = **str;
      (*str)++;
      insert_chars_in_arg_result(str, DIGITS, buff, arg->width_value, 1);
      if (arg->width != DYNAMIC) {
        (*result)++;
      }
      flag = true;
    }
  }

  if (arg->width != DYNAMIC && flag) {
    long long int result_parsing =
        (long long int)s21_strtoll(buff, S21_NULL, DEC);
    insert_signed_number_in_arg_result(arg, result_parsing);
  }

  if (arg->width != STATIC) {
    insert_chars_in_arg_result(str, DIGITS, S21_NULL, 0, 0);
  }

  return flag;
}

bool processing_i_p(char **str, argument *arg, int *res) {
  bool flag = false;

  skip_w_spaces(str);
  if (s21_strspn(*str, "0x") == 2 || s21_strspn(*str, "+-0x") == 3) {
    flag = true;
    processing_o_x_X(str, arg, res, HEX);
  } else if (s21_strspn(*str, "0") == 1 || s21_strspn(*str, "+-0") == 2) {
    flag = true;
    processing_o_x_X(str, arg, res, OCT);
  } else if (s21_strspn(*str, U_DIGITS)) {
    flag = true;
    processing_d(str, arg, res);
  }

  return flag;
}

bool skip_matching_chars(char **str, const argument *arg) {
  bool result = true;
  unsigned check = s21_strspn(*str, arg->buff);
  s21_size_t len = s21_strlen(arg->buff);

  if (len == 1 && **str == arg->buff[0]) {
    (*str) = (*str) + len;
    result = true;
  } else {
    if (check != len)
      result = false;
    else {
      (*str) = (*str) + len;
    }
  }

  return result;
}

int preparing_arguments(const char *format, argument *args, va_list va) {
  int args_count = 0;
  char *mut_format = (char *)format;
  s21_size_t len_form = s21_strlen(mut_format);
  while (mut_format < format + len_form && args_count < BUFF_SIZE) {
    argument arg = {NONE, 0, 0, 0, 0, {'\0'}, 0};
    if (isspace(*mut_format)) {
      arg.spec = W_SPACE;
      skip_w_spaces(&mut_format);
    }
    if (*mut_format == PERCENT && !arg.spec) {
      mut_format++;

      if (*mut_format == PERCENT) {
        mut_format++;
        arg.spec = 'b';
        s21_memset(arg.buff, '\0', BUFF_SIZE - 1);
        arg.buff[0] = PERCENT;
      } else {
        parsing_arguments(va, &mut_format, &arg);
      }

      if (arg.spec == 'p') {
        arg.length = 0;
      }
    }

    args[args_count] = arg;
    args_count++;
  }
  return args_count;
}

void parsing_arguments(va_list va, char **mut_format, argument *arg) {
  processing_width(mut_format, arg);
  processing_length(mut_format, arg);

  arg->spec = *(*mut_format);
  (*mut_format)++;

  if (arg->width != DYNAMIC) {
    arg->va_arg = va_arg(va, void *);
  }
}

void processing_width(char **mut_format, argument *arg) {
  if (*(*mut_format) == ASTERISK) {
    (*mut_format)++;
    arg->width = DYNAMIC;
  } else {
    char tmp_buff[BUFF_SIZE] = {'\0'};
    int result_parsing;
    int index = 0;
    while (*(*mut_format) >= '0' && *(*mut_format) <= '9') {
      tmp_buff[index] = *(*mut_format);
      (*mut_format)++;
      index++;
    }
    result_parsing = (int)s21_strtoll(tmp_buff, S21_NULL, DEC);
    if (result_parsing) {
      arg->width = STATIC;
      arg->width_value = result_parsing;
    }
  }
}

void processing_length(char **mut_format, argument *arg) {
  if (*(*mut_format) == SHORT) {
    arg->length = SHORT;
    (*mut_format)++;
  }
  if (*(*mut_format) == LONG) {
    arg->length = LONG;
    (*mut_format)++;
    if (*(*mut_format) == LONG) {
      arg->length = LONG_LONG;
      (*mut_format)++;
    }
  }
  if (*(*mut_format) == LONG_DOUBLE) {
    arg->length = LONG_DOUBLE;
    (*mut_format)++;
  }
}

void insert_unsigned_number_in_arg_result(argument *arg,
                                          unsigned long long int number,
                                          int sign) {
  switch (arg->length) {
    case 0:
      *(unsigned int *)arg->va_arg = sign * (unsigned int)number;
      break;
    case SHORT:
      *(unsigned short int *)arg->va_arg = sign * (unsigned short int)number;
      break;
    case LONG:
      *(unsigned long int *)arg->va_arg = sign * (unsigned long int)number;
      break;
    case LONG_LONG:
      *(unsigned long long int *)arg->va_arg =
          sign * (unsigned long long int)number;
      break;
  }
}

void insert_signed_number_in_arg_result(argument *arg, long long int number) {
  if (arg->spec != 'p') {
    switch (arg->length) {
      case 0:
        *(int *)arg->va_arg = (int)number;
        break;
      case SHORT:
        *(short int *)arg->va_arg = (short int)number;
        break;
      case LONG:
        *(long int *)arg->va_arg = (long int)number;
        break;
      case LONG_LONG:
        *(long long int *)arg->va_arg = (long long int)number;
        break;
    }
  }
}

void insert_real_number_in_arg_result(argument *arg, long double number) {
  switch (arg->length) {
    case 0:
      *(float *)arg->va_arg = (float)number;
      break;
    case LONG:
      *(double *)arg->va_arg = (double)number;
      break;
    case LONG_DOUBLE:
      *(long double *)arg->va_arg = (long double)number;
      break;
  }
}

void insert_chars_in_arg_result(char **str, const char *chars, char *buff,
                                unsigned width, unsigned index) {
  bool flag = true;
  while (flag && **str && s21_strspn(*str, chars) != 0) {
    if ((width && index >= width) || (isspace(**str))) {
      flag = false;
    }
    if (flag) {
      if (buff) {
        buff[index] = **str;
      }
      index++;
      (*str)++;
    }
  }
}

bool check_is_valid_str(const char *str) {
  return s21_strspn(str, " \t\n\r") != s21_strlen(str);
}

bool check_is_valid_format(const char *str) {
  return s21_strspn(str, " \t\n\r") == s21_strlen(str);
}

void skip_w_spaces(char **str) {
  while (isspace(**str)) {
    (*str)++;
  }
}