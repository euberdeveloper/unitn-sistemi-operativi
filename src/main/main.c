#include <unistd.h>

#include "../../libs/shell_utils/shell_utils.h"
#include "../../libs/forking/forking.h"
#include "pipes/pipes.h"
#include "shell_commands/shell_commands.h"
#include "functions/functions.h"

/* FUNCTIONS SIGNATURES */

void start_analizer(char* main_pid);
void start_reporter(char* main_pid);

/* ENTRY POINT */

int main(int argc, char** argv) {
    sh_handle__arguments(argv, argc);

    char *main_pid = fk_get_str_pid();
    fk_init_pipes(pip_main_analyzer_pipe);
    fk_init_pipes(pip_main_reporter_pipe);

    if (fk_fork() == 0) {
        start_analizer(main_pid);
    }
    else {
        fk_close(pip_main_analyzer_pipe[PARENT_TO_CHILD][READ_END]);
        fk_close(pip_main_analyzer_pipe[CHILD_TO_PARENT][WRITE_END]);

        if (fk_fork() == 0) {
            start_reporter(main_pid);
        }
        else {
            fk_close(pip_main_reporter_pipe[PARENT_TO_CHILD][READ_END]);
            fk_close(pip_main_reporter_pipe[CHILD_TO_PARENT][WRITE_END]);

            fk_set_nonblock(pip_main_analyzer_pipe[CHILD_TO_PARENT][READ_END]);
            fk_set_nonblock(pip_main_reporter_pipe[CHILD_TO_PARENT][READ_END]);

            init_analyzer_output_thread();
            init_reporter_output_thread();

            sh_loop();
        }
    }

    return 0;
}

/* FUNCTIONS DEFINITIONS */

void start_analizer(char* main_pid) {
    fk_pipe_redirect_in(pip_main_analyzer_pipe[PARENT_TO_CHILD]);
    fk_pipe_redirect_out(pip_main_analyzer_pipe[CHILD_TO_PARENT]);

    execl("./analyzer", "placeholder", "--is-shell", "--main-pid", main_pid, NULL);
}

void start_reporter(char* main_pid) {
    fk_pipe_redirect_in(pip_main_reporter_pipe[PARENT_TO_CHILD]);
    fk_pipe_redirect_out(pip_main_reporter_pipe[CHILD_TO_PARENT]);

    execl("./reporter", "placeholder", "--is-shell", "--main-pid", main_pid, NULL);
}