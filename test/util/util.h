//
// Created by xeno on 29/05/20.
//

#ifndef PROJECT_UTIL_H
#define PROJECT_UTIL_H

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define false 0
#define true 1

typedef char bool;

typedef struct {
    int alpha_upper;
    int alpha_lower;
    int digit;
    int punct;
    int space;
    int other;
} data_info;

typedef struct {
    char* path;
    data_info info;
} data_file;

typedef struct {
    char **inputs;
    int size;
}data_inputs;

typedef struct {
    char *path;
    int files_number;
    data_file *files;
}pthread_analyzer_arguments;

typedef struct {
    pid_t pid;
    pthread_t thread_r, thread_w;
    pthread_analyzer_arguments *arg;
}data_process;

//Util
void parse_arguments(int argc, char* argv[],int *n, int *m, data_inputs *input, bool *shell, bool *rec);
void print_parsed_arguments(int *n, int *m, data_inputs *input, bool *shell, bool *rec);
void print_files_data(pthread_analyzer_arguments *arg);
char* concat(const char *s1, const char *s2);
char *to_string(int number);


//Process Related
data_inputs *divide_input(int number,data_inputs input);
char **create_execv_args(int n, int m, data_inputs input);
data_process *create_process(int n, int m, data_inputs input, char *child);


//Thread Communication
void *pthread_fd_shell_sender(void *args);
void *pthread_fd_shell_receiver(void *args);
void *pthread_fd_analyzer_sender(void *args);
void *pthread_fd_analyzer_receiver(void *args);

#endif //PROJECT_UTIL_H
