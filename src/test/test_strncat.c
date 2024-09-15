#include "test_runner.h"

START_TEST(normal_test) {
  char result[100] = "Hello ";
  char expected[100] = "Hello ";
  const char add_str[] = "School21";
  s21_size_t num = 5;

  s21_strncat(result, add_str, num);
  strncat(expected, add_str, num);

  ck_assert_str_eq(result, expected);
}
END_TEST

START_TEST(empty_test) {
  char result[100] = "";
  char expected[100] = "";
  const char add_str[] = "";
  s21_size_t num = 0;

  s21_strncat(result, add_str, num);
  strncat(expected, add_str, num);

  ck_assert_str_eq(result, expected);
}
END_TEST

START_TEST(empty_add_test) {
  char result[100] = "Hello ";
  char expected[100] = "Hello ";
  const char add_str[] = "";
  s21_size_t num = 0;

  s21_strncat(result, add_str, num);
  strncat(expected, add_str, num);

  ck_assert_str_eq(result, expected);
}
END_TEST

START_TEST(add_to_empty_test) {
  char result[100] = "";
  char expected[100] = "";
  const char add_str[] = "School21";
  s21_size_t num = 5;

  s21_strncat(result, add_str, num);
  strncat(expected, add_str, num);

  ck_assert_str_eq(result, expected);
}
END_TEST

START_TEST(add_zero_test) {
  char result[100] = "Hello ";
  char expected[100] = "Hello ";
  const char add_str[] = "School21";
  s21_size_t num = 0;

  s21_strncat(result, add_str, num);
  strncat(expected, add_str, num);

  ck_assert_str_eq(result, expected);
}
END_TEST

START_TEST(add_symbol_test) {
  char result[100] = "Hello ";
  char expected[100] = "Hello ";
  const char add_str[] = "()()()!!..)";
  s21_size_t num = 5;

  s21_strncat(result, add_str, num);
  strncat(expected, add_str, num);

  ck_assert_str_eq(result, expected);
}
END_TEST

Suite *s21_strncat_cases(void) {
  Suite *s = suite_create("s21_strncat_cases");
  TCase *tc = tcase_create("tc_strncat");

  tcase_add_test(tc, normal_test);
  tcase_add_test(tc, empty_test);
  tcase_add_test(tc, empty_add_test);
  tcase_add_test(tc, add_to_empty_test);
  tcase_add_test(tc, add_zero_test);
  tcase_add_test(tc, add_symbol_test);

  suite_add_tcase(s, tc);
  return s;
}