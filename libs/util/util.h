//
// Created by xeno on 08/06/20.
//

#ifndef SOLVER_UTIL_H
#define SOLVER_UTIL_H

#define _GNU_SOURCE

#define BUFF_SIZE 1024
#define WRITE_MODE 1
#define TXT ".txt"
#define NUMBER_P "%d\n"
#define STRING_P "%s\n"
#define READ_END 0
#define WRITE_END 1
#define FW_CR 0
#define CW_FR 1
#define EOT "EOT"

#include <fcntl.h>
#include <limits.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../general/general.h"


typedef struct
{
    long d_ino;              //i-node
    unsigned long long d_off;             //offset to next linux dirent
    unsigned short d_reclen; //lengh of this linux dirent
    char d_name[];           //filename
} linux_dirent;



typedef struct {
    data_file *files;
    int size;
}files_array;

typedef struct{
    char** paths;
    //unsigned long long * sizes;
    int path_size;
}p_input;

typedef struct{
    int start;
    int end;
}range;

typedef struct
{
    char **files_paths;
    range *ranges;
    int size_ranges_files; // they are the same size ///ashdgashdgashgdahsgdahsgdashdgashdgashdg
} q_input;

// PROCESS -----

typedef struct {
    int pid;
    int **fd;
    int index;
    pthread_t thread_r;
}process;

typedef struct{
    process *process_list;
    p_input *p_inputs;
    int p_number;
    int q_number;
}process_p_list;

typedef struct {
    process *process_list;
    int q_number;
}process_q_list;

typedef struct {
    int **f_fds;
    int **c_fds;
    int index;
    data_file *p;
    p_input p_input;
}receiver_args_c;

typedef struct {
    int **f_fds;
    int **c_fds;
    unsigned long long *p;
    int index;
}receiver_args_p;


// XENO SAMA
int **create_pipes(int n_pipes);
unsigned long long *new_analyze(char *path, range range);
data_info vect_to_data_info(unsigned long long *vect);

void show_vect(unsigned long long *vect);

//SEBGOD
files_array get_files(char **input, int input_size, bool duplicate);
files_array old_get_files(char** input, int input_size);
range* get_ranges_from_size(char* path, int number_of_q);
p_input* get_P_input(data_file* files, int files_size, int number_of_P);
bool ends_with_txt(char* str);
void init_zero(data_file * file);


#endif //SOLVER_UTIL_H
