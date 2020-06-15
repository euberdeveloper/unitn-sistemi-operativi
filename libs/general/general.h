#ifndef GN_GENERAL_H
#define GN_GENERAL_H

/* IMPORTS */

#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include "../colour/colour.h"

/* DEFINES */

#define ERROR_FORK 1
#define ERROR_PIPE_INIT 2
#define ERROR_PIPE_READ 2
#define ERROR_DESCRIPTOR_CLOSE 4
#define ERROR_FCNTL 5
#define ERROR_SIGNAL 6
#define ERROR_THREAD_CREATE 7

/* STRUCTS */

typedef struct {
    unsigned long long int alpha_upper;
    unsigned long long int alpha_lower;
    unsigned long long int digit;
    unsigned long long int punct;
    unsigned long long int space;
    unsigned long long int other;
} data_info;

typedef struct{
    char* path;
    unsigned long long int size;
    data_info data_info;
} data_file;

/* ENUMS */

/**
 * The enum to simulate the boolean type 
*/
typedef enum { 
    false, 
    true 
} bool;

/**
 * The enum to have the state of the shell
*/
typedef enum {
    SH_CONTINUE,
    SH_EXIT
} SH_STATE;

/* FUNCTIONS */

/**
 * A function that prints a message and exits the program with a given code
 * @param message The message to print
 * @param code The code of the exited program 
*/
void gn_abort(char* message, int code);

#endif