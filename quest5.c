#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> // УДАЛИТЬ БИБЛИОТЕКА ДЛЯ ТЕСТОВ !!!!

#define MAX_LEN 1024

void *s21_memcpy(void *dest, const void *src, size_t n);
char *s21_strchr(const char *str, int c);
size_t s21_strlen(const char *str);
void *to_upper(const char *str);
char *to_lower(const char *str);
void *insert(const char *src, const char *str, size_t start_index);
void *trim(const char *src, const char *trim_chars);

int main() {
    int passed = 0, failed = 0;

    // Test to_upper
    void *test1 = to_upper("hello");
    if (test1 && strcmp(test1, "HELLO") == 0) passed++; else failed++;

    void *test2 = to_upper("HELLO");
    if (test2 && strcmp(test2, "HELLO") == 0) passed++; else failed++;

    void *test3 = to_upper("");
    if (test3 && strcmp(test3, "") == 0) passed++; else failed++;

    void *test4 = to_upper("123abc");
    if (test4 && strcmp(test4, "123ABC") == 0) passed++; else failed++;

    // Test to_lower
    void *test5 = to_lower("HELLO");
    if (test5 && strcmp(test5, "hello") == 0) passed++; else failed++;

    void *test6 = to_lower("hello");
    if (test6 && strcmp(test6, "hello") == 0) passed++; else failed++;

    void *test7 = to_lower("");
    if (test7 && strcmp(test7, "") == 0) passed++; else failed++;

    void *test8 = to_lower("123ABC");
    if (test8 && strcmp(test8, "123abc") == 0) passed++; else failed++;

    // Test insert
    char *test9 = insert("hello", "world", 5);
    if (test9 && strcmp(test9, "helloworld") == 0) passed++; else failed++;

    char *test10 = insert("hello", "world", 0);
    if (test10 && strcmp(test10, "worldhello") == 0) passed++; else failed++;

    char *test11 = insert("", "world", 0);
    if (test11 && strcmp(test11, "world") == 0) passed++; else failed++;

    char *test12 = insert("hello", "", 3);
    if (test12 && strcmp(test12, "hello") == 0) passed++; else failed++;

    // Test trim
    char *test13 = trim("  hello  ", " ");
    if (test13 && strcmp(test13, "hello") == 0) passed++; else failed++;

    char *test14 = trim("--hello--", "-");
    if (test14 && strcmp(test14, "hello") == 0) passed++; else failed++;

    char *test15 = trim("hello", " ");
    if (test15 && strcmp(test15, "hello") == 0) passed++; else failed++;
    char *test16 = trim("", " ");
    if (test16 && strcmp(test16, "") == 0) passed++; else failed++;

    printf("Tests passed: %d\n", passed);
    printf("Tests failed: %d\n", failed);

    return 0;
}

void *s21_memcpy(void *dest, const void *src, size_t n) { 
  unsigned char *d = (unsigned char *)dest;
  const unsigned char *s = (const unsigned char *)src;

  for (size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }
  d[n] = '\0';

  return dest;
}

char *s21_strchr(const char *str, int c) {
    char *result = NULL; 
    for (int i = 0; str[i] != '\0'; i++) {
        if ((unsigned char)str[i] == (unsigned char)c) {  // случай если символ совпадает с искомым
            result = (char *)&str[i];
            break; 
        }
    }

    if (result == NULL && c == '\0') {  // ищем символ конца строки '\0' и он не был найден ранее
        result = (char *)&str[0];
        while (*result != '\0') { // нашли указатель на конец строки
            result++;
        }
    }
    return result;
}

size_t s21_strlen(const char *str) {
    size_t length = 0;
    if (str != NULL) {
        while (str[length] != '\0') {
            length++;
        }
    }
    return length;
}

void *to_upper(const char *str) {
    static char result[MAX_LEN];
    if (str == NULL) {
        return NULL;
    }
    size_t len = s21_strlen(str);
    for (size_t i = 0; i < len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            result[i] = str[i] - 32;
        } else {
            result[i] = str[i];
        }
    }
    result[len] = '\0';

    return result;
}

char *to_lower(const char *str) {
    static char result[MAX_LEN];
    if (str == NULL) {
        return NULL;
    }
    size_t len = s21_strlen(str);
    for (size_t i = 0; i < len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            result[i] = str[i] + 32;
        } else {
            result[i] = str[i];
        }
    }
    result[len] = '\0';

    return result;
}

void *insert(const char *src, const char *str, size_t start_index) {
    static char result[MAX_LEN] = {0};
    if (src && str && start_index <= s21_strlen(src)) {
        size_t src_len = s21_strlen(src);
        size_t str_len = s21_strlen(str);

        if (src_len + str_len < MAX_LEN) {
            s21_memcpy(result, src, start_index);
            s21_memcpy(result + start_index, str, str_len);
            s21_memcpy(result + start_index + str_len, src + start_index, src_len - start_index);
            result[src_len + str_len] = '\0';
        } else {
            result[0] = '\0';
        }
    } else {
        result[0] = '\0';
    }
    return result;
}

void *trim(const char *src, const char *trim_chars) {
    static char result[MAX_LEN] = {0};
    if (src && trim_chars) {
        size_t start = 0, end = s21_strlen(src);

        while (start < end && s21_strchr(trim_chars, src[start])) {
            start++;
        }

        while (end > start && s21_strchr(trim_chars, src[end - 1])) {
            end--;
        }

        size_t len = end - start;
        if (len < MAX_LEN) {
            s21_memcpy(result, src + start, len);
            result[len] = '\0';
        } else {
            result[0] = '\0';
        }
    } else {
        result[0] = '\0';
    }
    return result;
}


