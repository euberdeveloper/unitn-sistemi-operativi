#define _GNU_SOURCE
#include <stdio.h>
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include "R_functions.h"



const char* TEST_MESSAGE = "000000552 ciao.txt 23 23 23 23 23 23 come.txt 23 23 23 23 23 23";


int main(){
    int MSG_SIZE;
    int data_file_number;
    
    char* fifo = "/tmp/myfifo";
    char* BUFFER_SIZE = (char*) malloc(8 * sizeof(char));

    if(mkfifo(fifo, 0666) == -1){
        perror("errror in creating the fifo\n");
        if (errno == EEXIST){
            printf("The fifo \'%s\', already exists\n", fifo);
        }
    }
    int fd_fifo;
    fd_fifo = open(fifo, O_RDONLY);
    //F_SETPIPE_SZ();
    while(1){
        if(read(fd_fifo, BUFFER_SIZE, 8) != 8){
            sleep(20);
        } else {
            break;
        }
    }

    
    sscanf(BUFFER_SIZE, "%d", &MSG_SIZE);
    free(BUFFER_SIZE);
    printf("mgs size = %d\n", MSG_SIZE);
    fflush(stdout);
    char* msg = NULL;
    while (msg == NULL){
        msg = (char*) malloc (MSG_SIZE * sizeof(char) + 1);
    }
    //int read_so_far;

    while(1){
        if(read(fd_fifo, msg, MSG_SIZE) != MSG_SIZE){
            printf("read error!\n");
            
        } else {
            break;
        }
    }
   // printf("%s\n",msg);
    fflush(stdout);
    //read(fd_fifo, msg, MSG_SIZE);
    int N_FILES = 0;
    DATA_FILE* FILES = deserialize(msg, &N_FILES);
    //printf("%s",FILES[0].path);
    
    /*
    int i;
    for (i = 0; i < N_FILES; i++){
        print_file(&FILES[i],true, true);
        fflush(stdout);
        //printf("hey");
    }*/
    
    //int ret = sscanf(read(8), "%d", &N) -> number of variable readed;    
    // alloc N-DATA_FILE
    // FILL n-DATA_FILE
    close(fd_fifo);
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