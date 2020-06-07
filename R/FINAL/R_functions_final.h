#ifndef R_FUNCTIONS_FINAL_H
#define R_FUNCTIONS_FINAL_H

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <sys/syscall.h>

typedef struct{
    unsigned long long int alpha_upper;
    unsigned long long int alpha_lower;
    unsigned long long int digit;
    unsigned long long int punct;
    unsigned long long int space;
    unsigned long long int other;
}DATA_INFO;

typedef struct{
    char* path;
    unsigned long long int size;
    DATA_INFO data_info;
}DATA_FILE;

typedef enum{
    false,
    true
}bool;

typedef struct
{
    long d_ino;              //i-node
    off_t d_off;             //offset to next linux dirent
    unsigned short d_reclen; //lengh of this linux dirent
    char d_name[];           //filename
} linux_dirent;



static const int WRITE_MODE = 1;
static const char* SPACE = " ";
static const char* TXT = ".txt";
static const int BUF_SIZE = 1024;

unsigned long long int total_letter_from_file(DATA_FILE* file);
bool ends_with_txt(char* str);
void init_zero(DATA_FILE* file);
void visit_recursive(char *name, int mode, DATA_FILE* files, int* counter);
void visit_iterative(char *name, int mode, DATA_FILE *files, int *counter);
DATA_FILE* get_files(char** input, int input_size, int* files_size, bool duplicate);
void dealloc_FILES(DATA_FILE* files, int size);
int print_file_short(DATA_FILE* file, bool case_sensitive, bool percentage);
int show(DATA_FILE* files, int files_size, bool sensitive, bool percentage, bool detailed, char** input, int input_size);

#endif