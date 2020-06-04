#include "functions.h"

/* HELPER FUNCTIONS DECLARATIONS */

static void forward_and_wait(int pipe[]);

/* EXPORTED FUNCTIONS */

SH_STATE arguments(int p_number, int q_number, char** inputs, int inputs_size, bool recursive) {
    sig_init_signals();
}

SH_STATE init(int p_number, int q_number, char** inputs, int inputs_size, bool recursive) {
    forward_and_wait(analyzer_pipe);
    return SH_CONTINUE;
}

SH_STATE set(int p_number, int q_number, char** inputs, int inputs_size, bool recursive, bool keep) {
    forward_and_wait(analyzer_pipe);
    return SH_CONTINUE;
}

SH_STATE restart(int p_number, int q_number, char** inputs, int inputs_size, bool recursive) {
    forward_and_wait(analyzer_pipe);
    return SH_CONTINUE;
}

SH_STATE pop(char** inputs, int inputs_size) {
    forward_and_wait(analyzer_pipe);
    return SH_CONTINUE;
}

SH_STATE status() {
    forward_and_wait(analyzer_pipe);
    return SH_CONTINUE;
}
SH_STATE stop() {
    forward_and_wait(analyzer_pipe);
    return SH_CONTINUE;
}

SH_STATE show(bool sensitive, bool percentage, bool realtime, bool detailed, char** files, int files_size) {
    forward_and_wait(reporter_pipe);
    return SH_CONTINUE;
}

SH_STATE quit() {
    forward_and_wait(analyzer_pipe);
    forward_and_wait(reporter_pipe);
    return SH_EXIT;
}

/* HELPER FUNCTIONS DEFINITIONS */

static void forward_and_wait(int pipe[]) {
    sig_wait_command_termination = true;
    write(pipe[1], sh_last_command, strlen(sh_last_command) * sizeof(char));
    while (sig_wait_command_termination) ;
}