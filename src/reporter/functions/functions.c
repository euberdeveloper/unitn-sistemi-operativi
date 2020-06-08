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

SH_STATE show(bool sensitive, bool percentage, bool realtime, bool detailed, bool total, char** files, int files_size) {
    data_file *shits = (data_file*) malloc(sizeof(data_file) * 2);
    shits[0].path = "primo";
    shits[0].data_info.alpha_lower = 1;
    shits[0].data_info.alpha_upper = 1;
    shits[0].data_info.digit = 1;
    shits[0].data_info.other = 1;
    shits[0].data_info.punct = 1;
    shits[0].data_info.space = 1;
    shits[1].path = "secondo aòlskdjf òlsakjf aòls jfaòlkds jfòlkdsa jfòlsakj fòlksa jfdòlkasj flksa dfòl kjsafòlkdsalkf";
    shits[1].data_info.alpha_lower = 22;
    shits[1].data_info.alpha_upper = 22;
    shits[1].data_info.digit = 22;
    shits[1].data_info.other = 22;
    shits[1].data_info.punct = 22;
    shits[1].data_info.space = 22;

    df_show_formatted_data(sensitive, percentage, detailed, total, files, files_size, shits, 2);

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