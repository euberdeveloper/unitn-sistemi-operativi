#ifndef FUNCTIONS
#define FUNCTIONS

/* IMPORTS */

#include <stdio.h>
#include <stdlib.h>
#include "../../../libs/general/general.h"

/* FUNCTIONS */

SH_STATE show(bool sensitive, bool percentage, bool realtime, bool detailed, char** files, int files_size);
SH_STATE quit();

#endif