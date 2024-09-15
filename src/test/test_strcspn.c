#include "test_runner.h"

START_TEST(empty) {
  const char src[] = "";
  const char des[] = "";

  ck_assert_int_eq(s21_strcspn(des, src), strcspn(des, src));
}
END_TEST

START_TEST(abc_) {
  const char src[] = "abc";
  const char des[] = "";

  ck_assert_int_eq(s21_strcspn(des, src), strcspn(des, src));
}
END_TEST

START_TEST(_abc) {
  const char src[] = "";
  const char des[] = "abc";

  ck_assert_int_eq(s21_strcspn(des, src), strcspn(des, src));
}
END_TEST

START_TEST(register_case) {
  const char src[] = "abc";
  const char des[] = "aBc";

  ck_assert_int_eq(s21_strcspn(des, src), strcspn(des, src));
}
END_TEST

START_TEST(num_num) {
  const char src[] = "12345";
  const char des[] = "12345";

  ck_assert_int_eq(s21_strcspn(des, src), strcspn(des, src));
}
END_TEST

START_TEST(longnum_num) {
  const char src[] = "12345";
  const char des[] = "123";

  ck_assert_int_eq(s21_strcspn(des, src), strcspn(des, src));
}
END_TEST

START_TEST(num_longnum) {
  const char src[] = "123";
  const char des[] = "12345";

  ck_assert_int_eq(s21_strcspn(des, src), strcspn(des, src));
}
END_TEST

START_TEST(any_num) {
  const char src[] = "1122334455";
  const char des[] = "5544332211";

  ck_assert_int_eq(s21_strcspn(des, src), strcspn(des, src));
}
END_TEST

START_TEST(num_letter_case) {
  const char src[] = "a1bbb23ccc41235";
  const char des[] = "235";

  ck_assert_int_eq(s21_strcspn(des, src), strcspn(des, src));
}
END_TEST

START_TEST(num_letter_CASE) {
  const char src[] = "1A2B3C4D5E";
  const char des[] = "123";

  ck_assert_int_eq(s21_strcspn(des, src), strcspn(des, src));
}
END_TEST

START_TEST(easy_test) {
  const char src[] = "abcdE";
  const char des[] = "acdE";

  ck_assert_int_eq(s21_strcspn(des, src), strcspn(des, src));
}
END_TEST

START_TEST(some_chars) {
  const char src[] = "42hellobyegoodbyenotfarewell1234567890";
  const char des[] = "0987654321";

  ck_assert_int_eq(s21_strcspn(des, src), strcspn(des, src));
}
END_TEST

START_TEST(upper_case) {
  const char src[] = "YOUDONTHACKME42BUYTRY1234567890";
  const char des[] = "42HACKMEDONTTRY54321";

  ck_assert_int_eq(s21_strcspn(des, src), strcspn(des, src));
}
END_TEST

START_TEST(lower_case) {
  const char src[] = "youdonthackme42buttry1234567890";
  const char des[] = "42hackmedonttry54321";

  ck_assert_int_eq(s21_strcspn(des, src), strcspn(des, src));
}
END_TEST

START_TEST(very_long) {
  const char src[] =
      "555555555555555555555555555555555555555555555555555555555555555555555555"
      "55555555555555";
  const char des[] =
      "111111111111111111111111111111111111111111111111111111111111111111111115"
      "11111111111111";

  ck_assert_int_eq(s21_strcspn(des, src), strcspn(des, src));
}
END_TEST

Suite *s21_strcspn_cases(void) {
  Suite *s = suite_create("s21_strcspn_cases");
  TCase *tc = tcase_create("s21_strcspn_tc");

  tcase_add_test(tc, empty);
  tcase_add_test(tc, abc_);
  tcase_add_test(tc, _abc);
  tcase_add_test(tc, register_case);
  tcase_add_test(tc, num_num);
  tcase_add_test(tc, longnum_num);
  tcase_add_test(tc, num_longnum);
  tcase_add_test(tc, any_num);
  tcase_add_test(tc, num_letter_case);
  tcase_add_test(tc, num_letter_CASE);
  tcase_add_test(tc, easy_test);
  tcase_add_test(tc, some_chars);
  tcase_add_test(tc, upper_case);
  tcase_add_test(tc, lower_case);
  tcase_add_test(tc, very_long);

  suite_add_tcase(s, tc);
  return s;
}
