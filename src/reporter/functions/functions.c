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
    DATA_FILE *shits = (DATA_FILE*) malloc(sizeof(DATA_FILE) * 2);
    shits[0].path = "primo";
    init_zero(&shits[0]);
    shits[1].path = "secondo aòlskdjf òlsakjf aòls jfaòlkds jfòlkdsa jfòlsakj fòlksa jfdòlkasj flksa dfòl kjsafòlkdsalkf";
    init_zero(&shits[1]);

    show_todo(shits, 2, sensitive, percentage, detailed, files, files_size);

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