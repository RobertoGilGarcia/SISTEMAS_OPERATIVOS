#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

enum{
    MAX_LINE = 1024
};

void
usage(void){
    fprintf(stderr, "usage: maxtab file\n");
    exit(EXIT_FAILURE);
}

FILE *
open_file(char *file){
    FILE *open_file;
    open_file = fopen(file, "r");
    if (open_file == NULL) {
        fprintf(stderr, "error opening file: %s\n", file);
        exit(EXIT_FAILURE);
    }
    return open_file;
}


void
num_tabs(FILE *file) {
    int found_tabs = 0;
    int num_tabs_line;
    char line_readed[MAX_LINE];
    char *best_line = NULL;
    char *last_line = NULL;
    int top_tabs = -1;
    while (fgets(line_readed, MAX_LINE, file) != NULL) {
        free(last_line);
        last_line = strdup(line_readed);
        if (last_line == NULL) {
            fprintf(stderr,"strdup error\n");
            exit(EXIT_FAILURE);
        }
        num_tabs_line = 0;
        while (line_readed[num_tabs_line] == '\t'){
            num_tabs_line++;
        }
        if (num_tabs_line > 0 && num_tabs_line >= top_tabs) {
            top_tabs = num_tabs_line;
            found_tabs = 1;

            free(best_line);
            best_line = strdup(line_readed);
            if (best_line == NULL){
                fprintf(stderr, "error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    if (found_tabs && best_line != NULL) {
        printf("%d:%s",top_tabs, best_line);
    } else if (found_tabs == 0 && last_line != NULL) {
        printf("0:%s", last_line);
    }
    free(best_line);
    free(last_line);
}


int
main(int argc, char *argv[]){
    FILE *fd;
    argc--;
    argv++;
    if (argc == 0 || argc >= 2) {
        usage();
    }
    fd = open_file(argv[0]);
    //open
    num_tabs(fd);
    fclose(fd);
    //closed
    exit(EXIT_SUCCESS);
}