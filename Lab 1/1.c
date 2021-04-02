#include <stdio.h>

int count_equals(int value, int *vector, size_t vector_length) {
    if (vector_length > 1) {
        if (*vector == value) return 1 + count_equals(value, vector + 1, vector_length - 1);
        return count_equals(value, vector + 1, vector_length - 1);
    }
    if (*vector == value) return 1;
    return 0;
}

int main(int argc, char *argv[]) {
    int n;
    scanf("%d", &n);
    int v[100];
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    int value;
    scanf("%d", &value);
    printf("%d\n", count_equals(value, v, n));
}