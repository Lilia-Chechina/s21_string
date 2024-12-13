#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void float_in_str(float val, int *length, int plus_flag, int accuracy, int null_flag) {
    int N = (int)val;
    float R = val - N;
    while (R != (int)R) {
        R *= 10;
    }
    int N_R = (int)R;
    printf("%d %d\n%f %f\n", N, N_R, R, val);
}

int main() {
    float val = 11233.512;
    int length = 5;
    int plus_flag = 1;
    int accuracy = 2;
    int null_flag = 0;
    float_in_str(val, &length, plus_flag, accuracy, null_flag);
    //printf("|%s|\n", float_in_str(val, &length, plus_flag, accuracy, null_flag));
    printf("|%f|\n", val);
    //printf("%d", length);
    return 0;
}