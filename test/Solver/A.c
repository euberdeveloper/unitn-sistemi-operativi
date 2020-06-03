#include "../util/util.h"

int main(int argc, char *argv[]){
    int i, n = 12,m = 5;
    bool shell = false, rec = false;
    data_inputs input;

    parse_arguments(argc, argv, &n, &m, &input, &shell, &rec);
    print_parsed_arguments(&n, &m, &input, &shell, &rec);

    if(shell){
        pthread_t shell_thread;
        pthread_create(&shell_thread,NULL, pthread_fd_shell_receiver, NULL);
    }else{
        //integrated_shell();
    }

    //Input_Fix (Folder Search)

    data_process *process = create_process(n, m, input, "/P");

    while(wait(NULL) > 0) //Waits for children
        ;

    print_files_data(process[0].arg);

    return 0;
}