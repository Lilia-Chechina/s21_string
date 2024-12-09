#include <stddef.h>

void *s21_memchr(const void *str, int c, size_t n) {
  const unsigned char *s = (const unsigned char *)str;
  unsigned char ch = (unsigned char)c;

  for (size_t i = 0; i < n; i++) {
    if (s[i] == ch) {
      return (void *)(s + i);
    }
  }

  return NULL;
}

int s21_memcmp(const void *str1, const void *str2, size_t n) {
  const unsigned char *p1 = (const unsigned char *)str1;
  const unsigned char *p2 = (const unsigned char *)str2;

  for (size_t i = 0; i < n; i++) {
    if (p1[i] < p2[i]) {
      return -1;
    } else if (p1[i] > p2[i]) {
      return 1;
    }
  }

  return 0;
}

void *s21_memcpy(void *dest, const void *src, size_t n) {  // Убрать 2 return
  unsigned char *d = (unsigned char *)dest;
  const unsigned char *s = (const unsigned char *)src;

  for (size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }

  return dest;
}
