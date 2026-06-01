#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <string.h>


enum{
    MAX_LINE = 1024
};

void
usage(void) {
    fprintf(stderr, "usage: pspid [pid]\n");
    exit(EXIT_FAILURE);
}

int
check_pid (char *str){
    int base = 10;
    char *end = NULL;
    int num = strtol (str, &end, base);
    if (*end != '\0' || end == str || num <= 0){
      usage();
    }
    return num;
}

int
pid_to_int (char *str){
    int base = 10;
    char *end = NULL;
    int num = strtol (str, &end, base);
    if (*end != '\0' || end == str || num <= 0){
      return -1;
    }
    return num;
}


int
getpidtoken(char line[]){
    char *pid = NULL;
    char *end = NULL;
    int curr = 0;
    char *token = strtok_r(line, " ", &end);
    if (token != NULL && strcmp(token, "USER") == 0){
        return -1;
    }
    while (token != NULL) {
        curr++;
        //fprintf(stderr, "[DEBUG] col=%d token='%s'\n", curr, token);
        if (curr == 2) {
            pid = token;
            break;
        }
        token = strtok_r(NULL, " \t", &end);
    }
    if (pid == NULL) {
        return -1;
    }
    return pid_to_int(pid);
}



int
myhelper(int *pipe, int pid){
    char line[MAX_LINE];
    FILE *fdread;
    close(pipe[1]);
    int pid_line = 0;
    fdread = fdopen(pipe[0], "r");
    if (fdread == NULL){
        err(EXIT_FAILURE, "reading error\n");
    }
    while (fgets(line, MAX_LINE, fdread) != NULL) {
        pid_line = getpidtoken(line);
        if (pid_line == -1){
            continue;
        }
        if (pid_line == pid) {
            fclose(fdread);
            exit(EXIT_SUCCESS);
        }
    }
    fclose(fdread);
    exit(EXIT_FAILURE);
}

void
mypsaux(int *pipe, pid_t pid){
    close(pipe[0]);
    if (dup2(pipe[1], STDOUT_FILENO) < 0){
        err(EXIT_FAILURE, "dup2 error\n");
    }
    close(pipe[1]);
    execl("/bin/ps", "mypsaux", "aux", NULL);
    err(EXIT_FAILURE, "execl failed\n");
}



int
main(int argc, char *argv[]){
    argc--;
    argv++;
    int pid;
    pid_t pid_psaux;
    pid_t helper_pid;
    int fd[2];
    int ps_pid_status;
    int helper_status = EXIT_FAILURE;
    if (argc == 0) {
        usage();
    }
    pid = check_pid(argv[0]);

    if (pipe(fd) < 0) {
        err(EXIT_FAILURE, "can't make a pipe\n");
    }
    pid_psaux = fork();
    if (pid_psaux == -1 ){
        err(EXIT_FAILURE, "fork error \n");
    }
    if (pid_psaux == 0){
        mypsaux(fd, pid);
    }
    helper_pid = fork();
    
    if (helper_pid == -1){
        err(EXIT_FAILURE, "fork error\n");
    }
    if (helper_pid == 0) {
        myhelper(fd, pid);
    }
    close(fd[0]);
    close(fd[1]);

    if (waitpid(pid_psaux, &ps_pid_status, 0) < 0) {
        err(EXIT_FAILURE, "waitpid pspid failed\n");
    }
    if (waitpid(helper_pid, &helper_status, 0) < 0) {
        err(EXIT_FAILURE, "waitpid helper failed\n");
    }
    if (WIFEXITED(helper_status) && WEXITSTATUS(helper_status) == 0) {
        exit(EXIT_SUCCESS);
    } else {
        exit(EXIT_FAILURE);
    }
}