//
// Created by alex on 09.11.23.
//
#include "test_runner.h"

START_TEST(empty_str) {
  char const str[] = "";
  char *answer = "";
  char *my_answer = s21_to_lower(str);
  ck_assert_str_eq(my_answer, answer);
  free(my_answer);
}
END_TEST

START_TEST(all_upper) {
  char const str[] = "THIS TEXT IN UPPER CASE";
  char answer[] = "this text in upper case";
  char *my_answer = s21_to_lower(str);
  ck_assert_str_eq(my_answer, answer);
  free(my_answer);
}
END_TEST

START_TEST(all_lower) {
  char const str[] = "this text in lower case";
  char answer[] = "this text in lower case";
  char *my_answer = s21_to_lower(str);
  ck_assert_str_eq(my_answer, answer);
  free(my_answer);
}
END_TEST

START_TEST(mixed_case) {
  char const str[] = "tHis tExt iN MiXeD caSe";
  char answer[] = "this text in mixed case";
  char *my_answer = s21_to_lower(str);
  ck_assert_str_eq(my_answer, answer);
  free(my_answer);
}
END_TEST

START_TEST(nothing_to_do_1) {
  char const str[] = "123456";
  char answer[] = "123456";
  char *my_answer = s21_to_lower(str);
  ck_assert_str_eq(my_answer, answer);
  free(my_answer);
}
END_TEST

START_TEST(string_with_terminate_simbol) {
  char const str[] = "before termInate\0after terminate\0";
  char answer[] = "before terminate";
  char *my_answer = s21_to_lower(str);
  ck_assert_str_eq(my_answer, answer);
  free(my_answer);
}
END_TEST

START_TEST(one_letter_lower) {
  char const str[] = "a";
  char answer[] = "a";
  char *my_answer = s21_to_lower(str);
  ck_assert_str_eq(my_answer, answer);
  free(my_answer);
}
END_TEST

START_TEST(one_letter_upper) {
  char const str[] = "A";
  char answer[] = "a";
  char *my_answer = s21_to_lower(str);
  ck_assert_str_eq(my_answer, answer);
  free(my_answer);
}
END_TEST

START_TEST(null_str) {
  char const *str = NULL;
  char *answer = S21_NULL;
  char *my_answer = s21_to_lower(str);
  ck_assert_ptr_eq(answer, my_answer);
  free(my_answer);
}
END_TEST

START_TEST(nothing_to_do_2) {
  char const *str = "{|||}";
  char *answer = "{|||}";
  char *my_answer = s21_to_lower(str);
  ck_assert_str_eq(answer, my_answer);
  free(my_answer);
}
END_TEST

Suite *s21_to_lower_cases(void) {
  Suite *suite = suite_create("s21_to_lower_cases");
  TCase *tc = tcase_create("to_lower_tc");

  tcase_add_test(tc, empty_str);
  tcase_add_test(tc, all_lower);
  tcase_add_test(tc, all_upper);
  tcase_add_test(tc, mixed_case);
  tcase_add_test(tc, nothing_to_do_1);
  tcase_add_test(tc, nothing_to_do_2);
  tcase_add_test(tc, string_with_terminate_simbol);
  tcase_add_test(tc, one_letter_lower);
  tcase_add_test(tc, one_letter_upper);
  tcase_add_test(tc, null_str);

  suite_add_tcase(suite, tc);

  return suite;
}