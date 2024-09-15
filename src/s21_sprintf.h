#ifndef C2_S21_STRINGPLUS_1_SRC_S21_SPRINTF_H_
#define C2_S21_STRINGPLUS_1_SRC_S21_SPRINTF_H_

#include "s21_string.h"

#define S21_BUF_SIZE 256

// База флагов
#define S21_F_MINUS '-'
#define S21_F_PLUS '+'
#define S21_F_SPACE ' '
#define S21_F_HASH '#'
#define S21_F_ZERO '0'

// Виды длинны
#define S21_L_NO_LENGTH 0
#define S21_L_SHORT_INT 'h'
#define S21_L_LONG_VAL 'l'
#define S21_L_LONG_DOUBLE 'L'

// База спецификаторов
#define S21_S_CHAR 'c'
#define S21_S_SDEC 'd'
#define S21_S_SINT 'i'
#define S21_S_SCI_MINI 'e'
#define S21_S_SCI_BIG 'E'
#define S21_S_FLOAT 'f'
#define S21_S_SHORTEST_MINI 'g'
#define S21_S_SHORTEST_BIG 'G'
#define S21_S_OCT 'o'
#define S21_S_STR 's'
#define S21_S_UINT 'u'
#define S21_S_HEX_MINI 'x'
#define S21_S_HEX_BIG 'X'
#define S21_S_POINTER 'p'
#define S21_S_COUNTER 'n'
#define S21_S_PERCENT '%'

// Специальные символы
#define S21_SC_HEX_NUM "0123456789abcdef"

// Флаги printf
typedef struct {
  bool minus;
  bool plus;
  bool space;
  bool hash;
  bool zero;
} s21_flags;

/*
 * Описание типа s21_options
 *
 * Символ спецификатора вывода
 * Флаги для этого спецификатора
 * Ширину поля вывода
 * Точность вывода числа с плавающей точкой
 *     Если число целое, то показывает минимальное количество цифр в выводе.
 *     Остальное дополняется 0.
 * Размер типа: short, long(int: %l, double: %L), wchar_t(%lc)
 * */
typedef struct {
  char specifier;
  s21_flags *flags;
  int width;
  int precision;
  bool is_precision;
  char length;
} s21_options;

int s21_sprintf(char *str, const char *format, ...);

/*
 * Работа с типом s21_options:
 *
 * Операция инициализации типа
 * Операция освобождения памяти под тип
 * */
s21_options *s21_init_s21_options();
void s21_free_s21_options(s21_options **options);

/*
 * Разбор опций после %:
 *
 * формат *format: %[флаги][ширина][.точность][длина]спецификатор
 *
 * s21_is_flag: Проверка по базе флагов.
 * s21_is_length: Проверка по видам длинны.
 * s21_set_flag_value: Установка значения true соответствующему флагу из базы
 * флагов.
 * s21_parse_flags: Разбор флагов '-', '+',' ', '#', '0'.
 * s21_parse_width: Разбор ширины.
 * s21_parse_precision: Разбор точности.(Начинает считывать после '.', иначе 0).
 * s21_parse_length: Разбор длинны.
 * */
bool s21_is_flag(char ch);
bool s21_is_length(char ch);
void s21_set_flag_value(s21_options *options, char flag);
const char *s21_parse_flags(s21_options *options, const char *format);
const char *s21_parse_width(s21_options *options, const char *format,
                            va_list va);
const char *s21_parse_precision(s21_options *options, const char *format,
                                va_list va);
const char *s21_parse_length(s21_options *options, const char *format);

/*
 * Реализация спецификаторов:
 *
 * s21_transform_value: Выдает строку для встраивания в поток вывода.
 * s21_str_from_char: Выдает строку, построенную в соответствии с options для
 * символа.
 * s21_str_from_str: Выдает строку, построенную в соответствии с options для
 * строки.
 * */
char *s21_transform_value(s21_options *options, va_list va);
char *s21_str_from_char(s21_options *options, va_list va);
char *s21_processing_wchar(s21_options *options, wchar_t wch);
char *s21_processing_char(s21_options *options, char ch);
char *s21_str_from_str(s21_options *options, va_list va);
char *s21_processing_wstr(s21_options *options, const wchar_t *wstr);
char *s21_processing_str(s21_options *options, const char *str);
char *s21_str_from_sint(s21_options *options, va_list va);
char *s21_str_from_sci(s21_options *options, va_list va);
char *s21_add_e(char *str, int pow, char sign);
char *s21_str_from_float(s21_options *options, va_list va);
char *s21_double_to_str(s21_options const *options, long double num);
char *s21_str_from_shortest(s21_options *options, va_list va);
char *s21_str_from_oct(s21_options *options, va_list va);
char *s21_str_from_hex(s21_options *options, va_list va);
char *s21_add_ox(char *str);
char *s21_str_from_uint(s21_options *options, va_list va);
char *s21_str_from_pointer(s21_options *options, va_list va);

/*
 * Общие функции
 *
 * s21_is_digit: Проверка на цифру.
 * s21_getint: Получение числа из строки(считывание до первой не цифры).
 * s21_sn_to_str: Преобразование числа со знаком в строку(СС<=16).
 * s21_un_to_str: Преобразование числа без знака в строку(СС<=16).
 * s21_reverse_str: Разворот строки.
 * */
bool s21_is_digit(char ch);
int s21_getint(const char **format);
char *s21_sn_to_str(int64_t num, int base);
char *s21_un_to_str(uint64_t num, int base);
void s21_reverse_str(char *str);
char *s21_processing_precision(s21_options const *options, char *str);
char *s21_processing_flags(s21_options *options, char *str);
void *s21_srealloc(char *src, unsigned long new_size);
void s21_pow_sig_val(int *pow, char *sign, long double *value);

#endif  // C2_S21_STRINGPLUS_1_SRC_S21_SPRINTF_H_
