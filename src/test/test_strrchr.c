#include "test_runner.h"

START_TEST(empty) {
  const char str1[] = "";
  char str2 = '\0';

  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(abcde_) {
  const char str1[] = "abcde";
  char str2 = '\0';

  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(_abcde) {
  const char str1[] = "";
  char str2 = 'a';

  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(abcd_abcd_c) {
  const char str1[] = "abcd abcd";
  char str2 = 'c';

  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(abcd_abcd_d) {
  const char str1[] = "abcd abcd";
  char str2 = 'd';

  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(abcd_abcd_a) {
  const char str1[] = "abcd abcd";
  char str2 = 'a';

  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(find_upper_case_A) {
  const char str1[] = "aaaaaaaaaaAa";
  char str2 = 'A';

  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(find_num) {
  const char str1[] = "123456789";
  char str2 = '0';

  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

Suite *s21_strrchr_cases(void) {
  Suite *s = suite_create("s21_strrchr_cases");
  TCase *tc = tcase_create("s21_strrchr_tc");

  tcase_add_test(tc, empty);
  tcase_add_test(tc, abcde_);
  tcase_add_test(tc, _abcde);
  tcase_add_test(tc, abcd_abcd_c);
  tcase_add_test(tc, abcd_abcd_d);
  tcase_add_test(tc, abcd_abcd_a);
  tcase_add_test(tc, find_upper_case_A);
  tcase_add_test(tc, find_num);

  suite_add_tcase(s, tc);
  return s;
}
