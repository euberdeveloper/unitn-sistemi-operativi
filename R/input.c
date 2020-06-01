#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <string.h>
#include <limits.h>
#include "R_functions.h"


#define BUF_SIZE 1024

//int FILE_COUNTER = 0;
int WRITE_MODE = 1;






/*
char** get_files_path(char* directory_name){
    char** path_matrix;
    //visit_recursive(directory_name,0,path_matrix);
    printf("counter = %d\n", FILE_COUNTER);
    path_matrix = (char **) malloc (sizeof(char*) * FILE_COUNTER);
    int i;
    for (i = 0; i < FILE_COUNTER; i++){
        path_matrix[i] = (char*) malloc(sizeof(char) * PATH_MAX);
    }
    FILE_COUNTER = 0;
    //visit_recursive(directory_name,WRITE_MODE,path_matrix);
    FILE_COUNTER = 0;
    return path_matrix;
}*/


int main(int argc, char** argv)
{
    
    int r = 0;
   // visit_recursive(argv[1], 0, NULL, &r);
    //ALLOCARE MAN MANO CHE LI LEGGO CON STRLEN PER RISPARMIARE MEMORIA
    //printf("number = %d\nfile counter = %d", r, FILE_COUNTER);
    /*
    for (i = 0; i < FILE_COUNTER; i++){
        printf("\'%s\'\n", path_matrix[i]);
    }*/
    int files_size = 0;
    DATA_FILE* files = get_files(&argv[1], argc - 1, &files_size);
    int i;
    for (i = 0; i < files_size; i++){
        print_file(&files[i],true, true);
        fflush(stdout);
        //printf("hey");
    }
    printf("\nDONE\n");
    return 0;
}