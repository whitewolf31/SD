#include <stdio.h>
#include <math.h>

double to_power(double num, double power) {
    double prod = 1;
    while (power > 0) {
        prod *= num;
        power--;
    }
    return prod;
}

double bin_search(double left, double right, double value, double rank) {
    double mid = (left + right) / 2;
    double foundVal = to_power(mid, rank) - value;
    if (fabs(foundVal) < 0.001) return mid;
    else if (foundVal > 0) return bin_search(left, mid, value, rank);
    else return bin_search(mid, right, value, rank);
}

double my_sqrt(double base, double rank) {
    return bin_search(0, base, base, rank);
}

int main(int argc, char *argv[]) {
    printf("%.2lf\n", my_sqrt(10, 3));
}