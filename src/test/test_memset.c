#include "test_runner.h"

START_TEST(normal_test) {
  char str1[] = "Hello, School21!";
  char str2[] = "Hello, School21!";
  int c = 'G';
  s21_size_t num_byte = 10;

  s21_memset(str1, c, num_byte);
  memset(str2, c, num_byte);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(zero_string_test) {
  char str1[] = "";
  char str2[] = "";
  int c = 'G';
  s21_size_t num_byte = 0;

  s21_memset(str1, c, num_byte);
  memset(str2, c, num_byte);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(slash_zero_test) {
  char str1[] = "Hello, School21!";
  char str2[] = "Hello, School21!";
  int c = '\0';
  s21_size_t num_byte = 2;

  s21_memset(str1, c, num_byte);
  memset(str2, c, num_byte);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(int_replace_test) {
  char str1[] = "Hello, School21!";
  char str2[] = "Hello, School21!";
  int c = '1';
  s21_size_t num_byte = 10;

  s21_memset(str1, c, num_byte);
  memset(str2, c, num_byte);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(long_symbol_test) {
  char str1[] = "Hello, School21aaaaaaaaaaaaaaaaaaaaaaa!";
  char str2[] = "Hello, School21aaaaaaaaaaaaaaaaaaaaaaa!";
  int c = '(';
  s21_size_t num_byte = 10;

  s21_memset(str1, c, num_byte);
  memset(str2, c, num_byte);
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite *s21_memset_cases(void) {
  Suite *s = suite_create("s21_memset_cases");
  TCase *tc = tcase_create("tc_memset");

  tcase_add_test(tc, normal_test);
  tcase_add_test(tc, zero_string_test);
  tcase_add_test(tc, slash_zero_test);
  tcase_add_test(tc, int_replace_test);
  tcase_add_test(tc, long_symbol_test);

  suite_add_tcase(s, tc);

  return s;
}