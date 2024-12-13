#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <math.h>
#include "s21_string.h"

#define s21_NULL ((void*)0)

typedef unsigned long s21_size_t;

//1-3
void *s21_memchr(const void *str, int c, s21_size_t n) {
    const unsigned char *s = (const unsigned char *)str;
    unsigned char ch = (unsigned char)c;
    
    for (s21_size_t i = 0; i < n; i++) {
        if (s[i] == ch) {
            return (void *)(s + i);
        }
    }
    
    return s21_NULL;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    const unsigned char *p1 = (const unsigned char *)str1;
    const unsigned char *p2 = (const unsigned char *)str2;

    for (s21_size_t i = 0; i < n; i++) {
        if (p1[i] < p2[i]) {
            return -1;
        } else if (p1[i] > p2[i]) {
            return 1;
        }
    }

    return 0;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    
    for (s21_size_t i = 0; i < n; i++) {
        d[i] = s[i];
    }
    
    return dest;
}

//4-6
void *s21_memset(void *str, int c, s21_size_t n) {
    unsigned char *ptr = (unsigned char *)str;
    for (s21_size_t i = 0; i < n; i++) {
        ptr[i] = (unsigned char)c;
    }
    return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    s21_size_t dest_len = 0;  // длина строки 
    s21_size_t i;  // счетчик для копирования символов

    while (dest[dest_len] != '\0') {  // определяем длину строки 
        dest_len++;
    }

    for (i = 0; i < n && src[i] != '\0'; i++) {  // конкатенация src с dest, не превышая n символов
        dest[dest_len + i] = src[i];
    }

    dest[dest_len + i] = '\0';

    return dest;
}

char *s21_strchr(const char *str, int c) {
    char *result = s21_NULL; 
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

//7, 9
int s21_strncmp(const char *str1, const char *str2, size_t n) {
  for (; n > 0; n--, str1++, str2++) {
    if (*str1 != *str2) {
      break;
    }
  }
  if (n == 0)
    return 0;
  else
    return (*(unsigned char *)str1 - (*(unsigned char *)str2));
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t size = 0;
  while (!s21_strchr(str2, *str1) && *str1 != '\0') {
    str1++;
    size++;
  }
  return size;
}
//10-12
char *s21_strerror(int errnum) {
  static char buffer[256];
#ifdef __linux__
#define S21_ERR_NUM 134
  static const char *s21_errlist[] = {
      "Success",                           // Error 0
      "Operation not permitted",           // Error 1
      "No such file or directory",         // Error 2
      "No such process",                   // Error 3
      "Interrupted system call",           // Error 4
      "Input/output error",                // Error 5
      "No such device or address",         // Error 6
      "Argument list too long",            // Error 7
      "Exec format error",                 // Error 8
      "Bad file descriptor",               // Error 9
      "No child processes",                // Error 10
      "Resource temporarily unavailable",  // Error 11
      "Cannot allocate memory",            // Error 12
      "Permission denied",                 // Error 13
      "Bad address",                       // Error 14
      // todo: remaining error messages up to S21_ERR_NUM, we need to check
      // errmo.h.
  };
#elif defined(__APPLE__)
#define S21_ERR_NUM 107
  static const char *s21_errlist[] = {
      "Undefined error: 0",         // Error 0
      "Operation not permitted",    // Error 1
      "No such file or directory",  // Error 2
      "No such process",            // Error 3
      "Interrupted system call",    // Error 4
      "Input/output error",         // Error 5
      "Device not configured",      // Error 6
      "Argument list too long",     // Error 7
      "Exec format error",          // Error 8
      "Bad file descriptor",        // Error 9
      "No child processes",         // Error 10
      "Resource deadlock avoided",  // Error 11
      "Cannot allocate memory",     // Error 12
      "Permission denied",          // Error 13
      // todo: remaining error messages up to S21_ERR_NUM, we need to check
      // errmo.h.
  };
#else
#error "Unsupported platform"
#endif

  if (errnum >= 0 && errnum < S21_ERR_NUM) {
    return (char *)s21_errlist[errnum];
  } else {
    // Construct "Unknown error <errnum>"
    char num_str[12];  // Enough for 32-bit int
    int num = errnum;
    int is_negative = 0;
    int i = 0;
    if (num < 0) {
      is_negative = 1;
      num = -num;  // Make positive
    }
    do {
      num_str[i++] = '0' + (num % 10);
      num /= 10;
    } while (num > 0);
    if (is_negative) {
      num_str[i++] = '-';
    }
    num_str[i] = '\0';
    for (int j = 0; j < i / 2; j++) {
      char temp = num_str[j];
      num_str[j] = num_str[i - j - 1];
      num_str[i - j - 1] = temp;
    }
    const char *unknown_error = "Unknown error ";
    size_t msg_len = s21_strlen(unknown_error);
    s21_memcpy(buffer, unknown_error, msg_len);
    s21_memcpy(buffer + msg_len, num_str, s21_strlen(num_str) + 1);

    return buffer;
  }
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t length = 0;
  while (str && str[length] != '\0') {
    length++;
  }
  return length;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *res = NULL;
  if (!str1 || !str2) res = NULL;  // костыль

  while (*str1) {
    const char *s = str2;
    while (*s) {
      if (*str1 == *s) {
        res = (char *)str1;
      }
      s++;
    }
    str1++;
  }
  return res;
}

//13-15
char *s21_strrchr(const char *str, int c) {
    char *res = s21_NULL;
    for (int i = 0; str[i] != '\0'; i++) {
        if ((int)str[i] == c) {
            res = (char *)&str[i];
        }
    }
    return res;
}

char *s21_strstr(const char *haystack, const char *needle) {
    char *res = s21_NULL;
    int err = 0;
    for (int x = 0; haystack[x] != '\0'; x++) {
        err = 0;
        for (int y = 0; needle[y] != '\0'; y++) {
            if (needle[y] != haystack[x + y]) {
                err = 1;
                break;
            }
        }
        if (err == 0) {
            res = (char *)&haystack[x];
            break;
        }
    }
    return res;
}

char *s21_strtok(char *str, const char *delim) {
    static char *last = s21_NULL;
    char *token = s21_NULL;

    if (str != s21_NULL) {
        last = str;
    }

    
    while (last != s21_NULL && *last && s21_strchr(delim, *last)) {
        last++;
    }


    if (last == s21_NULL || *last == '\0') {
        token = s21_NULL;
    } else {
       
        token = last;

        
        while (*last && !s21_strchr(delim, *last)) {
            last++;
        }

        
        if (*last) {
            *last = '\0';
            last++;
        }
    }

    return token;
}

//sprintf

int is_int(char val) {
    int res = 1;
    if (val >= 48 && val <= 57) res = 0;
    return res;
}

char *int_in_str(int val, int *length, int plus_flag, int null_flag, int accuracy_flag, int accuracy) {
    int len = 0;
    int res_val = val;
    if (val == 0) len = 1;
    else {
        if (res_val < 0) res_val = -res_val;
        len = (int)(log10(res_val)) + 1;
    }
    int size = len;
    int count = 0;
    int cura = 0;
    if (val < 0) len++;
    if (len > (*length)) (*length) = len;
    if (accuracy > len && accuracy > (*length)) (*length) = accuracy;
    char *res = malloc(sizeof(char) * (*length));
    char point = ' ';
    if (null_flag == 1 && accuracy_flag == 0) point = '0';
    for (int i = 0; i < (*length); i++) {
        res[i] = point;
    }
    if (plus_flag == 1) {
        if (val < 0) {
            res[(*length) - len] = '-';
            count = (*length) - len + 1;
        } else count = (*length) - len;
        for (int i = count - accuracy + len; i < count; i++) {
            res[i] = '0';
        }

        for (int i = count; i < (*length); i++) {
            cura = (int)(res_val / pow(10, size - 1)) + 48;
            res[i] = cura;
            res_val = res_val - pow(10, size - 1) * (cura - 48);
            size--;
        }
    } else {
        if (val < 0) {
            count = 1;
            res[0] = '-';
        }
        int res_size = size;
        for (int i = count; i < accuracy - len; i++) {
            res[i] = '0';
            count++;
        }
        for (int i = count; i < res_size + count; i++) {
            cura = (int)(res_val / pow(10, size - 1)) + 48;
            res[i] = cura;
            res_val = res_val - pow(10, size - 1) * (cura - 48);
            size--;
        }
    }
    return res;
}

char *long_int_in_str(long int val, int *length, int plus_flag, int null_flag, int accuracy_flag, int accuracy) {
    int len = 0;
    long int res_val = val;
    if (val == 0) len = 1;
    else {
        if (res_val < 0) res_val = -res_val;
        len = (long int)(log10(res_val)) + 1;
    }
    int size = len;
    int count = 0;
    int cura = 0;
    if (val < 0) len++;
    if (len > (*length)) (*length) = len;
    if (accuracy > len && accuracy > (*length)) (*length) = accuracy;
    char *res = malloc(sizeof(char) * (*length));
    char point = ' ';
    if (null_flag == 1 && accuracy_flag == 0) point = '0';
    for (int i = 0; i < (*length); i++) {
        res[i] = point;
    }
    if (plus_flag == 1) {
        if (val < 0) {
            res[(*length) - len] = '-';
            count = (*length) - len + 1;
        } else count = (*length) - len;
        for (int i = count - accuracy + len; i < count; i++) {
            res[i] = '0';
        }

        for (int i = count; i < (*length); i++) {
            cura = (int)(res_val / pow(10, size - 1)) + 48;
            res[i] = cura;
            res_val = res_val - pow(10, size - 1) * (cura - 48);
            size--;
        }
    } else {
        if (val < 0) {
            count = 1;
            res[0] = '-';
        }
        int res_size = size;
        for (int i = count; i < accuracy - len; i++) {
            res[i] = '0';
            count++;
        }
        for (int i = count; i < res_size + count; i++) {
            cura = (int)(res_val / pow(10, size - 1)) + 48;
            res[i] = cura;
            res_val = res_val - pow(10, size - 1) * (cura - 48);
            size--;
        }
    }

    return res;
}

char *short_int_in_str(short int val, int *length, int plus_flag, int null_flag, int accuracy_flag, int accuracy) {
    int len = 0;
    short int res_val = val;
    if (val == 0) len = 1;
    else {
        if (res_val < 0) res_val = -res_val;
        len = (short int)(log10(res_val)) + 1;
    }
    int size = len;
    int count = 0;
    int cura = 0;
    if (val < 0) len++;
    if (len > (*length)) (*length) = len;
    if (accuracy > len && accuracy > (*length)) (*length) = accuracy;
    char *res = malloc(sizeof(char) * (*length));
    char point = ' ';
    if (null_flag == 1 && accuracy_flag == 0) point = '0';
    for (int i = 0; i < (*length); i++) {
        res[i] = point;
    }
    if (plus_flag == 1) {
        if (val < 0) {
            res[(*length) - len] = '-';
            count = (*length) - len + 1;
        } else count = (*length) - len;
        for (int i = count - accuracy + len; i < count; i++) {
            res[i] = '0';
        }

        for (int i = count; i < (*length); i++) {
            cura = (int)(res_val / pow(10, size - 1)) + 48;
            res[i] = cura;
            res_val = res_val - pow(10, size - 1) * (cura - 48);
            size--;
        }
    } else {
        if (val < 0) {
            count = 1;
            res[0] = '-';
        }
        int res_size = size;
        for (int i = count; i < accuracy - len; i++) {
            res[i] = '0';
            count++;
        }
        for (int i = count; i < res_size + count; i++) {
            cura = (int)(res_val / pow(10, size - 1)) + 48;
            res[i] = cura;
            res_val = res_val - pow(10, size - 1) * (cura - 48);
            size--;
        }
    }

    return res;
}

char *long_long_int_in_str(long long int val, int *length, int plus_flag, int null_flag, int accuracy_flag, int accuracy) {
    int len = 0;
    long long int res_val = val;
    if (val == 0) len = 1;
    else {
        if (res_val < 0) res_val = -res_val;
        len = (long long int)(log10(res_val)) + 1;
    }
    int size = len;
    int count = 0;
    int cura = 0;
    if (val < 0) len++;
    if (len > (*length)) (*length) = len;
    if (accuracy > len && accuracy > (*length)) (*length) = accuracy;
    char *res = malloc(sizeof(char) * (*length));
    char point = ' ';
    if (null_flag == 1 && accuracy_flag == 0) point = '0';
    for (int i = 0; i < (*length); i++) {
        res[i] = point;
    }
    if (plus_flag == 1) {
        if (val < 0) {
            res[(*length) - len] = '-';
            count = (*length) - len + 1;
        } else count = (*length) - len;
        for (int i = count - accuracy + len; i < count; i++) {
            res[i] = '0';
        }

        for (int i = count; i < (*length); i++) {
            cura = (int)(res_val / pow(10, size - 1)) + 48;
            res[i] = cura;
            res_val = res_val - pow(10, size - 1) * (cura - 48);
            size--;
        }
    } else {
        if (val < 0) {
            count = 1;
            res[0] = '-';
        }
        int res_size = size;
        for (int i = count; i < accuracy - len; i++) {
            res[i] = '0';
            count++;
        }
        for (int i = count; i < res_size + count; i++) {
            cura = (int)(res_val / pow(10, size - 1)) + 48;
            res[i] = cura;
            res_val = res_val - pow(10, size - 1) * (cura - 48);
            size--;
        }
    }

    return res;
}

char *unsigned_int_in_str(unsigned int val, int *length, int plus_flag, int null_flag, int accuracy_flag, int accuracy) {
    int len = 0;
    long int res_val = val;
    if (val == 0) len = 1;
    else {
        if (res_val < 0) res_val = -res_val;
        len = (unsigned int)(log10(res_val)) + 1;
    }
    int size = len;
    int count = 0;
    int cura = 0;
    
    if (len > (*length)) (*length) = len;
    if (accuracy > len && accuracy > (*length)) (*length) = accuracy;
    char *res = malloc(sizeof(char) * (*length));
    char point = ' ';
    if (null_flag == 1 && accuracy_flag == 0) point = '0';
    for (int i = 0; i < (*length); i++) {
        res[i] = point;
    }
    if (plus_flag == 1) {
        count = (*length) - len;
        for (int i = count - accuracy + len; i < count; i++) {
            res[i] = '0';
        }

        for (int i = count; i < (*length); i++) {
            cura = (int)(res_val / pow(10, size - 1)) + 48;
            res[i] = cura;
            res_val = res_val - pow(10, size - 1) * (cura - 48);
            size--;
        }
    } else {
        int res_size = size;
        for (int i = count; i < accuracy - len; i++) {
            res[i] = '0';
            count++;
        }
        for (int i = count; i < res_size + count; i++) {
            cura = (int)(res_val / pow(10, size - 1)) + 48;
            res[i] = cura;
            res_val = res_val - pow(10, size - 1) * (cura - 48);
            size--;
        }
    }

    return res;
}

char *unsigned_short_int_in_str(unsigned short int val, int *length, int plus_flag, int null_flag, int accuracy_flag, int accuracy) {
    int len = 0;
    long int res_val = val;
    if (val == 0) len = 1;
    else {
        if (res_val < 0) res_val = -res_val;
        len = (unsigned short int)(log10(res_val)) + 1;
    }
    int size = len;
    int count = 0;
    int cura = 0;
    
    if (len > (*length)) (*length) = len;
    if (accuracy > len && accuracy > (*length)) (*length) = accuracy;
    char *res = malloc(sizeof(char) * (*length));
    char point = ' ';
    if (null_flag == 1 && accuracy_flag == 0) point = '0';
    for (int i = 0; i < (*length); i++) {
        res[i] = point;
    }
    if (plus_flag == 1) {
        count = (*length) - len;
        for (int i = count - accuracy + len; i < count; i++) {
            res[i] = '0';
        }

        for (int i = count; i < (*length); i++) {
            cura = (int)(res_val / pow(10, size - 1)) + 48;
            res[i] = cura;
            res_val = res_val - pow(10, size - 1) * (cura - 48);
            size--;
        }
    } else {
        int res_size = size;
        for (int i = count; i < accuracy - len; i++) {
            res[i] = '0';
            count++;
        }
        for (int i = count; i < res_size + count; i++) {
            cura = (int)(res_val / pow(10, size - 1)) + 48;
            res[i] = cura;
            res_val = res_val - pow(10, size - 1) * (cura - 48);
            size--;
        }
    }

    return res;
}

char *unsigned_long_int_in_str(unsigned long int val, int *length, int plus_flag, int null_flag, int accuracy_flag, int accuracy) {
    int len = 0;
    long int res_val = val;
    if (val == 0) len = 1;
    else {
        if (res_val < 0) res_val = -res_val;
        len = (unsigned long int)(log10(res_val)) + 1;
    }
    int size = len;
    int count = 0;
    int cura = 0;
    
    if (len > (*length)) (*length) = len;
    if (accuracy > len && accuracy > (*length)) (*length) = accuracy;
    char *res = malloc(sizeof(char) * (*length));
    char point = ' ';
    if (null_flag == 1 && accuracy_flag == 0) point = '0';
    for (int i = 0; i < (*length); i++) {
        res[i] = point;
    }
    if (plus_flag == 1) {
        count = (*length) - len;
        for (int i = count - accuracy + len; i < count; i++) {
            res[i] = '0';
        }

        for (int i = count; i < (*length); i++) {
            cura = (int)(res_val / pow(10, size - 1)) + 48;
            res[i] = cura;
            res_val = res_val - pow(10, size - 1) * (cura - 48);
            size--;
        }
    } else {
        int res_size = size;
        for (int i = count; i < accuracy - len; i++) {
            res[i] = '0';
            count++;
        }
        for (int i = count; i < res_size + count; i++) {
            cura = (int)(res_val / pow(10, size - 1)) + 48;
            res[i] = cura;
            res_val = res_val - pow(10, size - 1) * (cura - 48);
            size--;
        }
    }

    return res;
}

char *unsigned_long_long_int_in_str(unsigned long long int val, int *length, int plus_flag, int null_flag, int accuracy_flag, int accuracy) {
    int len = 0;
    long int res_val = val;
    if (val == 0) len = 1;
    else {
        if (res_val < 0) res_val = -res_val;
        len = (unsigned long long int)(log10(res_val)) + 1;
    }
    int size = len;
    int count = 0;
    int cura = 0;
    
    if (len > (*length)) (*length) = len;
    if (accuracy > len && accuracy > (*length)) (*length) = accuracy;
    char *res = malloc(sizeof(char) * (*length));
    char point = ' ';
    if (null_flag == 1 && accuracy_flag == 0) point = '0';
    for (int i = 0; i < (*length); i++) {
        res[i] = point;
    }
    if (plus_flag == 1) {
        count = (*length) - len;
        for (int i = count - accuracy + len; i < count; i++) {
            res[i] = '0';
        }

        for (int i = count; i < (*length); i++) {
            cura = (int)(res_val / pow(10, size - 1)) + 48;
            res[i] = cura;
            res_val = res_val - pow(10, size - 1) * (cura - 48);
            size--;
        }
    } else {
        int res_size = size;
        for (int i = count; i < accuracy - len; i++) {
            res[i] = '0';
            count++;
        }
        for (int i = count; i < res_size + count; i++) {
            cura = (int)(res_val / pow(10, size - 1)) + 48;
            res[i] = cura;
            res_val = res_val - pow(10, size - 1) * (cura - 48);
            size--;
        }
    }

    return res;
}

char *char_in_str(char val, int *length, int plus_flag) {
    if ((*length) < 1) (*length) = 1;
    char *res = malloc(sizeof(char) * (*length));
    for (int i = 0; i < (*length); i++) {
        res[i] = ' ';
    }
    if (plus_flag == 1) {
        res[(*length) - 1] = val;
    } else {
        res[0] = val;
    }
    return res;
}

char *str_in_str(char *val, int *length, int plus_flag, int accuracy) {
    int len = 0;
    while(1) {
        if (val[len] == '\0' || len >= accuracy) break;
        len++;
    }
    if (len > (*length)) (*length) = len;
    char *res = malloc(sizeof(char) * (*length));
    for (int i = 0; i < (*length); i++) {
        res[i] = ' ';
    }
    if (plus_flag == 1) {
        int count = 0;
        for (int i = (*length) - len; i < (*length); i++) {
            res[i] = val[count];
            count++;
        }
    } else {
        for (int i = 0; i < len; i++) {
            res[i] = val[i];
        }
    }
    return res;
}

char *float_in_str(float val, int *length, int plus_flag, int accuracy, int null_flag, int accuracy_flag) {
    int N = (int)val;
    int pointer = 6;
    int count = 0;
    int cura = 0;
    if (accuracy_flag == 1 && accuracy >= 0) pointer = accuracy;
    int R = rint(((val - (int)val) * pow (10, pointer + 1)) / 10);
    int len_1 = 0;
    if (N == 0) len_1 = 1;
    else len_1 = log10(N) + 1;
    int len_2 = pointer;
    int len = len_1 + len_2;
    int size = len_1;
    int size_2 = len_2;
    if (pointer != 0) len++;
    if (len > (*length)) (*length) = len;
    char *res = malloc(sizeof(char) * (*length));
    char point = ' ';
    if (null_flag == 1) point = '0';
    for (int i = 0; i < (*length); i++) {
        res[i] = point;
    }
    int res_val = N;
    if (plus_flag == 1) {
        if (val < 0) {
            res_val = -res_val;
            res[(*length) - len] = '-';
            count = (*length) - len;
        } else count = (*length) - len;
        for (int i = count; i < (*length) - len_2 - 1; i++) {
            cura = (int)(res_val / pow(10, size - 1)) + 48;
            res[i] = cura;
            res_val = res_val - pow(10, size - 1) * (cura - 48);
            size--;
        }
        if (pointer > 0) res[(*length) - len_2 - 1] = '.';
        for (int i = (*length) - len_2; i < (*length); i++) {
            cura = (int)(R / pow(10, size_2 - 1)) + 48;
            res[i] = cura;
            R = R - pow(10, size_2 - 1) * (cura - 48);
            size_2--;
        }
    } else {
        if (val < 0) {
            res_val = -res_val;
            res[0] = '-';
            count = 1;
        } else count = 0;
        for (int i = count; i < len_1; i++) {
            cura = (int)(res_val / pow(10, size - 1)) + 48;
            res[i] = cura;
            res_val = res_val - pow(10, size - 1) * (cura - 48);
            size--;
        }
        if (pointer > 0) res[len_1] = '.';
        for (int i = len_1 + 1; i < len; i++) {
            cura = (int)(R / pow(10, size_2 - 1)) + 48;
            res[i] = cura;
            R = R - pow(10, size_2 - 1) * (cura - 48);
            size_2--;
        }
    }
    return res;
}

char *double_in_str(double val, int *length, int plus_flag, int accuracy, int null_flag, int accuracy_flag) {
    int N = (int)val;
    int pointer = 6;
    int count = 0;
    int cura = 0;
    if (accuracy_flag == 1 && accuracy >= 0) pointer = accuracy;
    int R = rint(((val - (int)val) * pow (10, pointer + 1)) / 10);
    int len_1 = 0;
    if (N == 0) len_1 = 1;
    else len_1 = log10(N) + 1;
    int len_2 = pointer;
    int len = len_1 + len_2;
    int size = len_1;
    int size_2 = len_2;
    if (pointer != 0) len++;
    if (len > (*length)) (*length) = len;
    char *res = malloc(sizeof(char) * (*length));
    char point = ' ';
    if (null_flag == 1) point = '0';
    for (int i = 0; i < (*length); i++) {
        res[i] = point;
    }
    int res_val = N;
    if (plus_flag == 1) {
        if (val < 0) {
            res_val = -res_val;
            res[(*length) - len] = '-';
            count = (*length) - len;
        } else count = (*length) - len;
        for (int i = count; i < (*length) - len_2 - 1; i++) {
            cura = (int)(res_val / pow(10, size - 1)) + 48;
            res[i] = cura;
            res_val = res_val - pow(10, size - 1) * (cura - 48);
            size--;
        }
        if (pointer > 0) res[(*length) - len_2 - 1] = '.';
        for (int i = (*length) - len_2; i < (*length); i++) {
            cura = (int)(R / pow(10, size_2 - 1)) + 48;
            res[i] = cura;
            R = R - pow(10, size_2 - 1) * (cura - 48);
            size_2--;
        }
    } else {
        if (val < 0) {
            res_val = -res_val;
            res[0] = '-';
            count = 1;
        } else count = 0;
        for (int i = count; i < len_1; i++) {
            cura = (int)(res_val / pow(10, size - 1)) + 48;
            res[i] = cura;
            res_val = res_val - pow(10, size - 1) * (cura - 48);
            size--;
        }
        if (pointer > 0) res[len_1] = '.';
        for (int i = len_1 + 1; i < len; i++) {
            cura = (int)(R / pow(10, size_2 - 1)) + 48;
            res[i] = cura;
            R = R - pow(10, size_2 - 1) * (cura - 48);
            size_2--;
        }
    }
    return res;
}

void spech(char *str, int *count, int *i, char format_1, char format_2, char format_3, va_list *arg, int length, int accuracy_flag, int accuracy, int plus_flag, int null_flag) {
    char *res = NULL;
    if (format_1 == 'd') {
        int val = va_arg(*arg, int);
        res = int_in_str(val, &length, plus_flag, null_flag, accuracy_flag, accuracy);
    } else if (format_1 == 'l' && format_2 == 'd') {
        (*i)++;
        long int val = va_arg(*arg, long int);
        res = long_int_in_str(val, &length, plus_flag, null_flag, accuracy_flag, accuracy);
    } else if (format_1 == 'h' && format_2 == 'd') {
        (*i)++;
        short int val = va_arg(*arg, int);
        res = short_int_in_str(val, &length, plus_flag, null_flag, accuracy_flag, accuracy);
    } else if (format_1 == 'l' && format_2 == 'l' && format_3 == 'd') {
        (*i) += 2;
        long long int val = va_arg(*arg, long long int);
        res = long_int_in_str(val, &length, plus_flag, null_flag, accuracy_flag, accuracy);
    } else if (format_1 == 'u') {
        unsigned int val = va_arg(*arg, unsigned int);
        res = unsigned_int_in_str(val, &length, plus_flag, null_flag, accuracy_flag, accuracy);
    } else if (format_1 == 'l' && format_2 == 'u') {
        (*i)++;
        unsigned long int val = va_arg(*arg, unsigned long int);
        res = unsigned_long_int_in_str(val, &length, plus_flag, null_flag, accuracy_flag, accuracy);
    } else if (format_1 == 'h' && format_2 == 'u') {
        (*i)++;
        unsigned short int val = va_arg(*arg, int);
        res = unsigned_short_int_in_str(val, &length, plus_flag, null_flag, accuracy_flag, accuracy);
    } else if (format_1 == 'l' && format_2 == 'l' && format_3 == 'u') {
        (*i) += 2;
        unsigned long long int val = va_arg(*arg, unsigned long long int);
        res = unsigned_long_long_int_in_str(val, &length, plus_flag, null_flag, accuracy_flag, accuracy);
    } else if (format_1 == 'c') {
        char val = va_arg(*arg, int);
        res = char_in_str(val, &length, plus_flag);
    } else if (format_1 == 's') {
        char *val = va_arg(*arg, char*);
        res = str_in_str(val, &length, plus_flag, accuracy);
    } else if (format_1 == 'f') {
        float val = va_arg(*arg, double);
        res = float_in_str(val, &length, plus_flag, accuracy, null_flag, accuracy_flag);
    } else if (format_1 == 'l' && format_2 == 'f') {
        (*i)++;
        double val = va_arg(*arg, double);
        res = double_in_str(val, &length, plus_flag, accuracy, null_flag, accuracy_flag);
    }
    if (res != NULL) {
        for (int x = 0; x < length; x++) {
            str[(*count)++] = res[x];
        }
        free(res);
    }
}

int s21_sprintf(char *str, const char *format, ...) {
    va_list arg;
    va_start(arg, format);
    int count = 0;
    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%' && format[i + 1] != '\0') {
            i++;
            int plus_flag = 1;
            int null_flag = 0;
            int length = 0; //ширина
            int accuracy = 0; //точность
            int accuracy_flag = 0;
            //проверка флагов
            if (format[i] == ' ' || format[i] == '+') {
                i++;
                plus_flag = 1;
            } else if (format[i] == '-') {
                i++;
                plus_flag = 0;
            } else if (format[i] == '0') {
                i++;
                null_flag = 1;
            }
            //проверка ширины
            if (format[i] == '*') {
                length = va_arg(arg, int);
                i++;
            } else if (!is_int(format[i])) {
                int size = 0;
                char *char_int_1 = malloc(sizeof(char) * size);
                char *char_int = s21_NULL;
                while (!is_int(format[i])) {
                    char_int = realloc(char_int_1, sizeof(char) * (++size));
                    char_int[size - 1] = format[i];
                    i++;
                    char_int_1 = char_int;
                }
                for (int x = 0; x < size; x++) {
                    length += (pow(10, size - x - 1)) * (char_int[x] - 48);
                }
                free(char_int);
                char_int = NULL;
            }
            //проверка точности
            if (format[i] == '.') {
                i++;
                if (format[i] == '*') {
                    accuracy = va_arg(arg, int);
                    accuracy_flag = 1;
                    i++;
                } else if (!is_int(format[i])) {
                    accuracy_flag = 1;
                    int size = 0;
                    char *char_int_1 = malloc(sizeof(char) * size);
                    char *char_int = s21_NULL;
                    while (!is_int(format[i])) {
                        char_int = realloc(char_int_1, sizeof(char) * (++size));
                        char_int[size - 1] = format[i];
                        i++;
                        char_int_1 = char_int;
                    }
                    for (int x = 0; x < size; x++) {
                        accuracy += (pow(10, size - x - 1)) * (char_int[x] - 48);
                    }
                    free(char_int);
                    char_int = NULL;
                }
            }
            spech(str, &count, &i, format[i], format[i + 1], format[i + 2], &arg, length, accuracy_flag, accuracy, plus_flag, null_flag);
        } else {
            str[count++] = format[i];
        }
    }
    str[count] = '\0';
    va_end(arg);
    return count;
}

//5
