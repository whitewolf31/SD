#include <stdio.h>

unsigned greatest_commond_divisor(unsigned a, unsigned b) {
   if (a != b) {
       if (a > b) a = greatest_commond_divisor(a - b, b);
       else a = greatest_commond_divisor(b - a, a);
   }
   return a; 
}

unsigned least_common_multiple(unsigned a, unsigned b) {
    return a * b / greatest_commond_divisor(a, b);
}

int main(int argc, char *argv[]) {
    printf("%d\n", least_common_multiple(24, 130));
}