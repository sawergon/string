#include "test_runner.h"

START_TEST(empty) {
  char str1[] = "";
  const char str2[] = "";

  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(_abcde) {
  char str1[] = "";
  const char str2[] = "abdce";

  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(abcde_) {
  char str1[] = "abcde";
  const char str2[] = "";

  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(find_world) {
  char str1[] = "Hello world!";
  const char str2[] = "world";

  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(find_non_included) {
  char str1[] = "You don't ack me!";
  const char str2[] = "deal";

  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(any_case) {
  char str1[] = "AbCdEfGhIj";
  const char str2[] = "loloEFG";

  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(repeated) {
  char str1[] = "LOL LOL LOL LOL";
  const char str2[] = "LOL";

  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(least_word) {
  char str1[] = "123 456 7 89";
  const char str2[] = "89";

  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(one_simbol) {
  char str1[] = "5";
  const char str2[] = "5";

  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(one_simbol_2) {
  char str1[] = "lololoLMAOIMHOxD1234567890";
  const char str2[] = " ";

  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

START_TEST(one_simbol_3) {
  char str1[] = "@";
  const char str2[] = "lololoLMAOIMHOxD1234567890@";

  ck_assert_pstr_eq(s21_strstr(str1, str2), strstr(str1, str2));
}
END_TEST

Suite *s21_strstr_cases(void) {
  Suite *s = suite_create("s21_strstr_cases");
  TCase *tc = tcase_create("s21_strstr_tc");

  tcase_add_test(tc, empty);
  tcase_add_test(tc, _abcde);
  tcase_add_test(tc, abcde_);
  tcase_add_test(tc, find_world);
  tcase_add_test(tc, find_non_included);
  tcase_add_test(tc, any_case);
  tcase_add_test(tc, repeated);
  tcase_add_test(tc, least_word);
  tcase_add_test(tc, one_simbol);
  tcase_add_test(tc, one_simbol_2);
  tcase_add_test(tc, one_simbol_3);

  suite_add_tcase(s, tc);
  return s;
}