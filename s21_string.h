#include <stddef.h>

//1-3
void *s21_memchr(const void *str, int c, size_t n);

int s21_memcmp(const void *str1, const void *str2, size_t n);

void *s21_memcpy(void *dest, const void *src, size_t n);

//4-6
void *s21_memset(void *str, int c, size_t n);

char *s21_strncat(char *dest, const char *src, size_t n);

char *s21_strchr(const char *str, int c);
//10-12
size_t s21_strlen(const char *str);

char *s21_strpbrk(const char *str1, const char *str2);

char *s21_strerror(int errnum);

//13-15
char *s21_strrchr(const char *str, int c);

char *s21_strstr(const char *haystack, const char *needle);

char *s21_strtok(char *str, const char *delim);

//sprintf
int my_pow(int dig, int poww);

char *inint(int dig);

int s21_sprintf(char *str, const char *format, ...);