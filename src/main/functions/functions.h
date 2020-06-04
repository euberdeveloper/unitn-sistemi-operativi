#ifndef FUNCTIONS
#define FUNCTIONS

/* IMPORTS */

#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../../../libs/general/general.h"
#include "../signals/signals.h"

/* EXTERNS */

extern int analyzer_pipe[2];
extern int reporter_pipe[2];
extern char* sh_last_command;

/* FUNCTIONS */

SH_STATE arguments(int p_number, int q_number, char** inputs, int inputs_size, bool recursive);
SH_STATE init(int p_number, int q_number, char** inputs, int inputs_size, bool recursive);
SH_STATE set(int p_number, int q_number, char** inputs, int inputs_size, bool recursive, bool keep);
SH_STATE restart(int p_number, int q_number, char** inputs, int inputs_size, bool recursive);
SH_STATE pop(char** inputs, int inputs_size);
SH_STATE status();
SH_STATE stop();
SH_STATE show(bool sensitive, bool percentage, bool realtime, bool detailed, char** files, int files_size);
SH_STATE quit();

#endif