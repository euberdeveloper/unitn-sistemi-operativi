#ifndef R_FUNCTIONS_H
#define R_FUNCTIONS_H

#include <stdio.h>
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>


typedef struct{
    int alpha_upper;
    int alpha_over;
    int digit;
    int punct;
    int space;
    int other;
}DATA_INFO;

typedef struct{
    char* path;
    DATA_INFO data_info;
}DATA_FILE;

typedef enum{
    false,
    true
}bool;

static const char* SPACE = " ";

DATA_FILE* deserialize(char* msg, int* result_size);
int total_letter_from_file(DATA_FILE* file);
int print_file(DATA_FILE* file, bool case_sensitive, bool percentage);
int show_files(DATA_FILE* files,int number_of_files,  bool case_sensitive, bool percentage, char** files_names, int size_file_names);

#endif