#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char *float_in_str(double val, int *length, int plus_flag, int accuracy, int null_flag, int accuracy_flag) {
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

int main() {
    double val = 11233.123;
    int length = 10;
    int length_2 = length;
    int plus_flag = 0;
    int accuracy = -1;
    int accuracy_flag = 1;
    int null_flag = 0;
    printf("|%s|\n", float_in_str(val, &length, plus_flag, accuracy, null_flag, accuracy_flag));
    //printf("|%s|\n", float_in_str(val, &length, plus_flag, accuracy, null_flag));
    printf("|%llf|\n", val);
    printf("%d", length);
    return 0;
}