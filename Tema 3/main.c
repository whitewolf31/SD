#include "tema3.h"

int main(int argc, char *argv[]) {
    FILE *in = fopen(argv[2], "r");
    FILE *out = fopen(argv[3], "w");
    if (strcmp(argv[1], "-c1") == 0) {
        main_cerinta1(in, out);
    } else if (strcmp(argv[1], "-c2") == 0) {
        main_cerinta2(in, out);
    } else {
        main_cerinta3(in, out);
    }
    fclose(in);
    fclose(out);
    return 0;
}