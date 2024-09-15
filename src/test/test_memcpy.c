#include "test_runner.h"

START_TEST(normal_test) {
  const char str[] = "Hello, School21!";
  s21_size_t num_bytes = 10;
  char res[num_bytes];
  char expected[num_bytes];

  s21_memcpy(res, str, num_bytes);
  memcpy(expected, str, num_bytes);

  ck_assert_mem_eq(res, expected, num_bytes);
}
END_TEST

START_TEST(zero_byte_test) {
  const char str[] = "Hello, School21!";
  s21_size_t num_bytes = 0;
  char res[num_bytes];
  char expected[num_bytes];

  s21_memcpy(res, str, num_bytes);
  memcpy(expected, str, num_bytes);

  ck_assert_mem_eq(res, expected, num_bytes);
}
END_TEST

START_TEST(zero_string_test) {
  const char str[] = "";
  s21_size_t num_bytes = 0;
  char res[num_bytes];
  char expected[num_bytes];

  s21_memcpy(res, str, num_bytes);
  memcpy(expected, str, num_bytes);

  ck_assert_mem_eq(res, expected, num_bytes);
}
END_TEST

START_TEST(one_byte_test) {
  const char str[] = "Hello, School21!";
  s21_size_t num_bytes = 1;
  char res[num_bytes];
  char expected[num_bytes];

  s21_memcpy(res, str, num_bytes);
  memcpy(expected, str, num_bytes);

  ck_assert_mem_eq(res, expected, num_bytes);
}
END_TEST

START_TEST(one_byte_num_test) {
  const char str[] = "21";
  s21_size_t num_bytes = 1;
  char res[num_bytes];
  char expected[num_bytes];

  s21_memcpy(res, str, num_bytes);
  memcpy(expected, str, num_bytes);

  ck_assert_mem_eq(res, expected, num_bytes);
}
END_TEST

START_TEST(symbol_num_test) {
  const char str[] = "Hell909090909***:1213((((o, School21!";
  s21_size_t num_bytes = 30;
  char res[num_bytes];
  char expected[num_bytes];

  s21_memcpy(res, str, num_bytes);
  memcpy(expected, str, num_bytes);

  ck_assert_mem_eq(res, expected, num_bytes);
}
END_TEST

Suite *s21_memcpy_cases(void) {
  Suite *s = suite_create("s21_memcpy_cases");
  TCase *tc = tcase_create("tc_memcpy");

  tcase_add_test(tc, normal_test);
  tcase_add_test(tc, zero_byte_test);
  tcase_add_test(tc, zero_string_test);
  tcase_add_test(tc, one_byte_test);
  tcase_add_test(tc, one_byte_num_test);
  tcase_add_test(tc, symbol_num_test);

  suite_add_tcase(s, tc);

  return s;
}