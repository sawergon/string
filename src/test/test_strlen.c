#include "test_runner.h"

START_TEST(Hello_school21) {
  const char str[] = "Hello_school21";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(Hello_world) {
  const char str[] = "Hello_world";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(Medical) {
  const char str[] = "Medical";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(Russia) {
  const char str[] = "Russia";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(London) {
  const char str[] = "London";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(Yes) {
  const char str[] = "Yes";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(Very_good_you_and_fine) {
  const char str[] = "Very_good_you_and_fine";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(Iphone) {
  const char str[] = "Iphone";
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

Suite *s21_strlen_cases(void) {
  Suite *c = suite_create("s21_strlen_cases");
  TCase *tc = tcase_create("s21_strlen_tc");

  tcase_add_test(tc, Hello_school21);
  tcase_add_test(tc, Hello_world);
  tcase_add_test(tc, Medical);
  tcase_add_test(tc, Russia);
  tcase_add_test(tc, London);
  tcase_add_test(tc, Yes);
  tcase_add_test(tc, Very_good_you_and_fine);
  tcase_add_test(tc, Iphone);

  suite_add_tcase(c, tc);
  return c;
}