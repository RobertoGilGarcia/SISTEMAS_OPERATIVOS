#include <stdlib.h>
#include <stdio.h>
#include <string.h>


char*
truncar(char* str, int trunque) {
    char* str_truncado = str;
    if (trunque > strlen(str)) {
        str_truncado = str;
    }
    str_truncado[trunque] = '\0';
    return str_truncado;
}

char*
rev_truncar(char* str) {
    int inicio = 0;
    int final = strlen(str) - 1;
    char* str_rev = str;

    while (inicio < final) {
        char temp = str[inicio];
        str[inicio] = str[final];
        str[final] = temp;
        inicio++;
        final--;
    }
    return str_rev;
}

void
imprimir_n_trunc(char* str, int n, int trunque){
    int i;
    char* trunc = truncar(str, 5);
    for (i = 1; i <= n; i++){
        printf("%s", trunc);
    }
    printf("\n");
}

void
imprimir_n_trunc_rev(char* str, int n, int trunque){
    int i;
    char* trunc = truncar(str, 5);
    char* trunc_rev = rev_truncar(trunc);
    for (i = 1; i <= n; i++){
        printf("%s", trunc_rev);
    }
    printf("\n");
}


int
main(int argc, char* argv[]){
    argc -= 1;
    argv += 1;
    int base_10 = 10;
    char* end;
    int n;
    int i;


    if (strcmp(argv[0], "-r") == 0) {
        n = strtol(argv[1], &end, base_10);
        if (n == '\0' || *end == n) {
            fprintf(stderr, "ERROR\n");
            exit(EXIT_FAILURE);
        }
        if (n < 0) {
            fprintf(stderr, "n no puede ser negativo \n");
            exit(EXIT_FAILURE);
        }
        for (i = 2; i < argc; i++){
            imprimir_n_trunc_rev(argv[i], n, 5);
            
        }
    } else {
        n = strtol(argv[0], &end, base_10);
        if (n == '\0' || *end == n) {
            fprintf(stderr, "ERROR\n");
            exit(EXIT_FAILURE);
        }
        if (n < 0) {
            fprintf(stderr, "n no puede ser negativo \n");
            exit(EXIT_FAILURE);
        }
        for (i = 1; i < argc; i++){
            imprimir_n_trunc(argv[i], n, 5);
        }
    }
    exit(EXIT_SUCCESS);
}