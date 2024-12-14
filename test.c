#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <check.h>
#include <float.h>
#include "s21_string.h"

// Пример теста для s21_memchr
START_TEST(test_s21_memchr_edge) {
    char str[] = "Hello, World!";
    ck_assert_ptr_eq(s21_memchr(str, 'H', 0), NULL); // n == 0, ничего не найдено
    ck_assert_ptr_eq(s21_memchr(str, 'H', 5), str); // 'H' найден в начале
    ck_assert_ptr_eq(s21_memchr(str, 'z', 13), NULL); // 'z' не найдено
    ck_assert_ptr_eq(s21_memchr(str, 'o', 7), str + 4); // 'o' найдено на позиции 4
}
END_TEST

// Пример теста для s21_memcmp
START_TEST(test_s21_memcmp_edge) {
    char str1[] = "Hello";
    char str2[] = "Hello";
    char str3[] = "Hellx";
    ck_assert_int_eq(s21_memcmp(str1, str2, 5), 0); // одинаковые строки
    ck_assert_int_lt(s21_memcmp(str1, str3, 5), 0); // str1 < str3
    ck_assert_int_eq(s21_memcmp(str1, str3, 4), 0); // одинаковые строки
}
END_TEST

// Пример теста для s21_memcpy
START_TEST(test_s21_memcpy_edge) {
    char src[] = "Hello, World!";
    char dest[50];
    ck_assert_ptr_eq(s21_memcpy(dest, src, 0), dest); // n == 0, ничего не копируем
    ck_assert_str_eq(s21_memcpy(dest, src, 5), "Hello"); // копируем 5 символов
    ck_assert_str_eq(s21_memcpy(dest, src, 13), "Hello, World!"); // копируем всю строку
}
END_TEST

// Пример теста для s21_memset
START_TEST(test_s21_memset_edge) {
    char str[50] = "Hello, World!";
    ck_assert_ptr_eq(s21_memset(str, 'a', 0), str); // n == 0, ничего не меняем
    ck_assert_str_eq(s21_memset(str, 'x', 5), "xxxxx, World!"); // первые 5 символов заменены на 'x'
    ck_assert_str_eq(s21_memset(str, 'z', 13), "zzzzzzzzzzzzz"); // все 13 символов заменены на 'z'
}
END_TEST

// Пример теста для s21_strncat
START_TEST(test_s21_strncat_edge) {
    char dest[50] = "Hello";
    char src[] = " World!";
    ck_assert_str_eq(s21_strncat(dest, src, 0), "Hello"); // ничего не добавляем
    ck_assert_str_eq(s21_strncat(dest, src, 5), "Hello Worl"); // добавляем только 5 символов
}
END_TEST

// Пример теста для s21_strchr
START_TEST(test_s21_strchr_edge) {
    char str[] = "Hello, World!";
    ck_assert_ptr_eq(s21_strchr(str, 'H'), str); // символ 'H' в начале
    ck_assert_ptr_eq(s21_strchr(str, 'o'), str + 4); // символ 'o' на позиции 4
    ck_assert_ptr_eq(s21_strchr(str, 'z'), NULL); // символ 'z' не найден
}
END_TEST

// Пример теста для s21_strncmp
START_TEST(test_s21_strncmp_edge) {
    char str1[] = "Hello";
    char str2[] = "Hello";
    char str3[] = "Hellx";
    ck_assert_int_eq(s21_strncmp(str1, str2, 5), 0); // одинаковые строки
    ck_assert_int_lt(s21_strncmp(str1, str3, 5), 0); // str1 < str3
    ck_assert_int_eq(s21_strncmp(str1, str3, 4), 0); // одинаковые строки
}
END_TEST

// Пример теста для s21_strncpy
START_TEST(test_s21_strncpy_edge) {
    char src[] = "Hello, World!";
    char dest[20];
    ck_assert_str_eq(s21_strncpy(dest, src, 0), ""); // n == 0, строка пуста
    ck_assert_str_eq(s21_strncpy(dest, src, 5), "Hello"); // копируем первые 5 символов
    ck_assert_str_eq(s21_strncpy(dest, src, 20), "Hello, World!"); // копируем всю строку
}
END_TEST

// Пример теста для s21_strcspn
START_TEST(test_s21_strcspn_edge) {
    char str1[] = "Hello, World!";
    char str2[] = " ,!";
    ck_assert_int_eq(s21_strcspn(str1, str2), 5); // прекращается на первой пробеле
}
END_TEST

// Пример теста для s21_strerror
START_TEST(test_s21_strerror_edge) {
    ck_assert_str_eq(s21_strerror(0), "Success");
    ck_assert_str_eq(s21_strerror(1), "Operation not permitted");
}
END_TEST

// Пример теста для s21_strlen
START_TEST(test_s21_strlen_edge) {
    char str[] = "Hello, World!";
    ck_assert_int_eq(s21_strlen(str), 13); // длина строки
    ck_assert_int_eq(s21_strlen(""), 0); // пустая строка
}
END_TEST

// Пример теста для s21_strpbrk
START_TEST(test_s21_strpbrk_edge) {
    char str1[] = "Hello, World!";
    char str2[] = " ,!";
    ck_assert_ptr_eq(s21_strpbrk(str1, str2), "str1 + 5"); // находим первый пробел
}
END_TEST

// Пример теста для s21_strrchr
START_TEST(test_s21_strrchr_edge) {
    char str[] = "Hello, World!";
    ck_assert_ptr_eq(s21_strrchr(str, 'o'), str + 8); // последний символ 'o' на позиции 8
    ck_assert_ptr_eq(s21_strrchr(str, 'z'), NULL); // 'z' не найдено
}
END_TEST

// Пример теста для s21_strstr
START_TEST(test_s21_strstr_edge) {
    char haystack[] = "Hello, World!";
    char needle[] = "World";
    ck_assert_ptr_eq(s21_strstr(haystack, needle), haystack + 7); // строка найдена
    ck_assert_ptr_eq(s21_strstr(haystack, "z"), NULL); // ничего не найдено
}
END_TEST

// Пример теста для s21_strtok
START_TEST(test_s21_strtok_edge) {
    char str[] = "Hello, World! How are you?";
    char *token;
    char *delim = " ,!?";
    token = s21_strtok(str, delim);
    ck_assert_str_eq(token, "Hello"); // первый токен
    token = s21_strtok(NULL, delim);
    ck_assert_str_eq(token, "World"); // второй токен
}
END_TEST

// Пример теста для s21_sprintf
START_TEST(test_s21_sprintf_edge) {
    char buffer[100];
    ck_assert_int_eq(s21_sprintf(buffer, "%d", 42), 2); // %d
    ck_assert_str_eq(buffer, "42");

    ck_assert_int_eq(s21_sprintf(buffer, "%s", "Hello, World!"), 13); // %s
    ck_assert_str_eq(buffer, "Hello, World!");

    ck_assert_int_eq(s21_sprintf(buffer, "%f", 3.14159), 8); // %f
    ck_assert_str_eq(buffer, "3.141590");
}
END_TEST

// Функция для создания тестов
Suite *create_test_suite() {
    Suite *s = suite_create("s21_string_functions");

    TCase *tc_edge = tcase_create("Edge Cases");
    tcase_add_test(tc_edge, test_s21_memchr_edge);
    tcase_add_test(tc_edge, test_s21_memcmp_edge);
    tcase_add_test(tc_edge, test_s21_memcpy_edge);
    tcase_add_test(tc_edge, test_s21_memset_edge);
    tcase_add_test(tc_edge, test_s21_strncpy_edge);
    tcase_add_test(tc_edge, test_s21_strchr_edge);
    tcase_add_test(tc_edge, test_s21_strncmp_edge);
    tcase_add_test(tc_edge, test_s21_strncat_edge);
    tcase_add_test(tc_edge, test_s21_strcspn_edge);
    tcase_add_test(tc_edge, test_s21_strerror_edge);
    tcase_add_test(tc_edge, test_s21_strlen_edge);
    tcase_add_test(tc_edge, test_s21_strpbrk_edge);
    tcase_add_test(tc_edge, test_s21_strrchr_edge);
    tcase_add_test(tc_edge, test_s21_strstr_edge);
    tcase_add_test(tc_edge, test_s21_strtok_edge);
    tcase_add_test(tc_edge, test_s21_sprintf_edge);

    suite_add_tcase(s, tc_edge);

    return s;
}

// Функция для запуска тестов
int main() {
    Suite *s = create_test_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    srunner_set_log(sr, "test_report.log");  // Логирование отчёта в файл
    srunner_free(sr);

    return 0;
}
