#include <stdio.h>

double nth_random_value(size_t n) {
    if (n == 1) return 0.45;
    else {
        double help = nth_random_value(n-1);
        return 3.75 * help * (1 - help);
    }
}

int main(int argc, char *argv[]) {
    int n;
    scanf("%d", &n);
    printf("%.2f\n", nth_random_value(n));
}