#ifndef CM_COMMUNICATION
#define CM_COMMUNICATION

/* IMPORTS */

#include "../../../../libs/general/general.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <errno.h>

/* VARIABLES */

extern data_file *cm_data;
extern int cm_data_size;

extern data_file cm_sleeve_ace[10];

/* FUNCTIONS */

void cm_init_sleeve_ace();
void cm_fetch();

#endif