#include "test_runner.h"

START_TEST(normal_search) {
  s21_size_t num_bytes = 5;
  char str[18] = "Hello, School21!";
  int find_byte = 'e';

  ck_assert_ptr_eq(s21_memchr(str, find_byte, num_bytes),
                   memchr(str, find_byte, num_bytes));
}
END_TEST

START_TEST(empty_string) {
  s21_size_t num_bytes = 0;
  char str[18] = "";
  int find_byte = '\0';

  ck_assert_ptr_eq(s21_memchr(str, find_byte, num_bytes),
                   memchr(str, find_byte, num_bytes));
}
END_TEST

START_TEST(find_first_symbol) {
  s21_size_t num_bytes = 5;
  char str[18] = "Hello, School21!";
  int find_byte = 'H';

  ck_assert_ptr_eq(s21_memchr(str, find_byte, num_bytes),
                   memchr(str, find_byte, num_bytes));
}
END_TEST

START_TEST(find_last_symbol) {
  s21_size_t num_bytes = 18;
  char str[18] = "Hello, School21!";
  int find_byte = '!';

  ck_assert_ptr_eq(s21_memchr(str, find_byte, num_bytes),
                   memchr(str, find_byte, num_bytes));
}
END_TEST

START_TEST(find_no_symbol) {
  s21_size_t num_bytes = 10;
  char str[18] = "Hello, School21!";
  int find_byte = 't';

  ck_assert_ptr_eq(s21_memchr(str, find_byte, num_bytes),
                   memchr(str, find_byte, num_bytes));
}
END_TEST

Suite *s21_memchr_cases(void) {
  Suite *s = suite_create("s21_memchr_cases");
  TCase *tc = tcase_create("tc_memchr");

  tcase_add_test(tc, normal_search);
  tcase_add_test(tc, empty_string);
  tcase_add_test(tc, find_first_symbol);
  tcase_add_test(tc, find_last_symbol);
  tcase_add_test(tc, find_no_symbol);

  suite_add_tcase(s, tc);
  return s;
}