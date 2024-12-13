#include <check.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "s21_string.h"

// Тесты для s21_memchr
START_TEST(test_s21_memchr_found) {
    char str[] = "Hello, world!";
    char *result = s21_memchr(str, 'o', 13);
    ck_assert_ptr_eq(result, str + 4); // 'o' на 4-й позиции
}

START_TEST(test_s21_memchr_not_found) {
    char str[] = "Hello, world!";
    char *result = s21_memchr(str, 'z', 13);
    ck_assert_ptr_eq(result, NULL); // 'z' не найден
}

// Тесты для s21_strncat
START_TEST(test_s21_strncat_basic) {
    char dest[20] = "Hello, ";
    char src[] = "world!";
    s21_strncat(dest, src, 3);
    ck_assert_str_eq(dest, "Hello, wor"); // Конкатенация до 3 символов
}

START_TEST(test_s21_strncat_full) {
    char dest[20] = "Hello, ";
    char src[] = "world!";
    s21_strncat(dest, src, 6);
    ck_assert_str_eq(dest, "Hello, world!"); // Полная конкатенация
}

// Тесты для s21_strchr
START_TEST(test_s21_strchr_found) {
    char str[] = "Hello, world!";
    char *result = s21_strchr(str, 'o');
    ck_assert_ptr_eq(result, str + 4); // Первый 'o' на 4-й позиции
}

START_TEST(test_s21_strchr_not_found) {
    char str[] = "Hello, world!";
    char *result = s21_strchr(str, 'z');
    ck_assert_ptr_eq(result, NULL); // 'z' не найден
}

// Тесты для s21_memcmp
START_TEST(test_s21_memcmp_equal) {
    char str1[] = "Hello";
    char str2[] = "Hello";
    int result = s21_memcmp(str1, str2, 5);
    ck_assert_int_eq(result, 0); // Строки одинаковы
}

START_TEST(test_s21_memcmp_not_equal) {
    char str1[] = "Hello";
    char str2[] = "Hella";
    int result = s21_memcmp(str1, str2, 5);
    ck_assert_int_ne(result, 0); // Строки различаются
}

// Тесты для s21_memcpy
START_TEST(test_s21_memcpy) {
    char dest[10];
    dest[0] = '\0';
    dest[1] = '\0';
    dest[2] = '\0';
    dest[3] = '\0';
    dest[4] = '\0';
    dest[5] = '\0';
    dest[6] = '\0';
    dest[7] = '\0';
    dest[8] = '\0';
    dest[9] = '\0';
    char src[] = "Hello";
    s21_memcpy(dest, src, 5);
    ck_assert_str_eq(dest, "Hello"); // Копирование строки
}

// Тесты для s21_strrchr
START_TEST(test_s21_strrchr_found) {
    char str[] = "Hello, world!";
    char *result = s21_strrchr(str, 'o');
    ck_assert_ptr_eq(result, str + 8); // Последний 'o' на 8-й позиции
}

START_TEST(test_s21_strrchr_not_found) {
    char str[] = "Hello, world!";
    char *result = s21_strrchr(str, 'z');
    ck_assert_ptr_eq(result, NULL); // 'z' не найден
}

// Тесты для s21_strstr
START_TEST(test_s21_strstr_found) {
    char haystack[] = "Hello, world!";
    char needle[] = "world";
    char *result = s21_strstr(haystack, needle);
    ck_assert_ptr_eq(result, haystack + 7); // "world" начинается с 7-й позиции
}

START_TEST(test_s21_strstr_not_found) {
    char haystack[] = "Hello, world!";
    char needle[] = "earth";
    char *result = s21_strstr(haystack, needle);
    ck_assert_ptr_eq(result, NULL); // "earth" не найдено
}

// Тесты для s21_strtok
START_TEST(test_s21_strtok) {
    char str[] = "Hello, world, this, is, a, test";
    char *token = s21_strtok(str, ", ");
    ck_assert_str_eq(token, "Hello");
    token = s21_strtok(NULL, ", ");
    ck_assert_str_eq(token, "world");
    token = s21_strtok(NULL, ", ");
    ck_assert_str_eq(token, "this");
    token = s21_strtok(NULL, ", ");
    ck_assert_str_eq(token, "is");
    token = s21_strtok(NULL, ", ");
    ck_assert_str_eq(token, "a");
    token = s21_strtok(NULL, ", ");
    ck_assert_str_eq(token, "test");
}

// Главная функция для выполнения всех тестов
Suite *memchr_suite(void) {
    Suite *suite = suite_create("s21_memchr");
    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_s21_memchr_found);
    tcase_add_test(tc_core, test_s21_memchr_not_found);
    suite_add_tcase(suite, tc_core);
    return suite;
}

Suite *strncat_suite(void) {
    Suite *suite = suite_create("s21_strncat");
    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_s21_strncat_basic);
    tcase_add_test(tc_core, test_s21_strncat_full);
    suite_add_tcase(suite, tc_core);
    return suite;
}

Suite *strchr_suite(void) {
    Suite *suite = suite_create("s21_strchr");
    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_s21_strchr_found);
    tcase_add_test(tc_core, test_s21_strchr_not_found);
    suite_add_tcase(suite, tc_core);
    return suite;
}

Suite *memcmp_suite(void) {
    Suite *suite = suite_create("s21_memcmp");
    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_s21_memcmp_equal);
    tcase_add_test(tc_core, test_s21_memcmp_not_equal);
    suite_add_tcase(suite, tc_core);
    return suite;
}

Suite *memcpy_suite(void) {
    Suite *suite = suite_create("s21_memcpy");
    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_s21_memcpy);
    suite_add_tcase(suite, tc_core);
    return suite;
}

Suite *strrchr_suite(void) {
    Suite *suite = suite_create("s21_strrchr");
    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_s21_strrchr_found);
    tcase_add_test(tc_core, test_s21_strrchr_not_found);
    suite_add_tcase(suite, tc_core);
    return suite;
}

Suite *strstr_suite(void) {
    Suite *suite = suite_create("s21_strstr");
    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_s21_strstr_found);
    tcase_add_test(tc_core, test_s21_strstr_not_found);
    suite_add_tcase(suite, tc_core);
    return suite;
}

Suite *strtok_suite(void) {
    Suite *suite = suite_create("s21_strtok");
    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_s21_strtok);
    suite_add_tcase(suite, tc_core);
    return suite;
}

int main(void) {
    char buff[1024];
    char *format = "%34.32u|%-.9lf|%36.34ld";
    int len = s21_sprintf(buff, format, -42, 400.3, 10000000000000);
    printf("|%s, %d|\n", buff, len);
    len = sprintf(buff, format, -42, 400.3, 10000000000000);
    printf("|%s, %d|\n", buff, len);
    /*
    int number_failed;
    Suite *s1 = memchr_suite();
    Suite *s2 = strncat_suite();
    Suite *s3 = strchr_suite();
    Suite *s4 = memcmp_suite();
    Suite *s5 = memcpy_suite();
    Suite *s6 = strrchr_suite();
    Suite *s7 = strstr_suite();
    Suite *s8 = strtok_suite();
    
    SRunner *sr = srunner_create(s1);
    srunner_add_suite(sr, s2);
    srunner_add_suite(sr, s3);
    srunner_add_suite(sr, s4);
    srunner_add_suite(sr, s5);
    srunner_add_suite(sr, s6);
    srunner_add_suite(sr, s7);
    srunner_add_suite(sr, s8);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? 0 : 1;
    */
   return 0;
}