#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "func_4_6.h"

void test_s21_strchr() {
  printf("Testing s21_strchr...\n");

  const char *str = "hello world";

  // Тест 1: Символ есть в строке
  assert(s21_strchr(str, 'w') == strchr(str, 'w'));

  // Тест 2: Символ отсутствует в строке
  assert(s21_strchr(str, 'z') == strchr(str, 'z'));

  // Тест 3: Символ является null-терминатором
  assert(s21_strchr(str, '\0') == strchr(str, '\0'));

  // Тест 4: Пустая строка
  assert(s21_strchr("", 'a') == strchr("", 'a'));

  printf("s21_strchr tests passed!\n\n");
}

void test_s21_memset() {
  printf("Testing s21_memset...\n");

  char buffer1[20] = "original string";
  char buffer2[20] = "original string";

  // Тест 1: Заполнение символом
  assert(memcmp(s21_memset(buffer1, 'x', 5), memset(buffer2, 'x', 5), 20) == 0);

  // Тест 2: Заполнение нулями
  assert(memcmp(s21_memset(buffer1, 0, 10), memset(buffer2, 0, 10), 20) == 0);

  // Тест 3: Нулевой размер
  assert(memcmp(s21_memset(buffer1, 'y', 0), memset(buffer2, 'y', 0), 20) == 0);

  printf("s21_memset tests passed!\n\n");
}

void test_s21_strncat() {
  printf("Testing s21_strncat...\n");

  char dest1[30] = "hello ";
  char dest2[30] = "hello ";
  const char *src = "world!";

  // Тест 1: Конкатенация с ограничением
  assert(strcmp(s21_strncat(dest1, src, 3), strncat(dest2, src, 3)) == 0);

  // Тест 2: Конкатенация всей строки
  assert(strcmp(s21_strncat(dest1, src, strlen(src)),
                strncat(dest2, src, strlen(src))) == 0);

  // Тест 3: Нулевой размер
  assert(strcmp(s21_strncat(dest1, src, 0), strncat(dest2, src, 0)) == 0);

  // Тест 4: Пустая строка
  char empty_dest1[30] = "hello ";
  char empty_dest2[30] = "hello ";
  assert(strcmp(s21_strncat(empty_dest1, "", 5), strncat(empty_dest2, "", 5)) ==
         0);

  printf("s21_strncat tests passed!\n\n");
}

int main() {
  test_s21_strchr();
  test_s21_memset();
  test_s21_strncat();

  printf("All tests passed!\n");
  return 0;
}
