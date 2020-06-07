#ifndef FUNCTIONS
#define FUNCTIONS

/* IMPORTS */

#include "../../../libs/general/general.h" 

#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

#include "../forking/forking.h"
#include "signals/signals.h"

/* EXTERNS */

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

void init_analyzer_output_thread();
void init_reporter_output_thread();

#endif