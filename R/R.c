#include <stdio.h>
#include <stdbool.h>
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>

typedef struct{
    int alpha_upper;
    int alpha_over;
    int digit;
    int punct;
    int space;
    int other;
}DATA_INFO;

typedef struct{
    char* path;
    DATA_INFO data_info;
}DATA_FILE;



const char* TEST_MESSAGE = "000000552 ciao.txt 23 23 23 23 23 23 come.txt 23 23 23 23 23 23";


int main(){
    int MSG_SIZE;
    int data_file_number;
    
    char* fifo = "/tmp/myfifo";
    char* BUFFER_SIZE = (char) malloc(8 * sizeof(char));

    if(mkfifo(fifo, 0666) == -1){
        perror("errror in creating the fifo\n");
        if (errno == EEXIST){
            printf("The fifo \'%s\', already exists\n", fifo);
        }
    }
    int fd_fifo;
    fd_fifo = open(fifo, O_RDONLY);
    
    read(fd_fifo, BUFFER_SIZE, 8);
    sscanf(BUFFER_SIZE, "%d", &MSG_SIZE);
    free(BUFFER_SIZE);

    char* msg = NULL;
    while (msg == NULL){
        msg = (char) malloc (MSG_SIZE * sizeof(char));
    }
    //int read_so_far;
    read(fd_fifo, msg, MSG_SIZE);
    int N_FILES = 0;
    DATA_FILE* FILES = deserialize(msg, &N_FILES);
    
    //int ret = sscanf(read(8), "%d", &N) -> number of variable readed;    
    // alloc N-DATA_FILE
    // FILL n-DATA_FILE
    return 0;
}




/*
    bool a;
    int temp;
    scanf("%d", &temp);
    a = temp;
    if(a){
        printf("true");
    } else {
        printf("false");
    } */