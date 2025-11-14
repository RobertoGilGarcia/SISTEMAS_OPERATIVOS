//Decimal a hexadecimal
//• Crea un programa que reciba un número decimal y lo convierta a hexadecimal.
//• Ejemplo:
//./programa 255
//• La salida sería:
//FF


#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[]) {
    char *end = NULL;
    int base = 10;

    if (argc != 2) {
        printf("introduce un numero\n");
        exit(EXIT_FAILURE);
    }

    int num = strtol(argv[1] ,&end,base);

    if (end == argv[1]) {
        printf("introduce un numero decimal\n");
        exit(EXIT_FAILURE);
    }

    if (*end != '\0') {
        printf("no es un string\n");
        exit(EXIT_FAILURE);
    }
    printf("numero en hexadecimal: %X\n", num); // la clave es el %X -> hace que imprimas en hexadecimal y el X mayuscula hace que sea FF no ff
    exit(EXIT_SUCCESS);
}