#include "func_4_6.h"

char *s21_strchr(const char *str, int c) {
  char *result = s21_NULL;
  while (*str != '\0') {
    if (*str == (char)c) {
      result = (char *)str;
      break;
    }
    str++;
  }
  if (c == '\0' && result == s21_NULL) {
    result = (char *)str;
  }
  return result;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t dest_len = 0;
  s21_size_t i;

  while (dest[dest_len] != '\0') {
    dest_len++;
  }

  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[dest_len + i] = src[i];
  }

  dest[dest_len + i] = '\0';

  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    ptr[i] = (unsigned char)c;
  }
  return str;
}