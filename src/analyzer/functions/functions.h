#ifndef FUNCTIONS
#define FUNCTIONS

/* IMPORTS */

#include <stdio.h>
#include <stdlib.h>
#include "../../../libs/general/general.h"

/* FUNCTIONS */

SH_STATE init(int p_number, int q_number, char** inputs, int inputs_size, bool recursive);
SH_STATE set(int p_number, int q_number, char** inputs, int inputs_size, bool recursive, bool keep);
SH_STATE restart(int p_number, int q_number, char** inputs, int inputs_size, bool recursive);
SH_STATE pop(char** inputs, int inputs_size);
SH_STATE status();
SH_STATE stop();
SH_STATE quit();

#endif