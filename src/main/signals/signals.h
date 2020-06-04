#ifndef SIG_SIGNALS
#define SIG_SIGNALS

/* IMPORTS */

#include <signal.h>
#include "../../../libs/general/general.h"

/* VARIABLES */

extern bool sig_wait_command_termination;

/* FUNCTIONS */

void sig_init_signals();

#endif