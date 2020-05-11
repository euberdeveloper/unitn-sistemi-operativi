#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "./analyser/analyser.h"

int main() {
    int fd[2];
    int pipe_result = pipe(fd);

    if (pipe_result == -1) {
        printf("Errore nel pipe");
        exit(1);
    }

    int pid_child = fork();
    if (pid_child == -1) {
        printf("Errore nel forking\n");
        exit(1);
    }
    else if (pid_child == 0) {
        printf("Ich bin der Vater von Jamie, %d\n", getpid());
        close(fd[0]);

        const char *str = "Sondermeldung";
        write(fd[1], str, (strlen(str) + 1));
    }
    else {
        printf("Ich bin Jamie, der Sohn Dart Feners, %d\n", getpid());
        close(fd[1]);

        char buffer[90];
        read(fd[0], buffer, sizeof(buffer));
        printf("Received string: %s\n", buffer);
    }
    

    return 0;
}