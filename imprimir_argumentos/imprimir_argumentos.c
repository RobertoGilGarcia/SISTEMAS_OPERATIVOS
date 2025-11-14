//Imprimir argumentos
//• Crea un programa que imprima todos los argumentos que recibe:
//a) Cada argumento en una línea diferente.
//b) Todos los argumentos en una sola línea, separados por espacios.
//• Este ejercicio te enseña a recorrer el array argv.

#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char *argv[]) // -> hay que tener en cuenta que lo que le pasamos a main es, el numero de argumentos, y los argumentos
{
    int i = 1; // inicializamos el iterador del bucle para recorrer el array de argumentos a 1, el argumento 0 es el nombre del programa
    printf("Un argumento por linea: \n");
    for (i = 1; i < argc; i++) { //desde la posicion 1, si la posicion es < que la cantidad de argumentos, imprimimos y aumentamos uno al valor de i, en ese orden, en este caso con un salto de linea
        printf("Argumento %i: %s\n", i, argv[i]);
    }
    printf("Un argumento por palabra: \n");
    for (i = 1; i < argc; i++) { //igual que antes, pero ahora no imprimimos un salto de linea para imprimir todos los args en la misma linea
        printf("Argumento %i: %s    ", i, argv[i]);
    }
    printf("\n");
    exit(EXIT_SUCCESS); //acabamos con esta sentencia
}