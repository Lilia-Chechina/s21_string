#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h> // УДАЛИТЬ БИБЛИОТЕКА ДЛЯ ТЕСТОВ !!!!

void *s21_memcpy(void *dest, const void *src, size_t n);
char *s21_strchr(const char *str, int c);
size_t s21_strlen(const char *str);
char *to_upper(const char *str);
char *to_lower(const char *str);
void *insert(const char *src, const char *str, size_t start_index);
void *trim(const char *src, const char *trim_chars);

int main() {
    int passed = 0, failed = 0;

    // Test to_upper
    char *test1 = to_upper("hello");
    if (test1 && strcmp(test1, "HELLO") == 0) passed++; else failed++;
    free(test1);

    char *test2 = to_upper("HELLO");
    if (test2 && strcmp(test2, "HELLO") == 0) passed++; else failed++;
    free(test2);

    char *test3 = to_upper("");
    if (test3 && strcmp(test3, "") == 0) passed++; else failed++;
    free(test3);

    char *test4 = to_upper("123abc");
    if (test4 && strcmp(test4, "123ABC") == 0) passed++; else failed++;
    free(test4);

    // Test to_lower
    char *test5 = to_lower("HELLO");
    if (test5 && strcmp(test5, "hello") == 0) passed++; else failed++;
    free(test5);

    char *test6 = to_lower("hello");
    if (test6 && strcmp(test6, "hello") == 0) passed++; else failed++;
    free(test6);

    char *test7 = to_lower("");
    if (test7 && strcmp(test7, "") == 0) passed++; else failed++;
    free(test7);

    char *test8 = to_lower("123ABC");
    if (test8 && strcmp(test8, "123abc") == 0) passed++; else failed++;
    free(test8);

    // Test insert
    char *test9 = insert("hello", "world", 5);
    if (test9 && strcmp(test9, "helloworld") == 0) passed++; else failed++;
    free(test9);

    char *test10 = insert("hello", "world", 0);
    if (test10 && strcmp(test10, "worldhello") == 0) passed++; else failed++;
    free(test10);

    char *test11 = insert("", "world", 0);
    if (test11 && strcmp(test11, "world") == 0) passed++; else failed++;
    free(test11);

    char *test12 = insert("hello", "", 3);
    if (test12 && strcmp(test12, "hello") == 0) passed++; else failed++;
    free(test12);

    // Test trim
    char *test13 = trim("  hello  ", " ");
    if (test13 && strcmp(test13, "hello") == 0) passed++; else failed++;
    free(test13);

    char *test14 = trim("--hello--", "-");
    if (test14 && strcmp(test14, "hello") == 0) passed++; else failed++;
    free(test14);

    char *test15 = trim("hello", " ");
    if (test15 && strcmp(test15, "hello") == 0) passed++; else failed++;
    free(test15);

    char *test16 = trim("", " ");
    if (test16 && strcmp(test16, "") == 0) passed++; else failed++;
    free(test16);

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

char *to_upper(const char *str) {
    char *result = NULL;
    if (str) {
        size_t len = s21_strlen(str);
        result = malloc((len + 1) * sizeof(char));
        if (result) {
            for (size_t i = 0; i < len; i++) {
                if (str[i] >= 'a' && str[i] <= 'z') {
                    result[i] = str[i] - 32;
                } else {
                    result[i] = str[i];
                }
            }
            result[len] = '\0';
        }
    }
    return result;
}

char *to_lower(const char *str) {
    char *result = NULL;
    if (str) {
        size_t len = s21_strlen(str);
        result = malloc((len + 1) * sizeof(char));
        if (result) {
            for (size_t i = 0; i < len; i++) {
                if (str[i] >= 'A' && str[i] <= 'Z') {
                    result[i] = str[i] + 32;
                } else {
                    result[i] = str[i];
                }
            }
            result[len] = '\0';
        }
    }
    return result;
}

void *insert(const char *src, const char *str, size_t start_index) {
    char *result = NULL;
    if (src && str && start_index <= s21_strlen(src)) {
        size_t src_len = s21_strlen(src);
        size_t str_len = s21_strlen(str);
        result = malloc((src_len + str_len + 1) * sizeof(char));
        if (result) {
            s21_memcpy(result, src, start_index);
            s21_memcpy(result + start_index, str, str_len);
            s21_memcpy(result + start_index + str_len, src + start_index, src_len - start_index);
            result[src_len + str_len] = '\0';
        }
    }
    return result;
}

void *trim(const char *src, const char *trim_chars) {
    char *result = NULL;
    if (src && trim_chars) {
        size_t start = 0, end = s21_strlen(src);

        while (start < end && s21_strchr(trim_chars, src[start])) {
            start++;
        }

        while (end > start && s21_strchr(trim_chars, src[end - 1])) {
            end--;
        }

        size_t len = end - start;
        result = malloc((len + 1) * sizeof(char));
        if (result) {
            s21_memcpy(result, src + start, len);
            result[len] = '\0';
        }
    }
    return result;
}


