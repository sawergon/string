#include "test_runner.h"

START_TEST(delim_1) {
  char str1[] = "123456789";
  char str2[] = "123456789";
  const char delim[] = "+21_!";
  char *s21_token = s21_strtok(str1, delim);
  char *std_token = strtok(str2, delim);

  ck_assert_str_eq(s21_token, std_token);

  ck_assert_ptr_null(s21_strtok(S21_NULL, delim));
  ck_assert_ptr_null(strtok(S21_NULL, delim));
}
END_TEST

START_TEST(delim_2) {
  char str1[] = "VeryGoodForYou";
  char str2[] = "VeryGoodForYou";
  const char delim[] = "+21_!";
  char *s21_token = s21_strtok(str1, delim);
  char *std_token = strtok(str2, delim);
  ck_assert_uint_eq(s21_strlen(s21_token), s21_strlen(std_token));
  ck_assert_str_eq(s21_token, std_token);
  while (s21_token && std_token) {
    s21_token = s21_strtok(S21_NULL, delim);
    std_token = strtok(S21_NULL, delim);
    ck_assert_uint_eq(s21_strlen(s21_token), s21_strlen(std_token));
    if (s21_token || std_token) {
      ck_assert_str_eq(s21_token, std_token);
    } else {
      ck_assert_ptr_null(s21_token);
      ck_assert_ptr_null(std_token);
    }
  }
}
END_TEST

START_TEST(delim_3) {
  char str1[] = "ManyManyMany123456789LowLowLow ++++=======123!!!!!";
  char str2[] = "ManyManyMany123456789LowLowLow ++++=======123!!!!!";
  const char delim[] = "+21_!";
  char *s21_token = s21_strtok(str1, delim);
  char *std_token = strtok(str2, delim);
  ck_assert_uint_eq(s21_strlen(s21_token), s21_strlen(std_token));
  ck_assert_str_eq(s21_token, std_token);
  while (s21_token && std_token) {
    s21_token = s21_strtok(S21_NULL, delim);
    std_token = strtok(S21_NULL, delim);
    ck_assert_uint_eq(s21_strlen(s21_token), s21_strlen(std_token));
    if (s21_token || std_token) {
      ck_assert_str_eq(s21_token, std_token);
    } else {
      ck_assert_ptr_null(s21_token);
      ck_assert_ptr_null(std_token);
    }
  }
}
END_TEST

START_TEST(delim_4) {
  char str1[] = "+++====!!!!!????? VeryHard????????+++++++++======= done";
  char str2[] = "+++====!!!!!????? VeryHard????????+++++++++======= done";
  const char delim[] = "+21_!";
  char *s21_token = s21_strtok(str1, delim);
  char *std_token = strtok(str2, delim);
  ck_assert_uint_eq(s21_strlen(s21_token), s21_strlen(std_token));
  ck_assert_str_eq(s21_token, std_token);
  while (s21_token && std_token) {
    s21_token = s21_strtok(S21_NULL, delim);
    std_token = strtok(S21_NULL, delim);
    ck_assert_uint_eq(s21_strlen(s21_token), s21_strlen(std_token));
    if (s21_token || std_token) {
      ck_assert_str_eq(s21_token, std_token);
    } else {
      ck_assert_ptr_null(s21_token);
      ck_assert_ptr_null(std_token);
    }
  }
}
END_TEST

START_TEST(delim_5) {
  char str1[] = "     school21______+  d!o?n)e! Work_not! l_0_v_e";
  char str2[] = "     school21______+  d!o?n)e! Work_not! l_0_v_e";
  const char delim[] = "+21_!";
  char *s21_token = s21_strtok(str1, delim);
  char *std_token = strtok(str2, delim);
  ck_assert_uint_eq(s21_strlen(s21_token), s21_strlen(std_token));
  ck_assert_str_eq(s21_token, std_token);
  while (s21_token && std_token) {
    s21_token = s21_strtok(S21_NULL, delim);
    std_token = strtok(S21_NULL, delim);
    ck_assert_uint_eq(s21_strlen(s21_token), s21_strlen(std_token));
    if (s21_token || std_token) {
      ck_assert_str_eq(s21_token, std_token);
    } else {
      ck_assert_ptr_null(s21_token);
      ck_assert_ptr_null(std_token);
    }
  }
}
END_TEST

START_TEST(empty_6) {
  char str1[] = "";
  char str2[] = "";
  const char delim[] = "";
  char *s21_token = s21_strtok(str1, delim);
  char *std_token = strtok(str2, delim);

  ck_assert_ptr_null(s21_token);
  ck_assert_ptr_null(std_token);

  ck_assert_ptr_null(s21_strtok(S21_NULL, delim));
  ck_assert_ptr_null(strtok(S21_NULL, delim));
}
END_TEST

Suite *s21_strtok_cases(void) {
  Suite *s = suite_create("s21_strtok_cases");
  TCase *tc = tcase_create("s21_strtok_tc");

  tcase_add_test(tc, delim_1);
  tcase_add_test(tc, delim_2);
  tcase_add_test(tc, delim_3);
  tcase_add_test(tc, delim_4);
  tcase_add_test(tc, delim_5);
  tcase_add_test(tc, empty_6);
  suite_add_tcase(s, tc);

  return s;
}