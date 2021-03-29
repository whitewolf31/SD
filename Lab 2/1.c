#include <stdio.h>

int control(int x) {
    int s = 0;
    while (x > 0) {
        if (x % 2) s += x%10;
        x/=10;
    }
    if (s > 9) control(s);
    return s;
}

int main(int argc, char *argv[]) {
    printf("%d\n", control(98976));
}