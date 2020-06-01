#ifndef GN_GENERAL_H
#define GN_GENERAL_H

/* IMPORTS */

#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include "../colour/colour.h"

/* ENUMS */

/**
 * The enum to simulate the boolean type 
*/
typedef enum { 
    false, 
    true 
} bool;

/* FUNCTIONS */

/**
 * A function that prints a message and exits the program with a given code
 * @param message The message to print
 * @param code The code of the exited program 
*/
void gn_abort(char* message, int code);

#endif