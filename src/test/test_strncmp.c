#include "test_runner.h"

START_TEST(empty) {
  const char a[] = "";
  const char b[] = "";
  s21_size_t n = 0;

  int s21 = s21_strncmp(a, b, n);
  int original = strncmp(a, b, n);

  ck_assert_int_eq(s21, original);
}
END_TEST

START_TEST(abcde_) {
  const char a[] = "abcde";
  const char b[] = "";
  s21_size_t n = 0;

  int s21 = s21_strncmp(a, b, n);
  int original = strncmp(a, b, n);

  ck_assert_int_eq(s21, original);
}
END_TEST

START_TEST(_abcde) {
  const char a[] = "";
  const char b[] = "abcde";
  s21_size_t n = 0;

  int s21 = s21_strncmp(a, b, n);
  int original = strncmp(a, b, n);

  ck_assert_int_eq(s21, original);
}
END_TEST

START_TEST(abcde_abcde) {
  const char a[] = "abcde";
  const char b[] = "abcde";
  s21_size_t n = 5;

  int s21 = s21_strncmp(a, b, n);
  int original = strncmp(a, b, n);

  ck_assert_int_eq(s21, original);
}
END_TEST

START_TEST(abcde_abcde_6_bytes) {
  const char a[] = "abcdefghijk";
  const char b[] = "abcde";
  s21_size_t n = 6;

  int s21 = s21_strncmp(a, b, n);
  int original = strncmp(a, b, n);

  ck_assert_int_gt(s21, 0);
  ck_assert_int_gt(original, 0);
}
END_TEST

START_TEST(abcde_abcde_1_byte) {
  const char a[] = "abcde";
  const char b[] = "abcde";
  s21_size_t n = 1;

  int s21 = s21_strncmp(a, b, n);
  int original = strncmp(a, b, n);

  ck_assert_int_eq(s21, original);
}
END_TEST

Suite *s21_strncmp_cases(void) {
  Suite *s = suite_create("s21_strncmp_cases");
  TCase *tc = tcase_create("s21_strncmp_tc");

  tcase_add_test(tc, empty);
  tcase_add_test(tc, abcde_);
  tcase_add_test(tc, _abcde);
  tcase_add_test(tc, abcde_abcde);
  tcase_add_test(tc, abcde_abcde_6_bytes);
  tcase_add_test(tc, abcde_abcde_1_byte);

  suite_add_tcase(s, tc);
  return s;
}
