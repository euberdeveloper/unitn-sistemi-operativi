#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int READ = 0;
const int WRITE = 1;
const int SIZE = 95;
const int N = 5;

void workSmarterNotHarder(const char* text, int fd[]);
char *substring(const char *string, int start,unsigned int length);
char *getText();


int main() {
    pid_t *pids = (pid_t*)malloc(sizeof(pid_t) * N);
    int  i, start, fd[N][2], data[N][SIZE], final[SIZE];
    memset(final, 0, sizeof(int)*SIZE);

//Pipes Setup
    for(i = 0; i < N; i++) {
        if (pipe(fd[i]) < 0) {
            perror("pipe error");
            exit(1);
        }
    }

// Getting the text
    char *text = getText();
    unsigned int substring_size;
    if((strlen(text) % N) == 0)
        substring_size = strlen(text) / N;
    else
        substring_size = (strlen(text) / N) +1;

// Start children.
    for (i = 0; i < N; ++i) {
        if ((pids[i] = fork()) < 0) {
            perror("fork");
            abort();
        } else if (pids[i] == 0) {
            start = i*substring_size;

            if(i == N - 1)
                workSmarterNotHarder(substring(text, start, strlen(text)-start), fd[i]);
            else
                workSmarterNotHarder(substring(text, start, substring_size), fd[i]);

            exit(0);
        }
    }

// Parent Reading Results
    for(i = 0; i < N; i++){
        close(fd[i][WRITE]);
        read(fd[i][READ], data[i], sizeof(int)*SIZE);
        int k;
        for( k = 0; k < SIZE; k++){
            final[k]+=data[i][k];
        }
        close(fd[i][READ]);
    }



    int nmaed_fd = open("/tmp/demo6_fifo", O_WRONLY);
    if (nmaed_fd ==  -1) {
        perror("Cannot open fifo");
        return EXIT_FAILURE;
    }
    write(nmaed_fd, final, sizeof(int)*SIZE);

    //Tidy
    close(nmaed_fd);

    return 0;
}

void workSmarterNotHarder(const char* text, int fd[2]){
    int i, *data = (int*)calloc(SIZE, sizeof(int));
    close(fd[READ]);
    for(i = 0; i < strlen(text); i++){
        data[(int)text[i]-32] += 1;
    }
    write(fd[WRITE], data, sizeof(int)*SIZE);
    close(fd[WRITE]);
}

char *getText(){
    char *text = (char*) malloc(sizeof(char)*100000);
    gets(text);
    return text;
}

char *substring(const char *string,const int start,unsigned const int length){
    char *substring = (char*) malloc(sizeof(char)*(length+1));int i;
    memcpy(substring,&string[start], length);
    substring[length] = '\0';
    return substring;
}