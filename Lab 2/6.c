#include <stdio.h>

void print_solution(int *vector) {
    for (int i = 0; i < 9; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");
}

void generate(int vector[], size_t vector_length) {
    if (vector_length == 0) {
        print_solution(vector);
        return;
    };
    if (vector_length > 6) {
        for (int i = 4; i <= 9; i++) {
            vector[9-vector_length] = i;
            generate(vector, vector_length - 1);
        }
    } else {
        vector[9-vector_length] = 13 - vector[6-vector_length];
        generate(vector, vector_length - 1);
    }
}

int main(int argc, char *argv[]) {
    int v[9];
    generate(v, 9);
}