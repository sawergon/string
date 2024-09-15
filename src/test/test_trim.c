#include "test_runner.h"

START_TEST(src_trim_empty) {
  char const *src = "";
  char const *trim = "";
  char *actual = s21_trim(src, trim);
  if (actual) {
    ck_assert_str_eq(actual, "");
    free(actual);
  }
}
END_TEST

START_TEST(src_empty_trim_NULL) {
  char const *src = "";
  char const *actual = s21_trim(src, S21_NULL);
  ck_assert(actual == S21_NULL);
}
END_TEST

START_TEST(src_NULL_trim_empty) {
  char const *trim = "";
  char const *actual = s21_trim(S21_NULL, trim);
  ck_assert(actual == S21_NULL);
}
END_TEST

START_TEST(src_equals_trim) {
  char const *src = "test_trim_for_equality";
  char const *trim = "test_trim_for_equality";
  char *actual = s21_trim(src, trim);
  if (actual) {
    ck_assert_str_eq(actual, "");
    free(actual);
  }
}
END_TEST

START_TEST(trim_1) {
  char const *src = "test_trim_test";
  char const *trim = "test";
  char *actual = s21_trim(src, trim);
  if (actual) {
    ck_assert_str_eq(actual, "_trim_");
    free(actual);
  }
}
END_TEST

START_TEST(trim_2) {
  char const *src = "test_trim_test";
  char const *trim = "es";
  char *actual = s21_trim(src, trim);
  if (actual) {
    ck_assert_str_eq(actual, "test_trim_test");
    free(actual);
  }
}
END_TEST

START_TEST(trim_3) {
  char const *src = "test_trim_test";
  char const *trim = "trim";

  char *actual = s21_trim(src, trim);
  if (actual) {
    ck_assert_str_eq(actual, "est_trim_tes");
    free(actual);
  }
}
END_TEST

START_TEST(trim_4) {
  char const *src = "&* !!test * **";
  char const *trim = "&!* ";
  char *actual = s21_trim(src, trim);
  if (actual) {
    ck_assert_str_eq(actual, "test");
    free(actual);
  }
}
END_TEST

START_TEST(trim_spaces) {
  char const *src = "        test_trim_spaces         ";
  char const *trim = "";
  char *actual = s21_trim(src, trim);
  if (actual) {
    ck_assert_str_eq(actual, "test_trim_spaces");
    free(actual);
  }
}
END_TEST

Suite *s21_trim_cases(void) {
  Suite *suite = suite_create("s21_trim_cases");
  TCase *tc = tcase_create("trim_tc");

  tcase_add_test(tc, src_trim_empty);
  tcase_add_test(tc, src_empty_trim_NULL);
  tcase_add_test(tc, src_NULL_trim_empty);
  tcase_add_test(tc, src_equals_trim);
  tcase_add_test(tc, trim_spaces);

  tcase_add_test(tc, trim_1);
  tcase_add_test(tc, trim_2);
  tcase_add_test(tc, trim_3);
  tcase_add_test(tc, trim_4);

  suite_add_tcase(suite, tc);
  return suite;
}
