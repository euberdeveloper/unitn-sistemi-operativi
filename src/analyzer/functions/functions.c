#include "functions.h"

/* HELPER VARIABLES AND CONSTANTS */

static const int COMMAND_END_SIGNAL = SIGUSR1;
static bool is_shell = false;
static int main_pid = -1;

/* HELPER FUNCTIONS DECLARATIONS */

static void ende_mitteilen();

/* EXPORTED FUNCTIONS */

SH_STATE arguments(bool local_is_shell, int local_main_pid, int p_number, int q_number, char** inputs, int inputs_size, bool recursive) {
    if (local_is_shell) {
        sh_prompt_symbol = "";
        sh_use_advanced_terminal = false;
        is_shell = true;
        main_pid = local_main_pid;
    }
    return SH_CONTINUE;
}

SH_STATE init(int p_number, int q_number, char** inputs, int inputs_size, bool recursive) {
    files_array files = get_files(inputs, inputs_size, true);
    process c = create_c(p_number, q_number, &files);

    ende_mitteilen();
    return SH_CONTINUE;
}

SH_STATE set(int p_number, int q_number, char** inputs, int inputs_size, bool recursive, bool keep) {
    printf("init: n = %d m = %d r = %d k = %d\n", p_number, q_number, recursive, keep);

    printf("[\n");
    int i;
    for (i = 0; i < inputs_size; i++) {
        printf("%s\n", inputs[i]);
    }
    printf("]\n");

    ende_mitteilen();
    return SH_CONTINUE;
}

SH_STATE restart(int p_number, int q_number, char** inputs, int inputs_size, bool recursive) {
    printf("init: n = %d m = %d r = %d\n", p_number, q_number, recursive);

    printf("[\n");
    int i;
    for (i = 0; i < inputs_size; i++) {
        printf("%s\n", inputs[i]);
    }
    printf("]\n");

    ende_mitteilen();
    return SH_CONTINUE;
}

SH_STATE pop(char** inputs, int inputs_size) {
    printf("[\n");
    int i;
    for (i = 0; i < inputs_size; i++) {
        printf("%s\n", inputs[i]);
    }
    printf("]\n");

    ende_mitteilen();
    return SH_CONTINUE;
}

SH_STATE status() {
    printf("status\n");

    ende_mitteilen();
    return SH_CONTINUE;
}

SH_STATE stop() {
    printf("stop\n");

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