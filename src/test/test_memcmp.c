#include "test_runner.h"

START_TEST(equal_char_strings) {
  const char str1[] = "Hello, School21!";
  const char str2[] = "Hello, School21!";
  ;
  s21_size_t num_size = 10;

  ck_assert_int_eq(s21_memcmp(str1, str2, num_size),
                   memcmp(str1, str2, num_size));
}
END_TEST

START_TEST(equal_int_strings) {
  const char str1[] = "123 12345 234125";
  const char str2[] = "123 12345 234125";
  ;
  s21_size_t num_size = 10;

  ck_assert_int_eq(s21_memcmp(str1, str2, num_size),
                   memcmp(str1, str2, num_size));
}
END_TEST

START_TEST(equal_empty_strings) {
  const char str1[] = "";
  const char str2[] = "";
  ;
  s21_size_t num_size = 0;

  ck_assert_int_eq(s21_memcmp(str1, str2, num_size),
                   memcmp(str1, str2, num_size));
}
END_TEST

START_TEST(unequal_char_strings) {
  const char str1[] = "Hello, School21!";
  const char str2[] = "Goodbye, School21!";
  ;
  s21_size_t num_size = 10;

  ck_assert_int_eq(s21_memcmp(str1, str2, num_size),
                   memcmp(str1, str2, num_size));
}
END_TEST

START_TEST(unequal_int_strings) {
  const char str1[] = "123 12345 234125";
  const char str2[] = "54352 34523 3323";
  ;
  s21_size_t num_size = 10;

  ck_assert_int_eq(s21_memcmp(str1, str2, num_size),
                   memcmp(str1, str2, num_size));
}
END_TEST

START_TEST(one_empty_string) {
  const char str1[] = "Hello, School21!";
  const char str2[] = "";
  ;
  s21_size_t num_size = 0;

  ck_assert_int_eq(s21_memcmp(str1, str2, num_size),
                   memcmp(str1, str2, num_size));
}
END_TEST

START_TEST(first_byte_int_strings) {
  const char str1[] = "1";
  const char str2[] = "123 12345 234125";
  ;
  s21_size_t num_size = 1;

  ck_assert_int_eq(s21_memcmp(str1, str2, num_size),
                   memcmp(str1, str2, num_size));
}
END_TEST

START_TEST(first_byte_char_strings) {
  const char str1[] = "H";
  const char str2[] = "Hello, School21!";
  ;
  s21_size_t num_size = 1;

  ck_assert_int_eq(s21_memcmp(str1, str2, num_size),
                   memcmp(str1, str2, num_size));
}
END_TEST

START_TEST(last_byte_char_strings) {
  const char str1[] = "Hello, School21.";
  const char str2[] = "Hello, School21!";
  ;
  s21_size_t num_size = 16;

  ck_assert_int_eq(s21_memcmp(str1, str2, num_size),
                   memcmp(str1, str2, num_size));
}
END_TEST

START_TEST(last_byte_int_strings) {
  const char str1[] = "123 12345 234125";
  const char str2[] = "123 12345 234121";
  ;
  s21_size_t num_size = 16;

  ck_assert_int_eq(s21_memcmp(str1, str2, num_size),
                   memcmp(str1, str2, num_size));
}
END_TEST

START_TEST(long_char_strings) {
  const char str1[] =
      "Hello, "
      "School21!aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  const char str2[] =
      "Hello, "
      "School21!aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  s21_size_t num_size = 50;

  ck_assert_int_eq(s21_memcmp(str1, str2, num_size),
                   memcmp(str1, str2, num_size));
}
END_TEST

START_TEST(long_int_strings) {
  const char str1[] =
      "123 12345 "
      "234125111111111111111111111111111111111111111111111111111111111111";
  const char str2[] =
      "123 12345 "
      "234125111111111111111111111111111111111111111111111111111111111111";
  ;
  s21_size_t num_size = 50;

  ck_assert_int_eq(s21_memcmp(str1, str2, num_size),
                   memcmp(str1, str2, num_size));
}
END_TEST

Suite *s21_memcmp_cases(void) {
  Suite *s = suite_create("s21_memcmp_cases");
  TCase *tc = tcase_create("tc_memcmp");

  tcase_add_test(tc, equal_char_strings);
  tcase_add_test(tc, equal_int_strings);
  tcase_add_test(tc, equal_empty_strings);
  tcase_add_test(tc, unequal_char_strings);
  tcase_add_test(tc, unequal_int_strings);
  tcase_add_test(tc, one_empty_string);
  tcase_add_test(tc, first_byte_int_strings);
  tcase_add_test(tc, first_byte_char_strings);
  tcase_add_test(tc, last_byte_char_strings);
  tcase_add_test(tc, last_byte_int_strings);
  tcase_add_test(tc, long_char_strings);
  tcase_add_test(tc, long_int_strings);

  suite_add_tcase(s, tc);
  return s;
}