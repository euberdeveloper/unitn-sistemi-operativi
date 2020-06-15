
#include "communications.h"


// NORMALS
char *next_path(int *fd){
    int size;
    read(fd[READ_END], &size, sizeof(int));
    char *new_path = (char *)malloc(sizeof(char) * (size + 1));
    read(fd[READ_END], new_path, sizeof(char) * size);
    new_path[size] = '\0';
    return new_path;
}
range next_range(int *fd){
    range res;
    read(fd[READ_END], &(res.start), sizeof(int));
    read(fd[READ_END], &(res.end), sizeof(int));
    return res;
}
void send_path(char *path, int *fd){
    int size = (int)strlen(path);
    write(fd[WRITE_END], &size, sizeof(int));
    write(fd[WRITE_END], path, sizeof(char) * size);
}
void send_range(range range, int *fd){
    write(fd[WRITE_END], &range.start, sizeof(int));
    write(fd[WRITE_END], &range.end, sizeof(int));
}

void send_to_parent_p(char *path, unsigned long long *vect, int *fd){
    /*printf("Writing to P: \n");
    printf("path: %s\n", path);
    int i = 0;
    for( ; i < 6; i++){
        printf("data%d: %llu\n", i, vect[i]);
    }printf("\n\n");*/
    int size = (int) strlen(path);
    write(fd[WRITE_END], &size, sizeof(int));
    write(fd[WRITE_END], path, sizeof(char) * size);
    write(fd[WRITE_END], vect, sizeof(unsigned long long ) * 6);
}

void send_to_parent_c(char *path, unsigned long long *vect, int *fd){
    /*printf("Writing to C: \n");
    printf("path: %s\n", path);
    int i = 0;
    for( ; i < 6; i++){
        printf("data%d: %llu\n", i, vect[i]);
    }printf("\n\n");*/
    int size = (int) strlen(path);
    write(fd[WRITE_END], &size, sizeof(int));
    write(fd[WRITE_END], path, sizeof(char) * size);
    write(fd[WRITE_END], vect, sizeof(unsigned long long ) * 6);
}


// THREADS

void *receiver_c(void *args){
    receiver_args_c *comm = args;
    int i;
    /*for(i = 0; i< comm->p_input.path_size; i++){
        printf("Path: %s\n", comm->p_input.paths[i]);
    }*/
    i = 0;
    char *path = next_path(comm->c_fds[CW_FR]);

    files_array data_array;
    data_array.files = (data_file*)malloc(sizeof(data_file) * (comm->p_input.path_size-1) );
    data_array.size = comm->p_input.path_size-1;
    unsigned long long *vect = (unsigned long long *) calloc(6, sizeof(unsigned long long));
    while(strcmp(path, EOT) != 0){
        /*if(i > 0){
            data_array.size ++;
            data_array.files = (data_file*) realloc(data_array.files,sizeof(data_file) * data_array.size);
        }*/
        read(comm->c_fds[CW_FR][READ_END], vect, sizeof(unsigned long long) * 6);

        /*printf("Receiving from P: \n");
        printf("path: %s\n", path);
        int k = 0;
        for( ; k < 6; k++){
            printf("data%d: %llu\n", k, vect[k]);
        }printf("\n\n");*/
        comm->p[i].path = path;
        //data_array.files[i].path = path;
        comm->p[i].data_info = vect_to_data_info(vect);
        //data_array.files[i].data_info = vect_to_data_info(vect);
        i++;
        if(i < comm->p_input.path_size){
            send_path(comm->p_input.paths[i], comm->c_fds[FW_CR]);
        }else{
            send_path("EOT", comm->c_fds[FW_CR]);
        }


        //printf("Sending to P : path: %s\n\n", path);
        path = next_path(comm->c_fds[CW_FR]);
    }

    /*for(i = 0; i < data_array.size; i++){
        printf("Path: %s\n",comm->p[i].path);
        printf("Upper: %d\n", comm->p[i].data_info.alpha_upper);
        printf("Lower: %d\n", comm->p[i].data_info.alpha_lower);
        printf("Digit: %d\n", comm->p[i].data_info.digit);
        printf("Punct: %d\n", comm->p[i].data_info.punct);
        printf("Space: %d\n", comm->p[i].data_info.space);
        printf("Other: %d\n\n\n", comm->p[i].data_info.other);
    }*/



    //fprintf(stderr, "OK Here\n");
    return NULL;
}


void *receiver_p(void *args){
    receiver_args_p *comm = args;
    range *ranges;
    char *path = next_path(comm->c_fds[CW_FR]);
    //if(strcmp(path, EOT) != 0)//aggiunto ciò
        read(comm->c_fds[CW_FR][READ_END], comm->p, sizeof(unsigned long long) * 6);

    //show_vect(comm->p);
    return NULL;
}
