#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "s21_string.h"

int main() {

    /*
    const char *str = "Hello, world!";
    char ch = 'o';
    
    // Ищем последний символ 'o' в строке
    char *result = s21_strchr(str, ch);
    
    if (result != NULL) {
        printf("Последнее вхождение символа '%c' найдено по адресу: %p\n", ch, (void*)result);
        printf("Остальная строка: %s\n", result);
    } else {
        printf("Символ '%c' не найден.\n", ch);
    }
    */

    /*
    const char *str = "Hello, world!";
    char ch = 'o';
    
    // Ищем последний символ 'o' в строке
    char *result = s21_strrchr(str, ch);
    
    if (result != NULL) {
        printf("Последнее вхождение символа '%c' найдено по адресу: %p\n", ch, (void*)result);
        printf("Остальная строка: %s\n", result);
    } else {
        printf("Символ '%c' не найден.\n", ch);
    }
    */

    /*
    const char *haystack = "Hello, world!";
    const char *needle = "world";

    // Ищем подстроку "world" в строке "Hello, world!"
    char *result = s21_strstr(haystack, needle);

    if (result != NULL) {
        printf("Подстрока '%s' найдена. Она начинается с: %s\n", needle, result);
    } else {
        printf("Подстрока '%s' не найдена.\n", needle);
    }
    */

    /*
    char str[] = "Hello, world! How are you?";
    const char *delim = " ,!?";  // Разделители: пробел, запятая, восклицательный знак, вопросительный знак
    
    // Разбиваем строку на токены
    char *token = s21_strtok(str, delim);  // Получаем первый токен

    while (token != NULL) {
        printf("Токен: %s\n", token);  // Выводим текущий токен
        token = s21_strtok(NULL, delim);   // Получаем следующий токен
    }
    */

    /*
    int age = 25;
    float height = 1.75;
    char name[] = "John";
    
    char result[100];  // Строка для хранения отформатированного вывода
    
    // Форматируем строку
    int length = s21_sprintf(result, "Name: %s, Age: %d, Height: %.2f", name, age, height);
    
    // Выводим результат
    printf("Formatted string: %s\n", result);
    printf("Length of the formatted string: %d\n", length);
    */

    char buff[1024];
    char *format = "He1111111111111llo %u %c %s world";
    int len = 0;

    //len = s21_sprintf(buff, format, +123, 'c', "yes");

    //printf("%s, %d\n", buff, len);

    len = sprintf(buff, format, -123, 'c', "yes");

    printf("%s, %d\n", buff, len);
    unsigned les = -123;
    printf("%d", (int)les);

    return 0;
}