#include <stdio.h>
#include <stdlib.h>

void merge(int *a, int start, int mid, int end) {
    int finalLen = end - start + 1;
    int *b = (int *) calloc(finalLen, sizeof(int));
    int j = mid;
    int index = 0;
    while (start < mid && j <= end) {
        if (a[start] < a[j]) {
            b[index++] = a[start++];
        } else {
            b[index++] = a[j++];
        }
    }
    for (int i = start; i < mid; i++) b[index++] = a[i];
    for (int i = j; i <= end; i++) b[index++] = a[i];
    for (int i = 0; i < index; i++) {
        a[i] = b[i];
    }
    free(b);
}

void my_merge_sort(int vector[], size_t length) {
    if (length == 1) return;
    int middle = length / 2;
    my_merge_sort(vector, middle);
    if (length % 2){
         my_merge_sort(vector + middle, middle + 1);
         merge(vector, 0, middle, 2*middle);
    }
    else {
        my_merge_sort(vector + middle, middle);
        merge(vector, 0, middle, 2*middle - 1);
    }
}

int main(int argc, char *argv[]) {
    int v[9] = {1, 2, -2, 3, -3, 2, 2, 5, -2};
    my_merge_sort(v, 8);
    for (int i = 0; i < 8; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}