#include "signals.h"

/* HELPER FUNCTIONS DECLARATIONS */

static void _sig_signal(int sig, __sighandler_t handler);
static void _sig_handle_signal_analizer(int sig);
static void _sig_handle_signal_reporter(int sig);

/* EXPORTED VARIABLES */

bool sig_wait_command_termination;

/* EXPORTED FUNCTIONS */

void sig_init_signals() {
    sig_wait_command_termination = false;
    _sig_signal(SIGUSR1, _sig_handle_signal_analizer);
    _sig_signal(SIGUSR2, _sig_handle_signal_reporter);
}

/* HELPER FUNCTIONS DEFINITIONS */

static void _sig_signal(int sig, __sighandler_t handler) {
    if (signal(sig, handler) == SIG_ERR) {
        gn_abort("Error in signal", ERROR_SIGNAL);
    }
}

static void _sig_handle_signal_analizer(int sig) {
    sig_wait_command_termination = false;
}

static void _sig_handle_signal_reporter(int sig) {
    sig_wait_command_termination = false;
}