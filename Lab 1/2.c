#include <stdio.h>

int fibonacci(int k) {
    if (k > 2) return fibonacci(k-1) + fibonacci(k-2);
    return 1;
}

int main (int argc, char *argv[]) {
    int k;
    scanf("%d", &k);
    printf("%d\n", fibonacci(k));
}