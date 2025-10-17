

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char*
copiar_path(char* path) { // otra opcion usar strdup(), pero prefiero hacerlo manual.
    char* copia_path = (char*)malloc(strlen(path + 1)* sizeof(char));
    for (long i = 0; i < strlen(path); i++) { // manipular este array.
        copia_path[i] = path[i];
    }
    return copia_path;
}


void
imprimir_largo(char* copia_path, char* separador) {
    char* end = NULL;
    char* token = strtok_r(copia_path, separador, &end); // inicializamos el primer token, se usa de referencia
    if (!token){
        fprintf(stderr, "no hay tokens\n");
        exit(EXIT_FAILURE);
    }
    char* mas_largo = token; // el primero es el mas largo en un principio
    long max_len = strlen(token);
    for (token = strtok_r(NULL, separador, &end); token; token = strtok_r(NULL, separador, &end) ) {
        //empieza en NULL porque ya tenias el primero de referencia, de ahi sigue hasta que no haya token
        int size_token = strlen(token);
        if (max_len < size_token) {
            max_len = size_token;
            mas_largo = token;
        }
    }
    printf("%s\n", mas_largo);
    
}



void
imprimir_corto(char* copia_path, char* separador) {
    char* end = NULL;
    char* token = strtok_r(copia_path, separador, &end); // inicializamos el primer token, se usa de referencia
    if (!token){
        fprintf(stderr, "no hay tokens\n");
        exit(EXIT_FAILURE);
    }
    char* mas_corto = token; // el primero es el mas corto en un principio
    long min_len = strlen(token);
    for (token = strtok_r(NULL, separador, &end); token; token = strtok_r(NULL, separador, &end) ) {
        //empieza en NULL porque ya tenias el primero de referencia, de ahi sigue hasta que no haya token
        if (min_len > strlen(token)) {
            min_len = strlen(token);
            mas_corto = token;
        }
    }
    printf("%s\n", mas_corto);
    
}



int
main (int argc, char *argv[])
{
    char* path = getenv("PATH");
    if (!path || *path == '\0') {
        fprintf(stderr, "error: PATH no definida o vacía\n");
        exit(EXIT_FAILURE);
    }
    char* separador = ":";
    char* copia_path = copiar_path(path); // memoria reservada

    if (argc == 2 && strcmp(argv[1], "-s") == 0) {
        imprimir_corto(copia_path, separador);
        free(copia_path);
        exit(EXIT_SUCCESS);
    } else if (argc == 1) {
        imprimir_largo(copia_path, separador);
        free(copia_path);
        exit(EXIT_SUCCESS);
    } else {
        fprintf(stderr, "usage: pathmlen [-s]\n");
        free(copia_path);
        exit(EXIT_FAILURE);
    }
}