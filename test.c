#include <stdio.h>

int main() {
    char a[30];
    a[0] = 195;
    a[1] = 169;
    a[2] = '\0';
    printf("%s\n", a);
    return 0;
}