#include "util/util.h"


int main(){
    char cmd[80];
    bool end = false;
    while(!end){
        printf(">> ");
        scanf("%79s",cmd);
        if (strcmp(cmd,"exit") == 0){
            end = true;
        }else{
            pthread_t analyzer;
            pthread_create(&analyzer, NULL, pthread_fd_shell_sender, (void*)&cmd);
            pthread_join(analyzer, NULL);
        }
        printf("\n");
    }

}