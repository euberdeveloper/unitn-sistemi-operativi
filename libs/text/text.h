#ifndef TXT_TEXT_H
#define TXT_TEXT_H

/* IMPORTS */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../general/general.h"

/* FUNCTIONS */

/**
 * Reads from stdin a line of text
 * @return The read line as a string
*/
char *txt_readline();
/**
 * Splits a line into words
 * @param line The line to be split into words
 * @param size A pointer to an integer that will contain the number of the returned words
 * @return An array of strings containing the obtained words
*/
char **txt_splitline(char *line, int *size);
/**
 * Deallocates a given array of strings
 * @param array The strings array to be deallocated
 * @param size The number of elements of the given strings array 
*/
void txt_free_string_array(char **array, int size);

#endif