//Array invertido (Números)
//• Crea un programa que recibe varios números como argumentos.
//• Guarda los números en un array y luego los imprime en orden inverso.


#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[]) {
    int len = argc - 1;
    int *array_inv = (int *)malloc(len * sizeof(int)); // reserva memoria dinamica para el array invertido
    int *array = (int *)malloc(len * sizeof(int)); //reserva memoria dinamica para array de enteros
    int base = 10;
    char *end = NULL;
    if (argc == 0) {
        printf("por favor, proporciona argumentos\n");
        free(array_inv);
        free(array);
        exit(EXIT_FAILURE);
    }

    printf("array de argumentos: \n");
    for (int i = 1; i <= len; i++) {
        int num = strtol(argv[i], &end, base);

        if (end == argv[i] || *end != '\0') {
            printf("error, no es un string\n");
            free(array_inv);
            free(array);
            exit(EXIT_FAILURE);
        }
        array[i - 1] = num; // este array[i - 1] es porque si empezamos en la posicion 1 de argv, que es el primer argumento
        // hay que meterlo en la posicion 0 del array de los enteros, y asi sucesivamente.
        printf("%i  ", num);
        
    }
    printf("\n");
    printf("array de argumentos invertido: \n");
    for (int j = len - 1; j >= 0; --j) { //for decremental -> recorre de der a izq el array ordenado e inserta en el array invertido de izq a der
        array_inv[len - 1 - j] = array[j];
        printf("%i  ", array_inv[len - 1 -j]);
    }
    printf("\n");
    

    free(array);
    free(array_inv);
    exit(EXIT_SUCCESS);

}