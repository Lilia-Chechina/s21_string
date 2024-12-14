

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


s21_size_t s21_strlen(const char *str) {
    s21_size_t length = 0;
    if (str != s21_NULL) {
        while (str[length] != '\0') {
            length++;
        }
    }
    return length;
}

void *to_upper(const char *str) {
    static char result[MAX_LEN];
    if (str == s21_NULL) {
        return s21_NULL;
    }
    s21_size_t len = s21_strlen(str);
    for (s21_size_t i = 0; i < len; i++) {
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
    if (str == s21_NULL) {
        return s21_NULL;
    }
    s21_size_t len = s21_strlen(str);
    for (s21_size_t i = 0; i < len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            result[i] = str[i] + 32;
        } else {
            result[i] = str[i];
        }
    }
    result[len] = '\0';

    return result;
}

void *insert(const char *src, const char *str, s21_size_t start_index) {
    static char result[MAX_LEN] = {0};
    if (src && str && start_index <= s21_strlen(src)) {
        s21_size_t src_len = s21_strlen(src);
        s21_size_t str_len = s21_strlen(str);

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
        s21_size_t start = 0, end = s21_strlen(src);

        while (start < end && s21_strchr(trim_chars, src[start])) {
            start++;
        }

        while (end > start && s21_strchr(trim_chars, src[end - 1])) {
            end--;
        }

        s21_size_t len = end - start;
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


// ТЕСТЫ


START_TEST(test_s21_to_upper_edge) {
    ck_assert_str_eq(to_upper("hello"), "HELLO");
    ck_assert_str_eq(to_upper("HELLO"), "HELLO");
    ck_assert_str_eq(to_upper(""), "");
    ck_assert_str_eq(to_upper("123abc"), "123ABC");
}
END_TEST

START_TEST(test_s21_to_lower_edge) {
    ck_assert_str_eq(to_lower("HELLO"), "hello");
    ck_assert_str_eq(to_lower("hello"), "hello");
    ck_assert_str_eq(to_lower(""), "");
    ck_assert_str_eq(to_lower("123ABC"), "123abc");
}
END_TEST

START_TEST(test_21_insert_edge) {
    ck_assert_str_eq(insert("hello", "world", 5), "helloworld");
    ck_assert_str_eq(insert("hello", "world", 0), "worldhello");
    ck_assert_str_eq(insert("", "world", 0), "world");
    ck_assert_str_eq(insert("hello", "", 3), "hello");
}
END_TEST

START_TEST(test_s21_trim_edge) {
    ck_assert_str_eq(trim("  hello  ", " "), "hello");
    ck_assert_str_eq(trim("--hello--", "-"), "hello");
    ck_assert_str_eq(trim("hello", " "), "hello");
    ck_assert_str_eq(trim("", " "), "");
}
END_TEST


tcase_add_test(tc_edge, test_s21_to_upper_edge);
tcase_add_test(tc_edge, test_s21_to_lower_edge);
tcase_add_test(tc_edge, test_21_insert_edge);
tcase_add_test(tc_edge, test_s21_trim_edge);
