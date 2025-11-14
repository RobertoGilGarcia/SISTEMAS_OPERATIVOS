#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <err.h>
enum {
    MAX_FICHS = 1000
};
int
usage(){
    fprintf(stderr, "usage: mysplit N file\n");
    exit(EXIT_FAILURE);
}

int
take_bytes(char *str) {
    char *end = NULL;
    int base = 10;
    int num = strtol(str,&end,base);
    if (num <= 0 || end == str || *end != '\0'){
        fprintf(stderr, "usage: mysplit N file\n");
        exit(EXIT_FAILURE);
    }
    return num;
}

int
read_file(int fd, char *buf, int len_buf, int *end) {
    int dev = 0;
    int total = 0;
    while(total < len_buf) {
        dev = read(fd, buf + total, len_buf - total);
        if (dev < 0) {
            err(EXIT_FAILURE, "reading error\n");
        }
        if (dev == 0) {
            *end = 0;
            break;
        }
        total += dev;
    }
    return total;
}

int
write_file(int fd, char *buff, int len_buf) {
    int dev = 0;
    int total = 0;
    while(total < len_buf){
        dev = write(fd, buff + total, len_buf - total);
        if (dev < 0 ) {
            err(EXIT_FAILURE, "writing error\n");
        }
        total += dev;
    }
    return total;
}

int
main(int argc, char *argv[]) {
    argc--;
    argv++;
    int n_bytes;
    int fd;
    int n_bytes_readed;
    char *buf;
    char *name_subfile;
    int len_name_subfile;
    int count = 0;
    int end = 1;
    int sub_file;
    if (argc < 2) {
        usage();
    }
    len_name_subfile = 4 + strlen(argv[1]);
    name_subfile = (char *) malloc(len_name_subfile);
    if (name_subfile == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(EXIT_FAILURE);
    }
    n_bytes = take_bytes(argv[0]);
    buf = (char *)malloc (n_bytes*sizeof(char));
    if (buf == NULL) {
        fprintf(stderr, "malloc error\n");
        free(name_subfile);
        exit(EXIT_FAILURE);
    }
    fd = open(argv[1], O_RDONLY, 0664);
    if (fd < 0) {
        usage();
    }
    while (1) {
        if (count == MAX_FICHS) {
            fprintf(stderr, "MAX files created\n");
            free(buf);
            free(name_subfile);
            exit(EXIT_FAILURE);
        }
        n_bytes_readed = read_file(fd, buf, n_bytes, &end);
        snprintf(name_subfile, len_name_subfile, "%03d%s",count , argv[1]); //NOMBRE SUBFICHERO
        sub_file = open(name_subfile, O_RDWR | O_CREAT | O_TRUNC, 0664);
        if (sub_file < 0) {
            fprintf(stderr, "error opening file: %d\n", sub_file);
            exit(EXIT_FAILURE);
        }
        write_file(sub_file, buf, n_bytes_readed);
        close(sub_file);
        memset(buf, 0, n_bytes);
        memset(name_subfile, 0, len_name_subfile);
        if (end == 0) {
            break;
        }
        count++;
    }
    close(fd);
    free(buf);
    free(name_subfile);
    exit(EXIT_SUCCESS);
}