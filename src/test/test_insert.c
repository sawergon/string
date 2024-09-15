#include "test_runner.h"

START_TEST(src_str_empty) {
  char const *src = "";
  char const *str = "";
  char *actual = s21_insert(src, str, 0);
  if (actual) {
    ck_assert_str_eq(actual, "");
    free(actual);
  }
}
END_TEST

START_TEST(src_empty_str_NULL) {
  char const *src = "";
  char const *actual = s21_insert(src, S21_NULL, 0);
  ck_assert(actual == S21_NULL);
}
END_TEST

START_TEST(src_NULL_str_empty) {
  char const *str = "";
  char const *actual = s21_insert(S21_NULL, str, 0);
  ck_assert(actual == S21_NULL);
}
END_TEST

START_TEST(src_NULL_str_NULL) {
  char const *actual = s21_insert(S21_NULL, S21_NULL, 0);
  ck_assert(actual == S21_NULL);
}
END_TEST

START_TEST(big_start_index) {
  char const *src = "test";
  char const *str = "_insert";
  char const *actual = s21_insert(src, str, 100);
  ck_assert(actual == S21_NULL);
}
END_TEST

START_TEST(insert_1) {
  char const *src = "test__test";
  char const *str = "test";
  char *actual = s21_insert(src, str, 5);
  if (actual) {
    ck_assert_str_eq(actual, "test_test_test");
    free(actual);
  }
}
END_TEST

START_TEST(insert_2) {
  char const *src = "test";
  char const *str = "begin_";
  char *actual = s21_insert(src, str, 0);
  if (actual) {
    ck_assert_str_eq(actual, "begin_test");
    free(actual);
  }
}
END_TEST

START_TEST(insert_3) {
  char const *src = "test";
  char const *str = "_end";

  char *actual = s21_insert(src, str, 4);
  if (actual) {
    ck_assert_str_eq(actual, "test_end");
    free(actual);
  }
}
END_TEST

START_TEST(insert_spaces) {
  char const *src = "        test_trim_spaces         ";
  char const *str = "  ";
  char *actual = s21_insert(src, str, 17);
  if (actual) {
    ck_assert_str_eq(actual, "        test_trim  _spaces         ");
    free(actual);
  }
}
END_TEST

Suite *s21_insert_cases(void) {
  Suite *suite = suite_create("s21_insert_cases");
  TCase *tc = tcase_create("insert_tc");

  tcase_add_test(tc, src_str_empty);
  tcase_add_test(tc, src_empty_str_NULL);
  tcase_add_test(tc, src_NULL_str_empty);
  tcase_add_test(tc, src_NULL_str_NULL);
  tcase_add_test(tc, big_start_index);

  tcase_add_test(tc, insert_1);
  tcase_add_test(tc, insert_2);
  tcase_add_test(tc, insert_3);
  tcase_add_test(tc, insert_spaces);

  suite_add_tcase(suite, tc);
  return suite;
}
