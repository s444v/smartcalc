#include "tests.h"

START_TEST(smart_calculation) {
  numbers *num1 = init_double_stack();
  numbers *num2 = init_double_stack();
  char *first = toPostFix(
      "2.1+2.1-2.1*3-(3*4+5)%4-sin(2)-cos(1)/"
      "sqrt(4)-ln(2)^lg(3)+atan(1)+asin(1)+acos(1)+tan(1)");
  char *second = toPostFix("-(-1)");
  ck_assert_double_eq_tol(
      calculations(first, num1),
      (2.1 + 2.1 - 2.1 * 3 - fmod((3 * 4 + 5), 4) - sin(2) - cos(1) / sqrt(4) -
       pow(log(2), log10(3)) + atan(1) + asin(1) + acos(1) + tan(1)),
      0.0000001);
  ck_assert_double_eq_tol(calculations(second, num2), (-(-1)), 0.0000001);
  remove_double_stack(num2);
  remove_double_stack(num1);
  free(num1);
  free(num2);
  free(second);
  free(first);
}
END_TEST

START_TEST(smart_calculation_with_x) {
  numbers *num = init_double_stack();
  char *first = toPostFix("-(-x)");
  char *second = toPostFix(
      "2.1*x+2.1-2.1*3-(3*4+5)%4-sin(2)-cos(1)/"
      "sqrt(4)-ln(2)^lg(3)+atan(1)+asin(1)+acos(1)+tan(1)");
  ck_assert_double_eq_tol(calculationsWithX(second, num, 3.01),
                          (2.1 * 3.01 + 2.1 - 2.1 * 3 - fmod((3 * 4 + 5), 4) -
                           sin(2) - cos(1) / sqrt(4) - pow(log(2), log10(3)) +
                           atan(1) + asin(1) + acos(1) + tan(1)),
                          0.0000001);
  ck_assert_double_eq_tol(calculationsWithX(first, num, 1), (-(-1)), 0.0000001);
  remove_double_stack(num);
  free(num);
  free(second);
  free(first);
}
END_TEST

START_TEST(smart_calculation_main) {
  int flag = 0;
  int flag_error = 0;
  ck_assert_double_eq_tol(
      outputResult("2.1*x+2.1-2.1*3-(3*4+5)%4-sin(2)-cos(1)/"
                   "sqrt(4)-ln(2)^lg(3)+atan(1)+asin(1)+acos(1)+tan(1)",
                   0, &flag),
      (2.1 * 0 + 2.1 - 2.1 * 3 - fmod((3 * 4 + 5), 4) - sin(2) -
       cos(1) / sqrt(4) - pow(log(2), log10(3)) + atan(1) + asin(1) + acos(1) +
       tan(1)),
      0.0000001);
  ck_assert_double_eq_tol(
      graphResult("2.1*x+2.1-2.1*3-(3*4+5)%4-sin(2)-cos(1)/"
                  "sqrt(4)-ln(2)^lg(3)+atan(1)+asin(1)+acos(1)+tan(1)",
                  0, &flag),
      (2.1 * 0 + 2.1 - 2.1 * 3 - fmod((3 * 4 + 5), 4) - sin(2) -
       cos(1) / sqrt(4) - pow(log(2), log10(3)) + atan(1) + asin(1) + acos(1) +
       tan(1)),
      0.0000001);
  ck_assert_double_eq_tol(
      outputResult("2.1*3.0001+2.1-2.1*3-(3*4+5)%4-sin(2)-cos(1)/"
                   "sqrt(4)-ln(2)^lg(3)+atan(1)+asin(1)+acos(1)+tan(1)",
                   0, &flag),
      (2.1 * 3.0001 + 2.1 - 2.1 * 3 - fmod((3 * 4 + 5), 4) - sin(2) -
       cos(1) / sqrt(4) - pow(log(2), log10(3)) + atan(1) + asin(1) + acos(1) +
       tan(1)),
      0.0000001);
  ck_assert_double_eq_tol(
      outputResult("2.1*2.1*-2.1*3-(3*4+5)%4-sin(2)-cos(1)/"
                   "sqrt(4)-ln(2)^lg(3)+atan(1)+asin(1)+acos(1)+tan(1)",
                   0, &flag),
      (2.1 * 2.1 * -2.1 * 3 - fmod((3 * 4 + 5), 4) - sin(2) - cos(1) / sqrt(4) -
       pow(log(2), log10(3)) + atan(1) + asin(1) + acos(1) + tan(1)),
      0.0000001);
  outputResult(
      "2.1*2.1*-2.1*3-(3*4+5)%4-sin(2)-cos(1)/"
      "sqrt(4)-ln(2)^lg(3)+atan(1)++asin(1)+acos(1)+tan(1)",
      0, &flag_error);
  graphResult(
      "2.1*2.1*-2.1*3-(3*4+5)%4-sin(2)-cos(1)/"
      "sqrt(4)-ln(2)^lg(3)+atan(1)++asin(1)+acos(1)+tan(1)",
      0, &flag_error);
  ck_assert_int_eq(flag_error, 1);
  ck_assert_int_eq(flag, 0);
}
END_TEST

START_TEST(smart_calculation_validation) {
  ck_assert_int_eq(
      isValidExpression("2.1+2.1-2.1*3-(3*4+5)%4-sin(2)-cos(1)/"
                        "sqrt(4)-ln(2)^lg(3)+atan(1)+asin(1)+acos(1)+tan(1)"),
      1);
  ck_assert_int_eq(
      isValidExpression("2.1+2.1-2.1*3-(3*4+5)%4-sin(2)-cos(1)/"
                        "sqrt(4)-ln(2)^lg(3)+atan(1)+asin(1)+acos(1)+tan(1))"),
      0);
  ck_assert_int_eq(
      isValidExpression("2.1+2.1-2.1*3-(3*4+5)%4-sin(2)-cos(1)/"
                        "sqrt(4)-ln(2)^lg(3)+atan(1)+asin(1)+acos(1)++tan(1)"),
      0);
  ck_assert_int_eq(
      isValidExpression("2.1+2.1-2.1*3-(3*4+5)%4-sn(2)-cos(1)/"
                        "sqrt(4)-ln(2)^lg(3)+atan(1)+asin(1)+acos(1)++tan(1)"),
      0);
}
END_TEST

Suite *test_s21_smartcalc() {
  TCase *tc1_1 = tcase_create("s21_smartcalc");

  tcase_add_test(tc1_1, smart_calculation);  // 1
  tcase_add_test(tc1_1, smart_calculation_with_x);
  tcase_add_test(tc1_1, smart_calculation_validation);
  tcase_add_test(tc1_1, smart_calculation_main);  // 2

  Suite *s1 = suite_create("s21_smartcalc");
  suite_add_tcase(s1, tc1_1);

  return s1;
}

int main(void) {
  int failed_tests = 0;  // счётчик проваленных тестов
  Suite *test_s21_smartcalc_func[] = {test_s21_smartcalc(), NULL};

  for (int i = 0; test_s21_smartcalc_func[i] != NULL; i++) {
    SRunner *srun = srunner_create(test_s21_smartcalc_func[i]);

    srunner_set_fork_status(srun, CK_NOFORK);
    srunner_run_all(srun, CK_NORMAL);

    failed_tests += srunner_ntests_failed(srun);
    srunner_free(srun);
  }
  printf("========= FAILED: %d =========\n", failed_tests);

  return failed_tests == 0 ? 0 : 1;
}