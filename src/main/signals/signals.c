#include "signals.h"

/* HELPER FUNCTIONS DECLARATIONS */

static void sig_handle_signal_analizer(int sig);
static void sig_handle_signal_reporter(int sig);

/* EXPORTED VARIABLES */

bool sig_wait_command_termination;

/* EXPORTED FUNCTIONS */

void sig_init_signals() {
    sig_wait_command_termination = false;
    signal(SIGUSR1, sig_handle_signal_analizer);
    signal(SIGUSR2, sig_handle_signal_reporter);
}

/* HELPER FUNCTIONS DEFINITIONS */

static void sig_handle_signal_analizer(int sig) {
    sig_wait_command_termination = false;
}

static void sig_handle_signal_reporter(int sig) {
    sig_wait_command_termination = false;
}