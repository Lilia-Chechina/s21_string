#include <stdio.h>
#include <stdlib.h>

char* to_lower(const char *str) {
    int len = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        len++;
    }
    char res[len];
    char *point = res;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] > 'A' && str[i] < 'Z') {
            res[i] = str[i] + 32;
        } else {
            res[i] = str[i];
        }
    }
    res[len] = '\0';
    return point;
}

int main() {

    char my_str[1024] = "LoX PiDr1235 45846";
    char *my_new_str = to_lower(my_str);
    printf("\n%s\n\n", my_new_str);
    free(my_str);
    return 0;
}