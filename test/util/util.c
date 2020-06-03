//
// Created by xeno on 29/05/20.
//

#include "util.h"

//Utility functions
void parse_arguments(int argc, char* argv[],int *n, int *m, data_inputs *input, bool *shell, bool *rec){
    int i;
    for(i = 0; i < argc; ++i){
        if(!strcmp(argv[i],"-shell")){
            *shell = true;
        }else if(!strcmp(argv[i], "-rec")) {
            *rec = true;
        }else if(!strcmp(argv[i], "-n")){
            *n = atoi(argv[++i]);
        }else if(!strcmp(argv[i], "-m")){
            *m = atoi(argv[++i]);
        }else if(!strcmp(argv[i], "-i")){
            input->size = argc - (++i);
            input->inputs = (char **)malloc(sizeof(char*)*input->size);
            int index = 0;
            while(i < argc && argv[i][0] != '-'){
                input->inputs[index] = (char*)malloc(strlen(argv[i]));
                input->inputs[index] = argv[i];
                ++index;    ++i;
            }
            --i;
            if(index < input->size){
                input->inputs = (char **)realloc(input->inputs, index+1);
                input->size = index;
            }
        }
    }
}
void print_parsed_arguments(int *n, int *m, data_inputs *input, bool *shell, bool *rec){
    int i;
    printf("N : %d\n", *n);
    printf("M : %d\n", *m);
    printf("S : %d\n", *shell);
    printf("R : %d\n", *rec);
    printf("%s","File/s : \n");
    for(i = 0; i < input->size; i++){
        printf("\t>%s\n",input->inputs[i]);
    }
    printf("\n");
}
void print_files_data(pthread_analyzer_arguments *arg){
    int i;
    for(i  = 0; i < arg->files_number; ++i){
        printf("Filename : %s\n", arg->files[i].path);
        printf("Upper : %d\n", arg->files[i].info.alpha_upper);
        printf("Lower : %d\n", arg->files[i].info.alpha_lower);
        printf("Digit : %d\n", arg->files[i].info.digit);
        printf("Punct : %d\n", arg->files[i].info.punct);
        printf("Space : %d\n", arg->files[i].info.space);
        printf("Other : %d\n\n", arg->files[i].info.other);
    }
}
char *to_string(int number){
    int n = number, count = 0;
    while (n != 0) {
        n /= 10;
        ++count;
    }
    char *string = (char*)malloc(count+1);
    sprintf(string, "%d", number);
    return string;
}
char* concat(const char *s1, const char *s2){
    char *res = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(res, s1);
    strcat(res, s2);
    return res;
}

//Process Functions
char **create_execv_args(int n, int m, data_inputs input){
    int i = 0, size = input.size + 2 + ((m>0)? 2 : 0);
    char **execv_args = (char**) malloc(sizeof(char*)*size);
    execv_args[i] = (char*) malloc(2); execv_args[i] = "-n";
    execv_args[++i] = (char*) malloc(strlen(to_string(n))); execv_args[i] = to_string(n);

    if(m > 0){
        execv_args[++i] = (char*) malloc(2); execv_args[i] = "-m";
        execv_args[++i] = (char*) malloc(strlen(to_string(m))); execv_args[i] = to_string(m);
    }

    int k;
    execv_args[++i] = (char*) malloc(2); execv_args[i] = "-i";
    for(k = 0; k < input.size; k++){
        execv_args[++i] = (char*) malloc( strlen(input.inputs[k]));
        execv_args[i] = input.inputs[k];
    }

    return execv_args;
}

data_process *create_process(int n, int m, data_inputs input, char *child){
    data_process *res = (data_process *)malloc(sizeof(res) * n);
    //Divide Inputs
    data_inputs *divided_data; // = divide_input(n, input);
    int i;

    for (i = 0; i < n; ++i) {
        if((res[i].pid = fork()) == -1){
            printf("Fork Failed");
        }else if (!res[i].pid){
            char **execv_args = create_execv_args(i, m, input);
            execv(concat(".", child), execv_args);
            exit(0);
        }else{
            res[i].arg = (pthread_analyzer_arguments*) malloc(sizeof(pthread_analyzer_arguments));
            res[i].arg->path = concat(concat("/tmp", child), to_string(i));
            pthread_create(&(res->thread_r), NULL, pthread_fd_analyzer_receiver, (void*)res[i].arg);
        }
    }
    return res;
}


//Pthread for fifo data exchanges
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
    return NULL;
}
void *pthread_fd_analyzer_sender(void *args){
    pthread_analyzer_arguments *data = args;

    int fd = open(data->path, O_WRONLY);
    int L= 1, cos = 23; char mode = 'D';

    write(fd, &mode, sizeof(char));
    write(fd, &L, sizeof(int));
    write(fd, &cos, sizeof(int));
    write(fd, &cos, sizeof(int));
    write(fd, &cos, sizeof(int));
    write(fd, &cos, sizeof(int));
    write(fd, &cos, sizeof(int));
    write(fd, &cos, sizeof(int));
    char *text = "ciao"; L = 4;
    write(fd, &L, sizeof(int));
    write(fd, text, L);

    mode = 'E';
    write(fd, &mode, sizeof(char));

    return NULL;
}
void *pthread_fd_analyzer_receiver(void *args){
    pthread_analyzer_arguments *data = args;
    bool cycle = true; char mode;
    int i, files_number, code = mkfifo(data->path, 0666);

    //Open read end
    int fd = open(data->path, O_RDONLY);

    while (cycle){
        read(fd, &mode, sizeof(char));
        switch (mode) {
            case 'D':
                read(fd, &files_number, sizeof(int));
                printf("Dio bon ne devo creare : %d\n", files_number);
                data_file *files = (data_file*) malloc((sizeof(*files) * files_number));

                int Len;
                for(i = 0; i < files_number; ++i){
                    if(i % 10000 == 0){
                        if(files_number > 100000)
                            printf("Received %d files\n", i);
                    }
                    read(fd, &files[i].info.alpha_upper, sizeof(int));
                    read(fd, &files[i].info.alpha_lower, sizeof(int));
                    read(fd, &files[i].info.digit, sizeof(int));
                    read(fd, &files[i].info.punct, sizeof(int));
                    read(fd, &files[i].info.space, sizeof(int));
                    read(fd, &files[i].info.other, sizeof(int));

                    read(fd, &Len, sizeof(int));
                    files[i].path = (char*)malloc(Len + 1);
                    read(fd, files[i].path, Len);					//Read string characters
                    files[i].path[Len] = 0;						//Zero terminator
                }
                data->files_number = files_number;
                data->files = files;
                break;
            case 'B':

                break;
            case 'E':
                cycle = false;
                puts("EOT found\n");
                break;
        }
    }

    //Tidy up
    close(fd);
    unlink(data->path);

    return NULL;
}

