//Par o impar
//• Crea un programa que reciba un número como argumento y determine si es par o impar.
//• El programa debe imprimir un mensaje indicando el resultado.

#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("error, debe proporcionar un solo numero.\n");
        exit(EXIT_FAILURE);
    }
    if (*argv[1] % 2 == 0) {
        printf("el numero es par\n");
        exit(EXIT_SUCCESS);
    } else {
        printf("el numero es impar\n");
        exit(EXIT_SUCCESS);
    }
    
}