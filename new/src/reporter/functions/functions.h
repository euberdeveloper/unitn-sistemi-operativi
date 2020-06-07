#ifndef FUNCTIONS
#define FUNCTIONS

/* IMPORTS */

#include "../../../libs/general/general.h"
#include <signal.h>
#include "todo/todo.h"

/* EXTERNS */

extern char* sh_prompt_symbol;
extern bool sh_use_advanced_terminal;

/* FUNCTIONS */

SH_STATE show(bool sensitive, bool percentage, bool realtime, bool detailed, char** files, int files_size);
SH_STATE quit();

#endif