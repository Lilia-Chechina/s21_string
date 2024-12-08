#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"

int total_tests = 0;
int passed_tests = 0;

#define ASSERT_EQ(expected, actual, format, ...) \
    do { \
        total_tests++; \
        if ((expected) == (actual)) { \
            passed_tests++; \
        } else { \
            fprintf(stderr, "Test failed: expected " format " but got " format "\n", __VA_ARGS__, __VA_ARGS__); \
        } \
    } while (0)

#define ASSERT_CMP(expected, actual) \
    do { \
        total_tests++; \
        if (((expected) < 0 && (actual) < 0) || \
            ((expected) == 0 && (actual) == 0) || \
            ((expected) > 0 && (actual) > 0)) { \
            passed_tests++; \
        } else { \
            fprintf(stderr, "Test failed: expected %d but got %d\n", (expected), (actual)); \
        } \
    } while (0)

void test_memchr() {
    printf("Testing memchr()...\n");

    const char *str = "Hello, world!";

    char *result_s21 = (char *)s21_memchr(str, 'l', strlen(str));
    char *result_orig = (char *)memchr(str, 'l', strlen(str));
    ASSERT_EQ(result_orig, result_s21, "%p", result_s21);

    result_s21 = (char *)s21_memchr(str, 'x', strlen(str));
    result_orig = (char *)memchr(str, 'x', strlen(str));
    ASSERT_EQ(result_orig, result_s21, "%p", result_s21);

    result_s21 = (char *)s21_memchr(str, '\0', strlen(str));
    result_orig = (char *)memchr(str, '\0', strlen(str));
    ASSERT_EQ(result_orig, result_s21, "%p", result_s21);

    result_s21 = (char *)s21_memchr(str, 'l', 0);
    result_orig = (char *)memchr(str, 'l', 0);
    ASSERT_EQ(result_orig, result_s21, "%p", result_s21);
}

void test_memcmp() {
    printf("\nTesting memcmp()...\n");

    const char *str1 = "Hello";
    const char *str2 = "Hello";
    const char *str3 = "World";

    int result_s21 = s21_memcmp(str1, str2, 5);
    int result_orig = memcmp(str1, str2, 5);
    ASSERT_CMP(result_orig, result_s21);

    result_s21 = s21_memcmp(str1, str3, 5);
    result_orig = memcmp(str1, str3, 5);
    ASSERT_CMP(result_orig, result_s21);

    result_s21 = s21_memcmp(str1, str1, 0);
    result_orig = memcmp(str1, str1, 0);
    ASSERT_CMP(result_orig, result_s21);

    result_s21 = s21_memcmp(str1, str2, 0);
    result_orig = memcmp(str1, str2, 0);
    ASSERT_CMP(result_orig, result_s21);
}

void test_memcpy() {
    printf("\nTesting memcpy()...\n");

    char dest[20] = {0};
    const char *src = "Copy me!";

    char *result_our = s21_memcpy(dest, src, strlen(src) + 1);
    char *result_orig = memcpy(dest, src, strlen(src) + 1);
    ASSERT_EQ(0, strcmp(dest, "Copy me!"), "%s", "Copy me!");
    ASSERT_EQ(result_orig, result_our, "%p", result_our);

    result_our = s21_memcpy(dest, src, 0);
    result_orig = memcpy(dest, src, 0);
    ASSERT_EQ(0, strcmp(dest, "Copy me!"), "%s", "Copy me!");
    ASSERT_EQ(result_orig, result_our, "%p", result_our);

    result_our = s21_memcpy(NULL, src, 10);
    ASSERT_EQ(NULL, result_our, "%p", result_our);

    result_our = s21_memcpy(dest, NULL, 10);
    ASSERT_EQ(NULL, result_our, "%p", result_our);
}

int main() {
    test_memchr();
    test_memcmp();
    test_memcpy();

    printf("\nTests passed: %d/%d\n", passed_tests, total_tests);
    return 0;
}
