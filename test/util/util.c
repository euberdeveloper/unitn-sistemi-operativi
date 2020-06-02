//
// Created by xeno on 29/05/20.
//

#include "util.h"


void *pthread_fd_shell_sender(void *args){
    char *string = (char*)args;

    int fd = open("/tmp/shell_analyzer", O_WRONLY);

    int string_size = (int)strlen(string);
    write(fd, &string_size, sizeof(int));
    write(fd, string, string_size);


    int code = mkfifo("/tmp/analyzer_shell", 0666);
    fd = open("/tmp/analyzer_shell", O_RDONLY);
    bool res;
    read(fd, &res, sizeof(int));
    if(res){
        printf("%s\n", ">> >> Command Executed with success");
    }else if(res == 2){
        printf("%s\n", ">> >> Transmissions Closed");
    }else{
        printf("%s\n", ">> >> Command Failed");
    }
    unlink("/tmp/analyzer_shell");
    return NULL;
}

void *pthread_fd_shell_receiver(void *args){
    int code = mkfifo("/tmp/shell_analyzer", 0666);

    //Open read end
    int fd = open("/tmp/shell_analyzer", O_RDONLY);
    puts("Listening Commands From Shell");

    bool EOT = false;
    int string_size;
    char *string;
    while(!EOT){
        read(fd, &string_size,sizeof(int));
        string = (char*)malloc(string_size*sizeof(char) +1);
        read(fd, string, string_size);
        string[string_size] = '\0';
        if(strcmp(string, "EOT") == 0){
            EOT = true;
            int res = 2;
            int tmp_fd = open("/tmp/analyzer_shell", O_WRONLY);
            write(tmp_fd, &res, sizeof(int));
        } else{
            //parse command
            bool res = true;// = command_execute(cmd_info cmd);
            int tmp_fd = open("/tmp/analyzer_shell", O_WRONLY);
            write(tmp_fd, &res, sizeof(int));
        }
    }
    unlink("/tmp/shell_analyzer");
}

void *pthread_fd_analyzer_receiver(void *args){
    pthread_arguments *data = args;
    int code = mkfifo(data->path, 0666);

    //Open read end
    int fd = open(data->path, O_RDONLY);
    puts("FIFO OPEN");

    int i, file_number;
    read(fd, &file_number, sizeof(int));
    printf("Dio bon ne devo stampare : %d\n", file_number);
    data_file *files = (data_file*) malloc((sizeof(*files) * file_number));

    int Len;
    for(i = 0; i < file_number; i++){
        if(i % 10000 == 0){
            printf("%d\n", i);
        }
        read(fd, &files[i].info.alpha_upper, sizeof(int));
        read(fd, &files[i].info.alpha_ower, sizeof(int));
        read(fd, &files[i].info.digit, sizeof(int));
        read(fd, &files[i].info.punct, sizeof(int));
        read(fd, &files[i].info.space, sizeof(int));
        read(fd, &files[i].info.other, sizeof(int));

        read(fd, &Len, sizeof(int));
        files[i].path = (char*)malloc(sizeof(char)*Len);
        read(fd, files[i].path, Len);					//Read string characters
        files[i].path[Len] = 0;						//Zero terminator

/*
        printf("Path : %s\n", files[i].path);
        printf("Alphas Upper : %d\n", files[i].info.alpha_upper);
        printf("Alphas Lower : %d\n", files[i].info.alpha_ower);
        printf("Digits : %d\n", files[i].info.digit);
        printf("Puncts : %d\n", files[i].info.punct);
        printf("Spaces : %d\n", files[i].info.space);
        printf("Others : %d\n\n", files[i].info.other);
        fflush(stdout);
        */
    }

    puts("EOF found");

    //Tidy up
    close(fd);
    puts("FIFO Closed");
    unlink("/tmp/protocol");


    return NULL;
}

