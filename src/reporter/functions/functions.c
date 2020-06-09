#include "functions.h"

/* HELPER VARIABLES AND CONSTANTS */

static const int COMMAND_END_SIGNAL = SIGUSR2;
static bool is_shell = false;
static int main_pid = -1;

/* HELPER FUNCTIONS DECLARATIONS */

static void ende_mitteilen();

/* EXPORTED FUNCTIONS */

SH_STATE arguments(bool local_is_shell, int local_main_pid, bool sensitive, bool percentage, bool detailed, bool total, char** files, int files_size) {
     void cm_init_sleeve_ace();
    
    if (local_is_shell) {
        sh_prompt_symbol = "";
        sh_use_advanced_terminal = false;
        is_shell = true;
        main_pid = local_main_pid;
    }
    else {
        cm_fetch();
        if (cm_data != NULL) {
            df_show_formatted_data(sensitive, percentage, detailed, total, files, files_size, cm_data, cm_data_size);
        }
        else {
            puts("Nessun dato da mostrare");
        }
    }

    ende_mitteilen();
    return SH_CONTINUE;
}

SH_STATE show(bool sensitive, bool percentage, bool detailed, bool total, char** files, int files_size) {
    cm_fetch();
    if (cm_data != NULL) {
        df_show_formatted_data(sensitive, percentage, detailed, total, files, files_size, cm_data, cm_data_size);
    }
    else {
        puts("Nessun dato da mostrare");
    }

    ende_mitteilen();
    return SH_CONTINUE;
}

SH_STATE quit() {
    ende_mitteilen();
    return SH_EXIT;
}

/* HELPER FUNCTIONS DEFINITIONS */

static void ende_mitteilen() {
    if (main_pid != -1) {
        kill(main_pid, COMMAND_END_SIGNAL);
    }
}