#include "test_runner.h"

START_TEST(positive_err) {
  for (int i = -150; i <= 150; i++) {
    char *s21 = s21_strerror(i);
    char *original = strerror(i);
    ck_assert_str_eq(s21, original);
  }
}
END_TEST

START_TEST(negative_err) {
  char *original = S21_NULL;
  for (int i = -150; i < 0; i++) {
    char *s21 = s21_strerror(i);
    original = strerror(i);
    ck_assert_str_eq(s21, original);
  }
  free(original);
}
END_TEST

Suite *s21_strerror_cases(void) {
  Suite *s = suite_create("s21_strerror_cases");
  TCase *tc = tcase_create("s21_strerror_tc");

  tcase_add_test(tc, positive_err);
  tcase_add_test(tc, negative_err);

  suite_add_tcase(s, tc);
  return s;
}
