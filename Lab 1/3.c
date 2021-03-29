#include <stdio.h>

double power(int base, int pow) {
    if (pow == 0) return 1;
    double help = power(base, pow/2);
    if (pow % 2) return base * help * help;
    return help * help;
}

int main(int argc, char *argv[]) {
    int base, pow;
    scanf("%d%d", &base, &pow);
    printf("%f\n", power(base, pow));
}