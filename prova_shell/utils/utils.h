#ifndef UTL_UTILS
#define UTL_UTILS

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef enum { 
    false, 
    true 
} bool;

char *utl_abort(const char* message, int code);

char *utl_readline();
char **utl_splitline(char *line, int *size);

void utl_free_string_array(char **array, int size);

#endif