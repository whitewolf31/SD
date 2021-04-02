#include <stdio.h>
#include <math.h>

double bin_search(double left, double right, double value) {
    double mid = (left + right) / 2;
    double foundVal = mid*mid - value;
    if (fabs(foundVal) < 0.001) return mid;
    else if (foundVal > 0) return bin_search(left, mid, value);
    else return bin_search(mid, right, value);
}

double my_sqrt(double base) {
    return bin_search(0, base, base);
}

int main(int argc, char *argv[]) {
    printf("%.2lf\n", my_sqrt(10));
}