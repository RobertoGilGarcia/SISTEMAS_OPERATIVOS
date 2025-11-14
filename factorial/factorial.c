//Factorial
//• Crea un programa que reciba un número como argumento y calcule su factorial.
//• Ejemplo:
//./programa 5
//• La salida sería: 120


#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

int
factorial(int n) {
    if (n == 0) {
        return 1;
    }
    return n * factorial(n -1);
}

int
main (int argc, char *argv[]) {
    if (argc != 2) {
        printf("escribe un numero, por favor \n");
        exit(EXIT_FAILURE);
    }
    char *end = NULL;
    int base = 10;
    int num = strtol(argv[1], &end, base);
    int resultado = factorial(num);
    
    printf("%i\n", resultado);
    exit(EXIT_SUCCESS);
}   