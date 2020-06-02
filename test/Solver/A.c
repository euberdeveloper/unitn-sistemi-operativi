
#include "../util/util.h"

int main(int argc, char *argv[]){
    int i, n = 3,m = 5;
    bool shell = false, rec = false;
    char **inputs;
    //parse_command(argc, argv, &n, &m, inputs, &shell, &rec);

    for(i = 0; i < argc; i++){
        if(strcmp(argv[i],"-shell") == 0){
            shell = true;
        }else if(strcmp(argv[i], "-n") == 0){
            n =atoi(argv[++i]);
        }else if(strcmp(argv[i], "-m") == 0){
            m = atoi(argv[++i]);
        }
    }
    if(shell){
        pthread_t shell_thread;
        pthread_create(&shell_thread,NULL, pthread_fd_shell_receiver, NULL);
        //pthread_join(shell_thread, NULL);
    }else{
        //integrated_shell
    }




    //parse_command
    return 0;
}