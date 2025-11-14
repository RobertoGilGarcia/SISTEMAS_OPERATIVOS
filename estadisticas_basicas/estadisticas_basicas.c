//Estadísticas básicas
//• Escribe un programa que reciba varios números como argumentos.
//• El programa debe imprimir:
//• El número más grande.
//• El número más pequeño.
//• La mediana (el valor central cuando están ordenados, si el número de elementos es
// par, debe ser la media de los dos elementos centrales).

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void
ordenar_array(int arr[], int n) {
    int c, d, t;
    for (c = 0; c < n; c++) {
        for (d=0; d < n - c -1; d++) {
            if (arr[d] > arr[d + 1]) {
                t = arr[d];
                arr[d] = arr[d + 1];
                arr[d + 1] = t;
                }
            }
        }
    }


int
main(int argc, char *argv[]) {
    int num;
    int len = argc - 1;
    char *end = NULL; //puntero a char para declarar el final del string de argumentos 
    int base_10 = 10; // base para convertir a base 10 los chars a integers
    int max;
    int min;
    int mediana;


    if (argc == 1) {
        printf("por favor, introduzca numeros\n");
        exit(EXIT_FAILURE);
    }
    
    int *array = (int *)malloc((len) * sizeof(int)); //declaracion del array de [4 bytes, 4 bytes, ....] -> tamaño argc - 1
    for (int i = 1; i < argc; i++) {
        num = strtol(argv[i], &end, base_10); //convertir los chars del vector de argumentos a int

        if (end == argv[i]) {
            printf("mete solo numeros\n");
            free(array);
            exit(EXIT_FAILURE);
        }

        if (*end != '\0') {
            printf("no es un string");
            exit(EXIT_FAILURE);
        }
        array[i - 1] = num;

        
    }

    
    
    max = array[0];
    min = array[0];
    mediana = array[0];

    ordenar_array(array, len);

    for (int i = 0; i < argc - 1; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }

    for (int j = 0; j < argc - 1; j++ ) {
        if (array[j] < min) {
            min = array[j];
        }
    }

    if (len % 2 != 0) {
        mediana = array[len/2];
    } else {
        mediana = (array[len/2] + array[len/2 - 1]) / 2;
    }

    printf("el numero mayor es: %i\n", max);
    printf("el numero menor es: %i\n", min);
    printf("el valor de la mediana es: %i\n", mediana);

    free(array);
    exit(EXIT_SUCCESS);
}