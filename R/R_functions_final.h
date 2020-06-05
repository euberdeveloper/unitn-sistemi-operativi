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
    int alpha_upper;
    int alpha_lower;
    int digit;
    int punct;
    int space;
    int other;
}DATA_INFO;

typedef struct{
    char* path;
    off_t size;
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

DATA_FILE* deserialize(char* msg, int* result_size);
char* serialize(DATA_FILE* files, int files_size);
int total_letter_from_file(DATA_FILE* file);
int print_file(DATA_FILE* file, bool case_sensitive, bool percentage);
int show_files(DATA_FILE* files,int number_of_files,  bool case_sensitive, bool percentage, char** files_names, int size_file_names);
char* FILE_to_string(const DATA_FILE f);
bool ends_with_txt(char* str);
void init_zero(DATA_FILE* file);
void visit_recursive(char *name, int mode, DATA_FILE* files, int* counter);
void visit_iterative(char *name, int mode, DATA_FILE *files, int *counter);
DATA_FILE* get_files(char** input, int input_size, int* files_size, bool iterative);
void dealloc_FILES(DATA_FILE* files, int size);
int print_file_short(DATA_FILE* file, bool case_sensitive, bool percentage);
int print_files_short(DATA_FILE* files, int files_size, bool sensitive, bool percentage);

#endif