#include "test_runner.h"

START_TEST(null_dest) {
  const char* src = "abcde";
  char* s21_des = S21_NULL;
  char* org_des = S21_NULL;

  s21_strcpy(s21_des, src);

  ck_assert_ptr_eq(s21_des, S21_NULL);
  ck_assert_ptr_eq(org_des, S21_NULL);
}
END_TEST

START_TEST(null_src) {
  const char* src = S21_NULL;
  char* s21_des = "abcde";
  char* org_des = "abcde";

  s21_strcpy(s21_des, src);

  ck_assert_str_eq(s21_des, org_des);
}
END_TEST

START_TEST(both_null) {
  const char* src = S21_NULL;
  char* s21_des = S21_NULL;

  s21_strcpy(s21_des, src);

  ck_assert_ptr_eq(s21_des, S21_NULL);
}
END_TEST

START_TEST(both_empty) {
  const char src[] = "";
  char s21_des[] = "";
  char org_des[] = "";

  s21_strcpy(s21_des, src);
  strcpy(org_des, src);

  ck_assert_str_eq(s21_des, org_des);
}
END_TEST

START_TEST(equals_str) {
  const char src[] = "abcde";
  char s21_des[] = "abcde";
  char org_des[] = "abcde";

  s21_strcpy(s21_des, src);
  strcpy(org_des, src);

  ck_assert_str_eq(s21_des, org_des);
}
END_TEST

START_TEST(empty_src) {
  const char src[] = "";
  char s21_des[] = "abcde";
  char org_des[] = "abcde";

  s21_strcpy(s21_des, src);
  strcpy(org_des, src);

  ck_assert_str_eq(s21_des, org_des);
}
END_TEST

START_TEST(string) {
  const char src[] = "abc123def";
  char s21_des[20] = "abc123def";
  char org_des[20] = "abc123def";

  s21_strcpy(s21_des, src);
  strcpy(org_des, src);

  ck_assert_str_eq(s21_des, org_des);
}
END_TEST

Suite* s21_strcpy_cases(void) {
  Suite* suite = suite_create("s21_strcpy_cases");
  TCase* tc = tcase_create("s21_strcpy_tc");

  tcase_add_test(tc, null_dest);
  tcase_add_test(tc, null_src);
  tcase_add_test(tc, both_null);
  tcase_add_test(tc, both_empty);
  tcase_add_test(tc, equals_str);
  tcase_add_test(tc, empty_src);
  tcase_add_test(tc, string);

  suite_add_tcase(suite, tc);
  return suite;
}
