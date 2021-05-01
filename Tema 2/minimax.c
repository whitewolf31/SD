#include <string.h>

#include "cerinte.h"

int main(int argc, char *argv[]) {
    // Se verifica care cerinta este
    if (strcmp(argv[1], "-c1") == 0){
        main_cerinta1(argc, argv);
    } 
    if (strcmp(argv[1], "-c2") == 0) {
        main_cerinta2(argc, argv);
    }
    if (strcmp(argv[1], "-c3") == 0) {
        main_cerinta3(argc, argv);
    } 
    return 0;
}