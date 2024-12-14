#include <stdio.h>
#include <string.h>

int main() {
    char str1[] = "Hello";
    char str3[] = "Hellx";
    int result = memcmp(str1, str3, 4);
    printf("%d", result);

    return 0;
}
