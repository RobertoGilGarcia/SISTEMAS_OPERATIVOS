//Hexadecimal a decimal
//• Escribe un programa que reciba un número en hexadecimal y lo convierta a decimal.
//• Ejemplo:
//./programa FF
//• La salida sería:
//255

#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[]) {
    char *end = NULL;
    int base = 16;
    if (argc != 2) {
        printf("introduce un numero hexadecimal\n");
        exit(EXIT_FAILURE);
    }

    int num = strtol(argv[1], &end, base);
    if (end == argv[1] || *end != '\0' ) {
        printf("error, no es un string\n");
        exit(EXIT_FAILURE);
    }
    printf("numero en decimal: %i\n", num);
    exit(EXIT_SUCCESS);
}