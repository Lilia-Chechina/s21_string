#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include <string.h>
#include <stdarg.h>
#include "s21_string.h"

// Тесты

START_TEST(test_integer_format) {
    char buffer[50];
    int result = s21_sprintf(buffer, "%d", 12345);
    ck_assert_int_eq(result, 5);  // Проверка длины строки
    ck_assert_str_eq(buffer, "12345");
}
END_TEST

START_TEST(test_float_format) {
    char buffer[50];
    int result = s21_sprintf(buffer, "%.2f", 123.456);
    ck_assert_int_eq(result, 6);  // Проверка длины строки
    ck_assert_str_eq(buffer, "123.46");
}
END_TEST

START_TEST(test_string_format) {
    char buffer[50];
    int result = s21_sprintf(buffer, "%s", "Hello");
    ck_assert_int_eq(result, 5);  // Проверка длины строки
    ck_assert_str_eq(buffer, "Hello");
}
END_TEST

START_TEST(test_char_format) {
    char buffer[50];
    int result = s21_sprintf(buffer, "%c", 'A');
    ck_assert_int_eq(result, 1);  // Проверка длины строки
    ck_assert_str_eq(buffer, "A");
}
END_TEST

START_TEST(test_multiple_arguments) {
    char buffer[50];
    int result = s21_sprintf(buffer, "%d %s", 12345, "Hello");
    ck_assert_int_eq(result, 11);  // Проверка длины строки
    ck_assert_str_eq(buffer, "12345 Hello");
}
END_TEST

START_TEST(test_width_modifier) {
    char buffer[50];
    int result = s21_sprintf(buffer, "%10d", 42);
    ck_assert_int_eq(result, 10);  // Проверка длины строки
    ck_assert_str_eq(buffer, "        42");
}
END_TEST

START_TEST(test_precision_modifier) {
    char buffer[50];
    int result = s21_sprintf(buffer, "%.3f", 123.456);
    ck_assert_int_eq(result, 7);  // Проверка длины строки
    ck_assert_str_eq(buffer, "123.456");
}
END_TEST

START_TEST(test_left_justified) {
    char buffer[50];
    int result = s21_sprintf(buffer, "%-10d", 42);
    ck_assert_int_eq(result, 10);  // Проверка длины строки
    ck_assert_str_eq(buffer, "42        ");
}
END_TEST

START_TEST(test_empty_format_string) {
    char buffer[50];
    int result = s21_sprintf(buffer, "");
    ck_assert_int_eq(result, 0);  // Проверка длины строки
    ck_assert_str_eq(buffer, "");
}
END_TEST

// Список всех тестов
Suite *sprintf_suite(void) {
    
    Suite *s;
    TCase *tc_core;

    s = suite_create("s21_sprintf");

    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_integer_format);
    tcase_add_test(tc_core, test_float_format);
    tcase_add_test(tc_core, test_string_format);
    tcase_add_test(tc_core, test_char_format);
    tcase_add_test(tc_core, test_multiple_arguments);
    tcase_add_test(tc_core, test_width_modifier);
    tcase_add_test(tc_core, test_precision_modifier);
    tcase_add_test(tc_core, test_left_justified);
    tcase_add_test(tc_core, test_empty_format_string);
    suite_add_tcase(s, tc_core);

    return s;
}

// Запуск тестов
int main(void) {
    
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = sprintf_suite();
    sr = srunner_create(s);

    srunner_set_xml(sr, "check_report.xml");  // Указываем имя для HTML-отчета

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    if (number_failed == 0) {
        printf("All tests passed!\n");
    } else {
        printf("%d test(s) failed\n", number_failed);
    }

    return number_failed == 0 ? 0 : 1;
    
    
    //return 0;
}