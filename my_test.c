#include <stdio.h>

int main() {
    char buffer[50];
    int result = s21_sprintf(buffer, "%d %s", 12345, "Hello");
    printf("%d", result);

    return 0;
}
