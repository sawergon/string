#include "test_runner.h"

START_TEST(findchar_c) {
  const char str[] = "findchar";
  char target = 'c';

  ck_assert_pstr_eq(s21_strchr(str, target), strchr(str, target));
}
END_TEST

START_TEST(findChar_C) {
  const char str[] = "findChar";
  char target = 'C';

  ck_assert_pstr_eq(s21_strchr(str, target), strchr(str, target));
}
END_TEST

START_TEST(find21char_2) {
  const char str[] = "find21char";
  char target = '2';

  ck_assert_pstr_eq(s21_strchr(str, target), strchr(str, target));
}
END_TEST

START_TEST(find21char_Z) {
  const char str[] = "find21char";
  char target = 'Z';

  ck_assert_pstr_eq(s21_strchr(str, target), strchr(str, target));
}
END_TEST

START_TEST(find21char_0) {
  const char str[] = "find21char";
  char target = '0';

  ck_assert_pstr_eq(s21_strchr(str, target), strchr(str, target));
}
END_TEST

START_TEST(empty_0) {
  const char str[] = "";
  char target = '0';

  ck_assert_pstr_eq(s21_strchr(str, target), strchr(str, target));
}
END_TEST

Suite *s21_strchr_cases(void) {
  Suite *s = suite_create("s21_strchr_cases");
  TCase *tc = tcase_create("s21_strchr_tc");

  tcase_add_test(tc, findchar_c);
  tcase_add_test(tc, findChar_C);
  tcase_add_test(tc, find21char_2);
  tcase_add_test(tc, find21char_Z);
  tcase_add_test(tc, find21char_0);
  tcase_add_test(tc, empty_0);

  suite_add_tcase(s, tc);
  return s;
}
