//
// Created by xeno on 08/06/20.
//
#include "process.h"
#include <pthread.h>
// A che crea c
void what_c_does(int p_number, int q_number, files_array *files, int **fd);
process create_c(int p_number, int q_number, files_array *files){
    process res;

    res.fd = create_pipes(2);

    if((res.pid = fork()) < 0){
        fprintf(stderr, "fork error");
    }else if(res.pid == 0){
        close(res.fd[FW_CR][WRITE_END]);
        close(res.fd[CW_FR][READ_END]);
        what_c_does(p_number, q_number, files, res.fd);
    }else{
        close(res.fd[FW_CR][READ_END]);
        close(res.fd[CW_FR][WRITE_END]);
    }

    return res;
}

// C che crea i p
void what_p_does(int index, int q_number, char *path, int paths_number, int **fd);
process_p_list create_p(int p_number, int q_number, files_array *files, int files_size, int **f_fds){
    process_p_list res;

    receiver_args_c *args = (receiver_args_c*) malloc(sizeof(receiver_args_c) * p_number);

    res.process_list = (process*) malloc(sizeof(process) * p_number);
    res.p_number = p_number;
    res.q_number = q_number;
    p_input *p_inputs = get_P_input(files->files, files_size, p_number);
    data_file **c_res = (data_file**)malloc(sizeof(data_file*) * p_number);

    /*int k;

    for(k = 0; k < p_number; k++){
        int j;
        printf("P: %d\n", k);
        for(j = 0; j < p_inputs[k].path_size; j++){
            printf("Path %d :%s\n",j, p_inputs[k].paths[j]);
        }
        printf("\n");
    }printf("\n\n\n");*/

    int i;


    for(i = 0; i < p_number; i++){
        res.process_list[i].fd = create_pipes(2);
        res.process_list[i].index = i;
        c_res[i] = (data_file *) malloc(sizeof(data_file) * p_inputs[i].path_size);

        args[i].index = i;
        args[i].f_fds = f_fds;
        args[i].c_fds = res.process_list[i].fd;
        args[i].p_input = p_inputs[i];
        args[i].p = c_res[i];

        /*int k;
        for(k = 0; k < args[i].p_input->path_size; k++){
            printf("Path: %s\n\n", args[i].p_input->paths[k]);
        }*/

        if((res.process_list[i].pid = fork()) < 0){
            fprintf(stderr, "fork error");
        }else if(res.process_list[i].pid == 0){
            close(res.process_list[i].fd[FW_CR][WRITE_END]);
            close(res.process_list[i].fd[CW_FR][READ_END]);

            what_p_does(i, q_number, args[i].p_input.paths[0], args[i].p_input.path_size, res.process_list[i].fd);

        }else{
            close(res.process_list[i].fd[FW_CR][READ_END]);
            close(res.process_list[i].fd[CW_FR][WRITE_END]);

            pthread_create(&res.process_list[i].thread_r, NULL, receiver_c, (void*)&args[i]);
        }
    }

    for(i = 0; i < p_number; i++){
        pthread_join(res.process_list[i].thread_r, NULL);
    }

    for(i = 0; i < p_number; i++){
        int j;
        for(j = 0; j < p_inputs[i].path_size; j++){
            int k;
            for(k = 0; k < files_size; k++){
                if(!strcmp(c_res[i][j].path, files->files[k].path)){
                    files->files[k].data_info = c_res[i][j].data_info;
                }
            }

        }
    }



    //show_vect(final);printf("\n\n");

    /*for(i = 0; i < p_number; i++){
        //close(res.process_list[i].fd[CW_FR][READ_END]);
        //close(res.process_list[i].fd[FW_CR][WRITE_END]);
        kill(res.process_list[i].pid, SIGKILL);
    }*/

    cm_schiken(files->files, files->size);

    return res;
}

// P che crea i q
void what_q_does(int father, int index, char *path, range range, int **fd);
process_q_list create_q(int father, int q_number, char *path, int paths_number, int **f_fds){
    process_q_list res;
    receiver_args_p *args = (receiver_args_p*) malloc(sizeof(receiver_args_p) * q_number);
    res.process_list = (process *) malloc(sizeof(process) * q_number);

    unsigned long long **q_res = (unsigned long long **) malloc(sizeof(data_file*) *q_number);

    res.q_number = q_number;
    range *ranges = get_ranges_from_size(path, q_number);

    int i;
    for(i = 0; i < q_number; i++){
        res.process_list[i].fd = create_pipes(2);
        res.process_list[i].index = i;

        q_res[i] = (unsigned long long*) malloc(sizeof(data_file) * 6);

        args[i].index = i;
        args[i].f_fds = f_fds;
        args[i].c_fds = res.process_list[i].fd;
        args[i].p = q_res[i];

        if((res.process_list[i].pid = fork()) < 0){
            fprintf(stderr, "fork error");
        }else if(res.process_list[i].pid == 0){
            close(res.process_list[i].fd[FW_CR][WRITE_END]);
            close(res.process_list[i].fd[CW_FR][READ_END]);
            //printf("path: %s | range %d - %d\n", path, ranges[i].start, ranges[i].end);
            what_q_does(father, i, path, ranges[i], res.process_list[i].fd);

        }else{
            close(res.process_list[i].fd[FW_CR][READ_END]);
            close(res.process_list[i].fd[CW_FR][WRITE_END]);

            pthread_create(&(res.process_list[i].thread_r), NULL, receiver_p, (void*)&args[i]);

        }
    }

    while(strcmp(path, EOT) != 0){
        //printf("P_path :%s\n", path);
        for(i = 0; i < q_number; i++){
            pthread_join(res.process_list[i].thread_r, NULL);
        }
        unsigned long long *final = (unsigned long long *) calloc(6, sizeof(unsigned long long));
        for(i = 0; i < q_number; i++){
            final[0] += q_res[i][0];
            final[1] += q_res[i][1];
            final[2] += q_res[i][2];
            final[3] += q_res[i][3];
            final[4] += q_res[i][4];
            final[5] += q_res[i][5];
        }
        //show_vect(final);printf("\n\n");
        send_to_parent_c(path, final, f_fds[CW_FR]);
        path = next_path(f_fds[FW_CR]);
        ranges = get_ranges_from_size(path, q_number);
        for(i = 0; i < q_number; i++){
            send_path(path, args[i].c_fds[FW_CR]);
            send_range(ranges[i], args[i].c_fds[FW_CR]);
        }
        for(i = 0; i < q_number; i++){
            pthread_create(&(res.process_list[i].thread_r), NULL, receiver_p, (void*)&args[i]);
        }
    }
    send_path(EOT, f_fds[CW_FR]);
}

void what_c_does(int p_number, int q_number, files_array *files, int **fd){

    process_p_list p = create_p(p_number, q_number, files, files->size, fd);

    while (wait(NULL) > 0)
        ;

    exit(0);
}

void what_p_does(int index, int q_number, char *path, int paths_number, int **fd){

    process_q_list q = create_q(index, q_number, path, paths_number, fd);

    while (wait(NULL) > 0)
        ;

    exit(0);
}

void what_q_does(int father, int index, char *path, range range, int **fd){

    unsigned long long *data;
    while(strcmp(path, EOT) != 0 && range.end >= 0){
        data = new_analyze(path, range);
        //show_vect(data);
        send_to_parent_p(path, data, fd[CW_FR]);
        path = next_path(fd[FW_CR]);
        //printf("Q: next path: %s\n\n", path);
        range = next_range(fd[FW_CR]);
        //printf("\n\nQ:\nrange : %d - %d\npath : %s\n",range.start, range.end, path);
    }

    send_path(EOT, fd[CW_FR]);

    exit(0);
}