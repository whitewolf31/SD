#include <stdio.h>

void process(int *vector, size_t vector_length) {
    if (vector_length == 1) { 
        printf("%d ", *vector);
        return;
    }
    process(vector, vector_length/2);
    if (vector_length % 2) {
        process(vector + vector_length/2 + 1, vector_length/2);
    } else {
        process(vector + vector_length/2, vector_length/2);
    }
}

int main(int argc, char *argv[]) {
    int n;
    scanf("%d", &n);
    int v[20];
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    process(v, n);
}