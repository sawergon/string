#ifndef S21_SSCANF_H_
#define S21_SSCANF_H_

#include "s21_string.h"

#define BUFF_SIZE 512
#define DEC 10
#define HEX 16
#define OCT 8
#define PERCENT '%'
#define W_SPACE ' '
#define ASTERISK '*'
#define SHORT 'h'
#define LONG 'l'
#define LONG_LONG 'A'
#define LONG_DOUBLE 'L'
#define DIGITS "0123456789"
#define U_DIGITS "+-0123456789"
#define R_DIGITS ".0123456789"
#define U_R_DIGITS "+-.0123456789"
#define EXTENDED_R_DIGITS ".0123456789eE+-NaAifIFn"
#define X_HEX_AND_OCT "xX0123456789abcdefABCDEF"

typedef enum width { NONE, STATIC, DYNAMIC } width;

typedef struct argument {
  bool is_flag;
  width width;
  unsigned width_value;
  unsigned length;
  char spec;
  char buff[BUFF_SIZE];
  void *va_arg;
} argument;

void processing_length(char **mut_format, argument *arg);
int preparing_arguments(const char *format, argument *args, va_list va);
int processing_arguments(const char *str, argument *args, int args_count);
void parsing_arguments(va_list va, char **mut_format, argument *arg);
bool processing_s(char **str, argument *arg, int *result);
bool processing_d(char **str, argument *arg, int *result);
bool processing_c(char **str, argument *arg, int *result);
bool processing_u(char **str, argument *arg, int *result);
void processing_f(char **str, argument *arg, int *result);
bool processing_i_p(char **str, argument *arg, int *res);
bool processing_o_x_X(char **str, argument *arg, int *res, int base);
void processing_width(char **mut_format, argument *arg);
bool skip_matching_chars(char **str, const argument *arg);
void insert_unsigned_number_in_arg_result(argument *arg,
                                          unsigned long long int number,
                                          int sign);
void insert_signed_number_in_arg_result(argument *arg, long long int number);
void insert_real_number_in_arg_result(argument *arg, long double number);
void insert_chars_in_arg_result(char **str, const char *chars, char *buff,
                                unsigned width, unsigned index);
bool check_is_valid_str(const char *str);
bool check_is_valid_format(const char *str);
void skip_w_spaces(char **str);

#endif  // S21_SSCANF_H_
