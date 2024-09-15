#include "test_runner.h"

START_TEST(null_both) {
  int a = 0;

  int res1 = s21_sscanf(S21_NULL, S21_NULL, &a);

  ck_assert_int_eq(res1, -1);
}
END_TEST

START_TEST(without_format_str) {
  int a = 0, b = 0;
  const char *str = "some_str";
  const char *format_str = "str%_without_format";

  int res1 = s21_sscanf(str, format_str, &a);
  int res2 = sscanf(str, format_str, &b);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(empty_str) {
  int a = 0, b = 0;
  int res1 = s21_sscanf("", "%d", &a);
  int res2 = sscanf("", "%d", &b);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(no_valid_str) {
  int a = 0, b = 0;

  const char str[] = "\0\n";
  const char format_str[] = "   ";

  int res1 = s21_sscanf(str, format_str, &a);
  int res2 = sscanf(str, format_str);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(w_space_str_1) {
  int a = 0, b = 0;
  int res1 = s21_sscanf(" ", "%d", &a);
  int res2 = sscanf(" ", "%d", &b);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(w_space_str_2) {
  int a = 0, b = 0;
  int res1 = s21_sscanf("            ", "%d", &a);
  int res2 = sscanf("            ", "%d", &b);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(opt_d_1_short) {
  short sa = 0, sb = 0, sc = 0, sd = 0;

  ck_assert_int_eq(s21_sscanf("123456123", "%6hd%hd", &sa, &sb),
                   sscanf("123456123", "%6hd%hd", &sc, &sd));
  ck_assert_int_eq(sa, sc);
  ck_assert_int_eq(sb, sd);
}
END_TEST

START_TEST(opt_d_1_int) {
  int a = 0, b = 0;

  ck_assert_int_eq(s21_sscanf("12345678901", "%d", &a),
                   sscanf("12345678901", "%d", &b));
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(opt_d_1_long) {
  long la = 0, lb = 0;

  ck_assert_int_eq(s21_sscanf("-12345678901", "%ld", &la),
                   sscanf("-12345678901", "%ld", &lb));
  ck_assert_int_eq(la, lb);
}
END_TEST

START_TEST(opt_d_1_longlong) {
  long long lla = 0, llb = 0;

  ck_assert_int_eq(s21_sscanf("123456789012345", "%lld", &lla),
                   sscanf("123456789012345", "%lld", &llb));
  ck_assert_int_eq(lla, llb);
}
END_TEST

START_TEST(opt_d_int_p) {
  int a1 = 0, b1 = 0;
  int *a2 = 0, *b2 = 0;

  ck_assert_int_eq(s21_sscanf("  123 0x7fff28e35250", "%d %p", &a1, &a2),
                   sscanf("  123 0x7fff28e35250", "%d %p", &b1, &b2));
  ck_assert_int_eq(a1, b1);
  ck_assert_ptr_nonnull(a2);
  ck_assert_ptr_nonnull(b2);
}
END_TEST

START_TEST(opt_d_1_overflow) {
  long la = 0, lb = 0, lc = 0, ld = 0;

  ck_assert_int_eq(s21_sscanf("12345678901234567890", "%ld", &la),
                   sscanf("12345678901234567890", "%ld", &lb));
  ck_assert_int_eq(la, lb);

  ck_assert_int_eq(s21_sscanf("-12345678901234567890", "%ld", &la),
                   sscanf("-12345678901234567890", "%ld", &lb));
  ck_assert_int_eq(la, lb);

  lb = 0;
  ck_assert_int_eq(s21_sscanf("19223372036854775807", "%ld%ld", &la, &lb),
                   sscanf("19223372036854775807", "%ld%ld", &lc, &ld));
  ck_assert_int_eq(la, lc);
  ck_assert_int_eq(lb, ld);
}
END_TEST

START_TEST(opt_d_int_1) {
  long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *format_str = "%ld %ld %ld %ld";
  const char *str = "555 666 777 888";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_d_int_2) {
  short a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *str = "3456 21 7789 3000";
  const char *format_str = "%hd %hd %hd %hd";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_d_int_3) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *str = "4555 21 21311 345768";
  const char *format_str = "%lld %lld %lld %lld";

  int16_t res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_d_int_stat_width_1) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *str = "2234 21 5008 300004";
  const char *format_str = "%1lld %3lld %1lld %4lld";

  int16_t res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_d_int_stat_width_2) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *str = "4567";
  const char *format_str = "%1lld %1lld %1lld %1lld";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_d_int_stat_width_3) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *str = "100000000000000009";
  const char *format_str = "%3lld%lld%1lld%5lld";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_d_int_stat_width_4) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *str = "2346";
  const char *format_str = "%15lld %1lld %1lld %1lld";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_d_int_dyn_width_1) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  const char *str = "1337123123 1 123412341234 1 999999 0";
  const char *format_str = "%*d %lld %*d %lld %*d %lld";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(opt_d_int_dyn_width_2) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *str = "8865";
  const char *format_str = "%15lld %1lld %1lld %1lld";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_d_int_dyn_width_3) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *str = "55555555";
  const char *format_str = "%3lld%lld%1lld%5lld";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_d_int_dyn_width_4) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *str = "987654321";
  const char *format_str = "%15lld %1lld %1lld %1lld";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_d_int_sign_1) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *str = "11337 ++3 -5 ------4";
  const char *format_str = "%lld %lld %lld %lld";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_d_int_sign_2) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *str = "-2331 +1 -12 -1";
  const char *format_str = "%15lld %1lld %1lld %5lld";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_d_int_sign_3) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *str = "-0 +0 +0 -0";
  const char *format_str = "%2lld %1lld %1lld %1lld";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_d_int_sign_4) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *str = "1 01 10 0";
  const char *format_str = "%lld %lld %lld %lld";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_d_1_other) {
  int a = 0, b = 0;

  ck_assert_int_eq(s21_sscanf("abc", "%d", &a), sscanf("abc", "%d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("123", "%5d", &a), sscanf("123", "%5d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("++321", "%d", &a), sscanf("++321", "%d", &b));
  ck_assert_int_eq(a, b);

  ck_assert_int_eq(s21_sscanf("+321", "%d", &a), sscanf("+321", "%d", &b));
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(char_1) {
  char const *format_str = "%c %c %c %c";
  char const *str = "   a     b c d";
  int a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(char_2) {
  char const *format_str = "%c%c%c%c";
  char const *str = "char";
  int a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(char_3) {
  char const *format_str = "%c %c %c      %c";
  char const *str = "1 a 3   c           ";
  int a1 = 0, a2 = 5, b1 = 0, b2 = 5, c1 = 0, c2 = 5, d1 = 0, d2 = 5;

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(char_ast) {
  int a1 = 0, a2 = 0;

  char const *format_str = "%*c%*c%*c%c";
  char const *str = "abcd ";

  int res1 = s21_sscanf(str, format_str, &a1);
  int res2 = sscanf(str, format_str, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(opt_i_int_1) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char *str = "300 500 -600 +700";
  const char *format_str = "%lli %lli %lli %lli";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_i_int_2) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char *str = "500500-444+700 111";
  const char *format_str = "%lli %lld %lld %lli";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_i_int_3) {
  long long a1 = 0, a2 = 0, c1 = 0, c2 = 0;
  char b1 = 0, b2 = 0, d1 = 0, d2 = 0;
  const char *str = "311340-600+700+400";
  const char *format_str = "%lli%c%lli%c";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_i_int_4) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char *str = "  23435 f f f5542555 ddd   4    2    1 ";
  const char *format_str = "%lli %lld %lld %lli";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_i_uint_no_prefix) {
  int a, b;
  const char *str = "1234567890";
  const char *format_str = "%i";

  a = b = 0;
  ck_assert_int_eq(s21_sscanf(str, format_str, &a),
                   sscanf(str, format_str, &b));
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(opt_i_uint_oct_prefix) {
  int a, b;
  const char *str = "01234567";
  const char *format_str = "%i";

  a = b = 0;
  ck_assert_int_eq(s21_sscanf(str, format_str, &a),
                   sscanf(str, format_str, &b));
  ck_assert_int_eq(a, b);
}

START_TEST(opt_i_uint_hex_prefix) {
  int a, b;
  const char *str = "0x1234567890";
  const char *format_str = "%i";

  a = b = 0;
  ck_assert_int_eq(s21_sscanf(str, format_str, &a),
                   sscanf(str, format_str, &b));
  ck_assert_int_eq(a, b);
}

START_TEST(opt_i_uint_negative) {
  int a, b;
  const char *str = "-1234567890";
  const char *format_str = "%i";

  a = b = 0;
  ck_assert_int_eq(s21_sscanf(str, format_str, &a),
                   sscanf(str, format_str, &b));
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(opt_i_uint_negative_oct_prefix) {
  int a, b;
  const char *str = "-01234567";
  const char *format_str = "%i";

  a = b = 0;
  ck_assert_int_eq(s21_sscanf(str, format_str, &a),
                   sscanf(str, format_str, &b));
  ck_assert_int_eq(a, b);
}

START_TEST(opt_i_uint_negative_hex_prefix) {
  int a, b;
  const char *str = "-0x1234567890";
  const char *format_str = "%i";

  a = b = 0;
  int res1 = s21_sscanf(str, format_str, &a);
  int res2 = sscanf(str, format_str, &b);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}

START_TEST(opt_i_uint_negative_hex_without_prefix) {
  int a, b;
  const char *str = "-123abcdef";
  const char *format_str = "%i";

  a = b = 0;
  ck_assert_int_eq(s21_sscanf(str, format_str, &a),
                   sscanf(str, format_str, &b));
  ck_assert_int_eq(a, b);
}

START_TEST(opt_i_uint_positive_hex_with_plus_prefix) {
  int a, b;
  const char *str = "+0xfaf";
  const char *format_str = "%i";

  a = b = 0;
  int res1 = s21_sscanf(str, format_str, &a);
  int res2 = sscanf(str, format_str, &b);

  ck_assert_int_eq(a, b);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(opt_i_hex_1) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *str = "0xFFF 0xA123123 0x123123 0x0";
  const char *format_str = "%lli %lli %lli %lli";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_i_hex_2) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *str = " 0xFFFF 0xf 0xf 0xf5555555 ddd   4    3    1 ";
  const char *format_str = "%lli %lli %lli %lli";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_i_oct_1) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *str = "  055555 0f 0f 0f5555555 0ddd   4    3    1 ";
  const char *format_str = "%lli %lld %lld %lli";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_i_oct_2) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *str = "  055555 0f 0f 0f5555555 0ddd   4    3    1 ";
  const char *format_str = "%lli %lld %lld %lli";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_n_1) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int n1 = 0, n2 = 5;

  const char str[BUFF_SIZE] = "22 111 33 44";
  const char format_str[BUFF_SIZE] = "%lli %lli %n %lli %lli";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &n1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &n2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_n_2) {
  int n1 = 1, n2 = 5;

  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};

  const char *str = "lorem fl? ipsum welw astra 1234";
  const char *format_str = "%s %s %n %s";

  int res1 = s21_sscanf(str, format_str, s1, s2, &n1, s3);
  int res2 = sscanf(str, format_str, s5, s6, &n2, s7);

  ck_assert_int_eq(res1, res2);

  ck_assert_int_eq(n1, n2);
  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
}
END_TEST

START_TEST(opt_n_3) {
  int n1 = 0, n2 = 5;

  const char str[BUFF_SIZE] = "50 60 70 80";
  const char format_str[BUFF_SIZE] = "%n";

  int res1 = s21_sscanf(str, format_str, &n1);
  int res2 = sscanf(str, format_str, &n2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(opt_n_4) {
  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  int n1 = 0, n2 = 5;

  const char *str = "11 22 33 44";
  const char *format_str = "%lli %lli %n %lli %lli";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &n1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &n2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_n_5) {
  char buf1[100] = {0};
  char buf2[100] = {0};
  int a = 0;
  int b = 0;

  const char *str = "1234567890";
  const char *format_str = "%5s%n";

  int res1 = s21_sscanf(str, format_str, buf1, &a);
  int res2 = sscanf(str, format_str, buf2, &b);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(opt_n_6) {
  char buf1[100] = {0};
  char buf2[100] = {0};
  int a = 0;
  int b = 0;

  const char *str = "";
  const char *format_str = "%s%n";

  int res1 = s21_sscanf(str, format_str, buf1, &a);
  int res2 = sscanf(str, format_str, buf2, &b);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(opt_f_1) {
  long double a1 = 1, a2 = 0, b1 = 1, b2 = 0, c1 = 1, c2 = 0, d1 = 1, d2 = 0;

  const char *str = "538.1 -3.1335 81.346 +2.0801";
  const char *format_str = "%Lf %Lf %Lf %Lf";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(opt_f_2) {
  double a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char *str = "0.00001 -4123123 4. .";
  const char *format_str = "%lf %lf %lf %lf";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(opt_f_3) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char *str = ". . . .";
  const char *format_str = "%f %f %f %f";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(opt_f_4) {
  long double a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char *str = "53.41 -7.1435 324.33443 +142.0001";
  const char *format_str = "%Lf %Lf %Lf %Lf";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(opt_f_5) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;

  const char *str = "544.1 -6.116665 416331.3433 +8.0001";
  const char *format_str = "%*f %f %f %f";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(a1, a2);
  ck_assert_float_eq(b1, b2);
  ck_assert_float_eq(c1, c2);
}
END_TEST

START_TEST(opt_f_6) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char *str = "4.44 2.31e+4 -7.31e-4 0.448e-5";
  const char *format_str = "%G %G %G %G";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(opt_f_7) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char *str = "inf 1.31e+4 NaN 0.444e-5";
  const char *format_str = "%G %G %G %G";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_float_nan(c1);
  ck_assert_float_nan(c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(opt_f_8) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char *str = "inF InF inF INF";
  const char *format_str = "%G %G %G %G";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(a1, a2);
  ck_assert_double_eq(b1, b2);
  ck_assert_double_eq(c1, c2);
  ck_assert_double_eq(d1, d2);
}
END_TEST

START_TEST(opt_f_9) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char *str = "Nan NAN 0.0000 0";
  const char *format_str = "%G %G %G %G";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_nan(a1);
  ck_assert_float_nan(a2);
  ck_assert_float_nan(b1);
  ck_assert_float_nan(b2);
  ck_assert_ldouble_eq(c1, c2);
  ck_assert_ldouble_eq(d1, d2);
}
END_TEST

START_TEST(opt_f_10) {
  float a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char *str = "nAN     INF            -0.1111       1e-10";
  const char *format_str = "%G %G %G %G";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_nan(a1);
  ck_assert_float_nan(a2);
  ck_assert_ldouble_eq(b1, b2);
  ck_assert_ldouble_eq(c1, c2);
  ck_assert_ldouble_eq(d1, d2);
}
END_TEST

START_TEST(opt_f_neg_width) {
  float a = 0, b = 0;

  const char *str = "12345.30009";
  const char *format_str = "%-4f";

  int res1 = s21_sscanf(str, format_str, &a);
  int res2 = sscanf(str, format_str, &b);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(opt_f_e) {
  float a = 0, b = 0;

  const char *str = "1.23e-4";
  const char *format_str = "%e";

  int res1 = s21_sscanf(str, format_str, &a);
  int res2 = sscanf(str, format_str, &b);

  ck_assert_int_eq(res1, res2);
  ck_assert_double_eq(a, b);
}
END_TEST

START_TEST(opt_f_E) {
  float a = 0, b = 0;

  const char *str = "1.23E10";
  const char *format_str = "%6E";

  int res1 = s21_sscanf(str, format_str, &a);
  int res2 = sscanf(str, format_str, &b);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(opt_f_with_width_1) {
  float a = 0, b = 0;
  const char *str = "123.456";
  const char *format_str = "%.2f";

  int res1 = s21_sscanf(str, format_str, &a);
  int res2 = sscanf(str, format_str, &b);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(opt_f_with_width_2) {
  float a = 0, b = 0;
  const char *str = "123.456";
  const char *format_str = "%6f";

  int res1 = s21_sscanf(str, format_str, &a);
  int res2 = sscanf(str, format_str, &b);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(opt_Lf) {
  long double a1 = 0, a2 = 0;

  const char *str = "1.8e+28";
  const char *format_str = "%Lf";

  int res1 = s21_sscanf(str, format_str, &a1);
  int res2 = sscanf(str, format_str, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(a1, a2);
}
END_TEST

START_TEST(opt_Le) {
  long double a1 = 0, a2 = 0;

  const char *str = "1.4e+23";
  const char *format_str = "%Le";

  int res1 = s21_sscanf(str, format_str, &a1);
  int res2 = sscanf(str, format_str, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(a1, a2);
}
END_TEST

START_TEST(opt_LE) {
  long double a1 = 0, a2 = 0;

  const char *str = "1.4E+23";
  const char *format_str = "%LE";

  int res1 = s21_sscanf(str, format_str, &a1);
  int res2 = sscanf(str, format_str, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(a1, a2);
}
END_TEST

START_TEST(opt_Lg) {
  long double a1 = 0, a2 = 0;

  const char *str = "1.0e+23";
  const char *format_str = "%Lg";

  int res1 = s21_sscanf(str, format_str, &a1);
  int res2 = sscanf(str, format_str, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(a1, a2);
}
END_TEST

START_TEST(opt_LG) {
  long double a1 = 0, a2 = 0;

  const char *str = "1.0e+11";
  const char *format_str = "%LG";

  int res1 = s21_sscanf(str, format_str, &a1);
  int res2 = sscanf(str, format_str, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ldouble_eq(a1, a2);
}
END_TEST

START_TEST(opt_s_1) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};
  char s8[BUFF_SIZE] = {'\0'};

  const char *str = "test string Scaning with S21_sscanf";
  const char *format_str = "%s %s %s %s";

  int res1 = s21_sscanf(str, format_str, s1, s2, s3, s4);
  int res2 = sscanf(str, format_str, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(opt_s_2) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};
  char s8[BUFF_SIZE] = {'\0'};

  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char *str = "test 123 String -3 With 123sample 124papmks 3";
  const char *format_str = "%s%ld%s%d%s%d%s";

  int res1 = s21_sscanf(str, format_str, s1, &a1, s2, &b1, s3, &c1, s4, &d1);
  int res2 = s21_sscanf(str, format_str, s5, &a2, s6, &b2, s7, &c2, s8, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(opt_s_4) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};
  char s8[BUFF_SIZE] = {'\0'};

  const char *str = "test\tagain test and again ap r g a F";
  const char format_str[] = "%*s%*s%*s%*s";

  int res1 = s21_sscanf(str, format_str);
  int res2 = sscanf(str, format_str);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(opt_s_5) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};
  char s8[BUFF_SIZE] = {'\0'};

  const char *str = "test\tand\ttest\tohhhh";
  const char *format_str = "%1s%1s%1s%1s";

  int res1 = s21_sscanf(str, format_str, s1, s2, s3, s4);
  int res2 = sscanf(str, format_str, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(opt_s_6) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};
  char s8[BUFF_SIZE] = {'\0'};

  const char *str = "test\tyesss\tanother\ttessst";
  const char *format_str = "%3s%3s%3s%3s";

  int res1 = s21_sscanf(str, format_str, s1, s2, s3, s4);
  int res2 = sscanf(str, format_str, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(opt_s_7) {
  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};

  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};
  char s7[BUFF_SIZE] = {'\0'};
  char s8[BUFF_SIZE] = {'\0'};

  const char *str = "test\tyesss\tanother\ttessst";
  const char *format_str = "%150s%1s%1s\t%3s";

  int res1 = s21_sscanf(str, format_str, s1, s2, s3, s4);
  int res2 = sscanf(str, format_str, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(opt_s_9) {
  int d1 = 0, d2 = 0, b1 = 0, b2 = 0, a1 = 0, a2 = 0;
  long long v1, v2;

  const char *str = "1 1 1 1 1 -1";
  const char *format_str = "%1s %5d %1s %1s %d %lld %d";

  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};
  char s3[BUFF_SIZE] = {'\0'};
  char s4[BUFF_SIZE] = {'\0'};
  char s5[BUFF_SIZE] = {'\0'};
  char s6[BUFF_SIZE] = {'\0'};

  int res1 = s21_sscanf(str, format_str, s1, &a1, s2, s3, &b1, &v1, &d1);
  int res2 = sscanf(str, format_str, s4, &a2, s5, s6, &b2, &v2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(s1, s2);
  ck_assert_str_eq(s3, s4);
  ck_assert_str_eq(s5, s6);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_x_1) {
  unsigned int a = 0, b = 0;

  const char *str = "0x1234567890";
  const char *format_str = "%x";

  int res1 = s21_sscanf(str, format_str, &a);
  int res2 = sscanf(str, format_str, &b);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(opt_x_2) {
  unsigned int a = 0, b = 0;

  const char *str = "0X1234567890";
  const char *format_str = "%x";

  int res1 = s21_sscanf(str, format_str, &a);
  int res2 = sscanf(str, format_str, &b);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(opt_X_1) {
  unsigned int a = 0, b = 0;

  const char *str = "0x1abcdef";
  const char *format_str = "%X";

  int res1 = s21_sscanf(str, format_str, &a);
  int res2 = sscanf(str, format_str, &b);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(opt_X_2) {
  unsigned int a = 0, b = 0;

  const char *str = "0X1ACDEF";
  const char *format_str = "%X";

  int res1 = s21_sscanf(str, format_str, &a);
  int res2 = sscanf(str, format_str, &b);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(opt_x_3) {
  unsigned int a = 0, b = 0;

  const char *str = "0x1aBcDeF";
  const char *format_str = "%x";

  int res1 = s21_sscanf(str, format_str, &a);
  int res2 = sscanf(str, format_str, &b);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(opt_x_4) {
  unsigned int a = 0, b = 0;

  const char *str = "01aBcDeF";
  const char *format_str = "%x";

  int res1 = s21_sscanf(str, format_str, &a);
  int res2 = sscanf(str, format_str, &b);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(opt_X_3) {
  unsigned int a = 0, b = 0;

  const char *str = "01aBcDeF";
  const char *format_str = "%X";

  int res1 = s21_sscanf(str, format_str, &a);
  int res2 = sscanf(str, format_str, &b);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(opt_x_5) {
  unsigned int a = 0, b = 0;

  const char *str = "x1aBcDeF";
  const char *format_str = "%x";

  int res1 = s21_sscanf(str, format_str, &a);
  int res2 = sscanf(str, format_str, &b);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(opt_X_4) {
  unsigned int a = 0, b = 0;

  const char *str = "X1aBcDeF";
  const char *format_str = "%X";

  int res1 = s21_sscanf(str, format_str, &a);
  int res2 = sscanf(str, format_str, &b);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(opt_x_6) {
  unsigned int a = 0, b = 0;

  const char *str = "-0x1aBcDeF";
  const char *format_str = "%x";

  int res1 = s21_sscanf(str, format_str, &a);
  int res2 = sscanf(str, format_str, &b);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(opt_x_7) {
  unsigned int a = 0, b = 0;

  const char *str = "+0x1aBcDeF";
  const char *format_str = "%x";

  int res1 = s21_sscanf(str, format_str, &a);
  int res2 = sscanf(str, format_str, &b);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(opt_x_8) {
  unsigned int a = 0, b = 0;

  const char *str = "+0x1aBcDeF";
  const char *format_str = "%x";

  int res1 = s21_sscanf(str, format_str, &a);
  int res2 = sscanf(str, format_str, &b);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(opt_o_1) {
  uint32_t a1 = 0, a2 = 0;

  const char *str = "1234";
  const char *format_str = "%o";

  int res1 = s21_sscanf(str, format_str, &a1);
  int res2 = sscanf(str, format_str, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(opt_o_2) {
  uint32_t a1 = 0, a2 = 0;

  const char *str = "0x7777777777766666666666";
  const char *format_str = "%o";

  int res1 = s21_sscanf(str, format_str, &a1);
  int res2 = sscanf(str, format_str, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(opt_o_3) {
  uint32_t a1 = 0, a2 = 0;

  const char *str = "0x";
  const char *format_str = "%o";

  int res1 = s21_sscanf(str, format_str, &a1);
  int res2 = sscanf(str, format_str, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(opt_o_4) {
  uint32_t a1 = 0, a2 = 0;

  const char *str = "0X";
  const char *format_str = "%o";

  int res1 = s21_sscanf(str, format_str, &a1);
  int res2 = sscanf(str, format_str, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(opt_o_empty) {
  uint32_t a1 = 0, a2 = 0;

  const char *str = "";
  const char *format_str = "%o";

  int res1 = s21_sscanf(str, format_str, &a1);
  int res2 = sscanf(str, format_str, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(opt_o_5) {
  uint32_t a1 = 0, a2 = 0;

  const char *str = "q1";
  const char *format_str = "%o";

  int res1 = s21_sscanf(str, format_str, &a1);
  int res2 = sscanf(str, format_str, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(opt_o_6) {
  uint32_t a1 = 0, a2 = 0;

  const char *str = "          \n             \n     5";
  const char *format_str = "%o";

  int res1 = s21_sscanf(str, format_str, &a1);
  int res2 = sscanf(str, format_str, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(opt_o_7) {
  unsigned short int a1 = 0, a2 = 0;

  const char *str = "67778";
  const char *format_str = "%ho";

  int res1 = s21_sscanf(str, format_str, &a1);
  int res2 = sscanf(str, format_str, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(opt_o_8) {
  unsigned long int a1 = 0, a2 = 0;

  const char *str = "12345";
  const char *format_str = "%lo";

  int res1 = s21_sscanf(str, format_str, &a1);
  int res2 = sscanf(str, format_str, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(opt_o_9) {
  unsigned long long int a1 = 0, a2 = 0;

  const char *str = "12356226137";
  const char *format_str = "%llo";

  int res1 = s21_sscanf(str, format_str, &a1);
  int res2 = sscanf(str, format_str, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(opt_o_10) {
  uint32_t a1 = 0, a2 = 0;

  const char *str = "0x12320x213x123213";
  const char *format_str = "%o";

  int res1 = s21_sscanf(str, format_str, &a1);
  int res2 = sscanf(str, format_str, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(opt_o_with_dyn) {
  const char str[] = "521561612";
  const char format_str[] = "%*o";

  int res1 = s21_sscanf(str, format_str);
  int res2 = sscanf(str, format_str);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(opt_o_11) {
  uint32_t a1 = 0, a2 = 0;

  const char *str = "qwerty";
  const char *format_str = "%o";

  int res1 = s21_sscanf(str, format_str, &a1);
  int res2 = sscanf(str, format_str, &a2);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(opt_o_12) {
  uint32_t a1 = 0, a2 = 0;

  const char *str = "01234567";
  const char *format_str = "%o";

  int res1 = s21_sscanf(str, format_str, &a1);
  int res2 = sscanf(str, format_str, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(opt_o_with_sign) {
  uint32_t a1 = 0, a2 = 0;

  const char *str = "-66";
  const char *format_str = "%o";

  int res1 = s21_sscanf(str, format_str, &a1);
  int res2 = sscanf(str, format_str, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(opt_o_with_static) {
  unsigned int a1 = 0, a2 = 0;

  const char *str = "123531";
  const char *format_str = "%2o";

  int res1 = s21_sscanf(str, format_str, &a1);
  int res2 = sscanf(str, format_str, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(opt_p_1) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;

  const char *str = "0xFFFF 0xAAAA 0x7123 0xBBC1FF";
  const char *format_str = "%p %p %p %p";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(opt_p_2) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;

  const char *str = "0xFFFF 0xAAAA 0x7123 0xBBC1FF";
  const char *format_str = "%p %p %p %p";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(opt_p_3) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;

  const char *str = "0xFFFF 0xAAAA 0x7123 0xBBC1FF";
  const char *format_str = "%p %p %p %p";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(opt_p_4) {
  int *a1 = 0, *a2 = 0, *b1 = 0, *b2 = 0, *c1 = 0, *c2 = 0, *d1 = 0, *d2 = 0;
  const char *str = "0xFFFF 0xAAAA 0x7123 0xBBC1FF";
  const char *format_str = "%p %p %p %p";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(a1, a2);
  ck_assert_ptr_eq(b1, b2);
  ck_assert_ptr_eq(c1, c2);
  ck_assert_ptr_eq(d1, d2);
}
END_TEST

START_TEST(opt_percent_1) {
  int a1, a2;
  int b1 = 80, b2 = 33;
  int c1 = 55, c2 = 33;

  const char *str = "12 % 13 % 14";
  const char *format_str = "%d %% %d %% %d";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(opt_percent_2) {
  int a1, a2;
  int b1 = 80, b2 = 33;
  int c1 = 55, c2 = 33;

  const char *str = "12%13%14";
  const char *format_str = "%d%%%d%%%d";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(opt_percent_3) {
  int a1 = 1234, a2 = 33333;

  const char *str = "%%%16";
  const char *format_str = "%%%%%%%d";

  int res1 = s21_sscanf(str, format_str, &a1);
  int res2 = sscanf(str, format_str, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(opt_percent_4) {
  const char str[] = "%%%";
  const char format_str[] = "%%%%%%";

  int res1 = s21_sscanf(str, format_str);
  int res2 = sscanf(str, format_str);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(opt_unsigned_1) {
  unsigned short a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char *str = "-245 +67 --50408 350";
  const char *format_str = "%hu %hu %hu %hu";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_uint_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
}
END_TEST

START_TEST(opt_unsigned_2) {
  unsigned long long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0,
                         d2 = 0;

  const char *str = "      -23456 2999933331 5118 3000";
  const char *format_str = "%1llu %2llu %5llu %4llu";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_unsigned_3) {
  unsigned long long int a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  long long d1 = 0, d2 = 0;
  long double v1, v2;

  const char *str =
      "\t\t\t\t\t\n 3      adsfdfa%$$$$`zxgytjjjjk -890 "
      "aurofon+ 21 -5608 -38800 0.32633";
  const char *format_str = "%*s %*s %llu %s %llu %llu %lld %Lf";

  char s1[BUFF_SIZE] = {'\0'};
  char s2[BUFF_SIZE] = {'\0'};

  int res1 = s21_sscanf(str, format_str, &a1, s1, &b1, &c1, &d1, &v1);
  int res2 = sscanf(str, format_str, &a2, s2, &b2, &c2, &d2, &v2);

  ck_assert_uint_eq(res1, res2);
  ck_assert_str_eq(s1, s2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_ldouble_eq_tol(v1, v2, 0.0001);
}
END_TEST

START_TEST(opt_unsigned_4) {
  unsigned short a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *str = "-5428 +71 --5998 3000";
  const char *format_str = "%hu %hu %hu %hu";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(opt_unsigned_5) {
  unsigned short a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;
  const char *str = "-5668 +91 --1008 4400";
  const char *format_str = "%hu %hu %hu %hu";

  int res1 = s21_sscanf(str, format_str, &a1, &b1, &c1, &d1);
  int res2 = sscanf(str, format_str, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

Suite *s21_sscanf_cases(void) {
  Suite *suite = suite_create("s21_sscanf_cases");
  TCase *tc = tcase_create("sscanf_tc");

  tcase_add_test(tc, null_both);
  tcase_add_test(tc, no_valid_str);
  tcase_add_test(tc, without_format_str);
  tcase_add_test(tc, empty_str);
  tcase_add_test(tc, w_space_str_1);
  tcase_add_test(tc, w_space_str_2);

  // d
  tcase_add_test(tc, opt_d_1_int);
  tcase_add_test(tc, opt_d_int_1);
  tcase_add_test(tc, opt_d_int_2);
  tcase_add_test(tc, opt_d_int_3);
  tcase_add_test(tc, opt_d_int_p);
  tcase_add_test(tc, opt_d_int_stat_width_1);
  tcase_add_test(tc, opt_d_int_stat_width_2);
  tcase_add_test(tc, opt_d_int_stat_width_3);
  tcase_add_test(tc, opt_d_int_stat_width_4);
  tcase_add_test(tc, opt_d_int_dyn_width_1);
  tcase_add_test(tc, opt_d_int_dyn_width_2);
  tcase_add_test(tc, opt_d_int_dyn_width_3);
  tcase_add_test(tc, opt_d_int_dyn_width_4);
  tcase_add_test(tc, opt_d_int_sign_1);
  tcase_add_test(tc, opt_d_int_sign_2);
  tcase_add_test(tc, opt_d_int_sign_3);
  tcase_add_test(tc, opt_d_int_sign_4);
  tcase_add_test(tc, opt_d_1_short);
  tcase_add_test(tc, opt_d_1_long);
  tcase_add_test(tc, opt_d_1_longlong);
  tcase_add_test(tc, opt_d_1_overflow);
  tcase_add_test(tc, opt_d_1_other);

  // c
  tcase_add_test(tc, char_1);
  tcase_add_test(tc, char_2);
  tcase_add_test(tc, char_3);
  tcase_add_test(tc, char_ast);

  // i
  tcase_add_test(tc, opt_i_int_1);
  tcase_add_test(tc, opt_i_int_2);
  tcase_add_test(tc, opt_i_int_3);
  tcase_add_test(tc, opt_i_int_4);
  tcase_add_test(tc, opt_i_uint_no_prefix);
  tcase_add_test(tc, opt_i_uint_oct_prefix);
  tcase_add_test(tc, opt_i_uint_hex_prefix);
  tcase_add_test(tc, opt_i_uint_negative);
  tcase_add_test(tc, opt_i_uint_negative_hex_prefix);
  tcase_add_test(tc, opt_i_uint_negative_oct_prefix);
  tcase_add_test(tc, opt_i_uint_negative_hex_without_prefix);
  tcase_add_test(tc, opt_i_uint_positive_hex_with_plus_prefix);
  tcase_add_test(tc, opt_i_hex_1);
  tcase_add_test(tc, opt_i_hex_2);
  tcase_add_test(tc, opt_i_oct_1);
  tcase_add_test(tc, opt_i_oct_2);

  // n
  tcase_add_test(tc, opt_n_1);
  tcase_add_test(tc, opt_n_2);
  tcase_add_test(tc, opt_n_3);
  tcase_add_test(tc, opt_n_4);
  tcase_add_test(tc, opt_n_5);
  tcase_add_test(tc, opt_n_6);

  // f g G
  tcase_add_test(tc, opt_f_1);
  tcase_add_test(tc, opt_f_2);
  tcase_add_test(tc, opt_f_3);
  tcase_add_test(tc, opt_f_4);
  tcase_add_test(tc, opt_f_5);
  tcase_add_test(tc, opt_f_6);
  tcase_add_test(tc, opt_f_7);
  tcase_add_test(tc, opt_f_8);
  tcase_add_test(tc, opt_f_9);
  tcase_add_test(tc, opt_f_10);
  tcase_add_test(tc, opt_f_e);
  tcase_add_test(tc, opt_f_E);
  tcase_add_test(tc, opt_f_neg_width);
  tcase_add_test(tc, opt_f_with_width_1);
  tcase_add_test(tc, opt_f_with_width_2);
  tcase_add_test(tc, opt_Lf);
  tcase_add_test(tc, opt_Le);
  tcase_add_test(tc, opt_LE);
  tcase_add_test(tc, opt_Lg);
  tcase_add_test(tc, opt_LG);

  // s
  tcase_add_test(tc, opt_s_1);
  tcase_add_test(tc, opt_s_2);
  tcase_add_test(tc, opt_s_4);
  tcase_add_test(tc, opt_s_5);
  tcase_add_test(tc, opt_s_6);
  tcase_add_test(tc, opt_s_7);
  tcase_add_test(tc, opt_s_9);

  // x X
  tcase_add_test(tc, opt_x_1);
  tcase_add_test(tc, opt_x_2);
  tcase_add_test(tc, opt_x_3);
  tcase_add_test(tc, opt_x_4);
  tcase_add_test(tc, opt_x_5);
  tcase_add_test(tc, opt_x_6);
  tcase_add_test(tc, opt_x_7);
  tcase_add_test(tc, opt_x_8);
  tcase_add_test(tc, opt_X_1);
  tcase_add_test(tc, opt_X_2);
  tcase_add_test(tc, opt_X_3);
  tcase_add_test(tc, opt_X_4);

  // o
  tcase_add_test(tc, opt_o_empty);
  tcase_add_test(tc, opt_o_with_dyn);
  tcase_add_test(tc, opt_o_with_static);
  tcase_add_test(tc, opt_o_with_sign);
  tcase_add_test(tc, opt_o_1);
  tcase_add_test(tc, opt_o_2);
  tcase_add_test(tc, opt_o_3);
  tcase_add_test(tc, opt_o_4);
  tcase_add_test(tc, opt_o_5);
  tcase_add_test(tc, opt_o_6);
  tcase_add_test(tc, opt_o_7);
  tcase_add_test(tc, opt_o_8);
  tcase_add_test(tc, opt_o_9);
  tcase_add_test(tc, opt_o_10);
  tcase_add_test(tc, opt_o_11);
  tcase_add_test(tc, opt_o_12);

  // p
  tcase_add_test(tc, opt_p_1);
  tcase_add_test(tc, opt_p_2);
  tcase_add_test(tc, opt_p_3);
  tcase_add_test(tc, opt_p_4);

  // %
  tcase_add_test(tc, opt_percent_1);
  tcase_add_test(tc, opt_percent_2);
  tcase_add_test(tc, opt_percent_3);
  tcase_add_test(tc, opt_percent_4);

  // uns
  tcase_add_test(tc, opt_unsigned_1);
  tcase_add_test(tc, opt_unsigned_2);
  tcase_add_test(tc, opt_unsigned_3);
  tcase_add_test(tc, opt_unsigned_4);
  tcase_add_test(tc, opt_unsigned_5);

  suite_add_tcase(suite, tc);

  return suite;
}
