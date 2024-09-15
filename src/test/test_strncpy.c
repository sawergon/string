#include "test_runner.h"

START_TEST(empty) {
  const char src[] = "";
  char s21_des[] = "";
  char org_des[] = "";
  s21_size_t n = 0;

  s21_strncpy(s21_des, src, n);
  strncpy(org_des, src, n);

  ck_assert_str_eq(s21_des, org_des);
}
END_TEST

START_TEST(byte_0) {
  const char src[] = "abcde";
  char s21_des[] = "abcde";
  char org_des[] = "abcde";
  s21_size_t n = 0;

  s21_strncpy(s21_des, src, n);
  strncpy(org_des, src, n);

  ck_assert_str_eq(s21_des, org_des);
}
END_TEST

START_TEST(empty_src) {
  const char src[] = "";
  char s21_des[] = "abcde";
  char org_des[] = "abcde";
  s21_size_t n = 0;

  s21_strncpy(s21_des, src, n);
  strncpy(org_des, src, n);

  ck_assert_str_eq(s21_des, org_des);
}
END_TEST

START_TEST(byte_1) {
  const char src[] = "abcde";
  char s21_des[7] = "abcde";
  char org_des[7] = "abcde";
  s21_size_t n = 1;

  s21_strncpy(s21_des, src, n);
  strncpy(org_des, src, n);

  ck_assert_str_eq(s21_des, org_des);
}
END_TEST

START_TEST(byte_2) {
  const char src[] = "abcde";
  char s21_des[10] = "abcde";
  char org_des[10] = "abcde";
  s21_size_t n = 2;

  s21_strncpy(s21_des, src, n);
  strncpy(org_des, src, n);

  ck_assert_str_eq(s21_des, org_des);
}
END_TEST

START_TEST(string) {
  const char src[] = "abc123def";
  char s21_des[20] = "abc123def";
  char org_des[20] = "abc123def";
  s21_size_t n = 10;

  s21_strncpy(s21_des, src, n);
  strncpy(org_des, src, n);

  ck_assert_str_eq(s21_des, org_des);
}
END_TEST

Suite *s21_strncpy_cases(void) {
  Suite *s = suite_create("s21_strncpy_cases");
  TCase *tc = tcase_create("s21_strncpy_tc");

  tcase_add_test(tc, empty);
  tcase_add_test(tc, byte_0);
  tcase_add_test(tc, empty_src);
  tcase_add_test(tc, byte_1);
  tcase_add_test(tc, byte_2);
  tcase_add_test(tc, string);

  suite_add_tcase(s, tc);
  return s;
}
