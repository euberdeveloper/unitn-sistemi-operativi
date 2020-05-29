#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const int READ = 0;
const int WRITE = 1;
const int SIZE = 95;
const int M = 5;
const int N = 3;

void GrandsonJob(char* text, int fd[2]);
void SonJob(char* text, int fd[2]);
char *strcut(const char *string,unsigned int start,unsigned int length);
char *getText();

int main() {
    pid_t son;
    int i, k, fd[N][2], data[N][SIZE], *final = (int*)calloc(SIZE, sizeof(int));
    unsigned int substring_size, start;


    char *text = getText(), *substring;//Temporary obtaining text from stdin and substrings creations

    //Calculating substring size based on number of M
    if((strlen(text) % N) == 0)
        substring_size = strlen(text) / N;
    else
        substring_size = (strlen(text) / N) + 1;


    //Creating N pipes for comunication
    for(i = 0; i < N; i++) {
        if (pipe(fd[i]) < 0) {
            perror("Pipe error");
            exit(1);
        }
    }

    //Sons generation
    for(i = 0; i < N; i++) {
        if ((son = fork()) < 0) {
            perror("Fork P");
            abort();
        } else if (son == 0) {
            start = i * substring_size;//Calculating index of start of substring

            //"Good" creation of substring
            if(i == N-1)
                substring = strcut(text,start, strlen(text) - start);
            else
                substring = strcut(text, start, substring_size);


            SonJob(substring, fd[i]);
            exit(0);
        }
    }

    //Receiving data form sons
    for(i = 0; i < N; i++) {
        close(fd[i][WRITE]);
        read(fd[i][READ], data[i],sizeof(int)*SIZE);
        close(fd[i][READ]);

        for(k = 0; k < SIZE; k++)
            final[k]+=data[i][k];
    }

    //Sending data to report creator
    int named_fd = open("/tmp/demo6_fifo", O_WRONLY);
    if (named_fd == -1) {
        perror("Cannot open fifo");
        return EXIT_FAILURE;
    }
    write(named_fd, final, sizeof(int) * SIZE);

    //Tidy
    close(named_fd);

    //Showing Analyzed data
    for(i = 0; i < SIZE; i++)
        printf("%C : %d\n", (char)i+32, final[i]);

    return 0;
}

void SonJob(char* text, int fd[2]){
    pid_t son;
    int i, k, son_fd[M][2], data[M][SIZE], *final=(int*)calloc(SIZE, sizeof(int));
    char *substring;
    unsigned int substring_size, start;

    //Calculating substring size based on number of M
    if((strlen(text) % M) == 0)
        substring_size = strlen(text) / M;
    else
        substring_size = (strlen(text) / M) + 1;

    //Creating M pipes for comunication
    for(i = 0; i < M; i++) {
        if (pipe(son_fd[i]) < 0) {
            perror("Pipe error");
            exit(1);
        }
    }

    //Grandsons generation
    for(i = 0; i < M; i++) {
        if ((son = fork()) < 0) {
            perror("Fork P");
            abort();
        } else if (son == 0) {
            start = i * substring_size;

            if(i == N-1)
                substring = strcut(text,start, strlen(text) - start);
            else
                substring = strcut(text, start, substring_size);

            GrandsonJob(substring, son_fd[i]);
            exit(0);
        }
    }

    for(i = 0; i < M; i++) {
        close(son_fd[i][WRITE]);
        read(son_fd[i][READ], data[i],sizeof(int)*SIZE);
        close(son_fd[i][READ]);
        for(k = 0; k < SIZE; k++)
            final[k]+=data[i][k];
    }

    close(fd[READ]);
    write(fd[WRITE], final, sizeof(int)*SIZE);
    close(fd[WRITE]);
}

void GrandsonJob(char* text, int fd[2]){
    int i, *data=(int*)calloc(SIZE, sizeof(int));

    for(i = 0; i < strlen(text); i++)
        data[text[i]-32]++;

    close(fd[READ]);
    write(fd[WRITE], data, sizeof(int) * SIZE);
    close(fd[WRITE]);
}

char *getText(){
    char *text = (char*) malloc(sizeof(char)*100000);
    gets(text);
    return text;
}

char *strcut(const char *string,unsigned const int start,unsigned const int length){
    char *substring = (char*) malloc(sizeof(char)*(length+1));

    memcpy(substring,&string[start], length);
    substring[length] = '\0';

    return substring;
}