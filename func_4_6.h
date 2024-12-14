#ifndef INC_FUNC_4_6
#define INC_FUNC_4_6

#define s21_NULL ((void *)0)
typedef unsigned long s21_size_t;

char *s21_strchr(const char *str, int c);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);

#endif
