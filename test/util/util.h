//
// Created by xeno on 29/05/20.
//

#ifndef PROJECT_UTIL_H
#define PROJECT_UTIL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#define false 0
#define true 1

typedef int bool;

typedef struct {
    int alpha_upper;
    int alpha_ower;
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
    char *path;
    data_file *file;
}pthread_arguments;

void *pthread_fd_shell_sender(void *args);
void *pthread_fd_shell_receiver(void *args);

void *pthread_fd_analyzer(void *args);

#endif //PROJECT_UTIL_H
