#include "functions.h"

/* HELPER VARIABLES AND CONSTANTS */

static const int COMMAND_END_SIGNAL = SIGUSR2;
static bool is_shell = false;
static int main_pid = -1;

/* HELPER FUNCTIONS DECLARATIONS */

static void ende_mitteilen();

/* EXPORTED FUNCTIONS */

SH_STATE arguments(bool local_is_shell, int local_main_pid, bool sensitive, bool percentage, bool realtime, bool detailed, char** files, int files_size) {
    if (local_is_shell) {
        sh_prompt_symbol = "";
        sh_use_advanced_terminal = false;
        is_shell = true;
        main_pid = local_main_pid;
    }

    ende_mitteilen();
    return SH_CONTINUE;
}

SH_STATE show(bool sensitive, bool percentage, bool realtime, bool detailed, char** files, int files_size) {
    printf("s = %d, p = %d, r = %d, d = %d\n", sensitive, percentage, realtime, detailed);
    printf("[\n");
    for (int i = 0; i < files_size; i++) {
        printf("%s\n", files[i]);
    }
    printf("]\n");

    ende_mitteilen();
    return SH_CONTINUE;
}
SH_STATE quit() {
    printf("quit\n");
    ende_mitteilen();
    return SH_EXIT;
}

/* HELPER FUNCTIONS DEFINITIONS */

static void ende_mitteilen() {
    if (main_pid != -1) {
        kill(main_pid, COMMAND_END_SIGNAL);
    }
}