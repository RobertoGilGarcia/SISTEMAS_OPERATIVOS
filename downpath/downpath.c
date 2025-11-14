#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>


char*
string_toupper(char* str){
    int i;
    for (i = 0; i < strlen(str); i++){
        str[i] = toupper(str[i]);
    }
    return str;
}

int
main (int argc, char *argv[]) {
    char* home = getenv("HOME");
    char* user = getenv("USER");
    pid_t pid = getpid();

    printf("%s/Downloads/%s.%i\n", home, string_toupper(user), pid);
    exit(EXIT_SUCCESS);
}