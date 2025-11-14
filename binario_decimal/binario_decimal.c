//Binario a decimal
//• Escribe un programa que reciba un número en binario (como cadena) y lo convierta a
//decimal.
//• Ejemplo:
//./programa 1110
//• La salida sería:
//14


#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[]) {
    int base = 2;
    char *end = NULL;
    if (argc != 2) {
        printf("por favor, introduce un numero binario\n");
        exit(EXIT_FAILURE);
    }

    int num_binario = strtol(argv[1],&end , base);
    if (end == argv[1]) {
        printf("introduce un numero binario\n");
        exit(EXIT_FAILURE);
    }

    if (*end != '\0') {
        printf("no es un string\n");
        exit(EXIT_FAILURE);
    }
    printf("numero decimal: %i\n", num_binario); // -> no hace falta transformarlo, printf lo imprime en decimal.
    exit(EXIT_SUCCESS);
}