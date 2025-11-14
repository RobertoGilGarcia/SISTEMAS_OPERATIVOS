#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int
main(int argc, char* argv[]){
    argc -= 1;
    argv += 1;
    char* end = NULL;
    char* separador = ":";
    int i;
    char* copia;
    char* token = NULL;
    char* var_entorno = NULL;

    for (i = 0; i < argc; i++) {
        var_entorno = getenv(argv[i]);
        if (var_entorno == NULL) {
            fprintf(stderr, "variable nula\n");
            exit(EXIT_FAILURE);
        }
        copia = strdup(var_entorno);
        if (copia == NULL) {
            fprintf(stderr, "error del maloc\n");
            exit(EXIT_FAILURE);
        }
        token = strtok_r(copia, separador, &end);
        while(token != NULL) {
            printf("%s\n", token);
            token = strtok_r(NULL, separador, &end);
        }
    }
    exit(EXIT_SUCCESS);
}