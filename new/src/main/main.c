#include <unistd.h>

#include "../../libs/shell_utils/shell_utils.h"
#include "shell_commands/shell_commands.h"
#include "functions/functions.h"
#include "forking/forking.h"

/* FUNCTIONS SIGNATURES */

void start_analizer(char* main_pid);
void start_reporter(char* main_pid);

/* ENTRY POINT */

int main(int argc, char** argv) {
    sh_handle__arguments(argv, argc);

    char *main_pid = fk_get_str_pid();
    fk_init_pipes();

    if (fk_fork() == 0) {
        start_analizer(main_pid);
    }
    else {
        fk_close(fk_main_to_analyzer_pipe[READ_END]);
        fk_close(fk_analyzer_to_main_pipe[WRITE_END]);

        if (fk_fork() == 0) {
            start_reporter(main_pid);
        }
        else {
            fk_close(fk_main_to_reporter_pipe[READ_END]);  
            fk_close(fk_reporter_to_main_pipe[WRITE_END]);

            fk_set_nonblock(fk_analyzer_to_main_pipe[READ_END]);
            fk_set_nonblock(fk_reporter_to_main_pipe[READ_END]);

            init_analyzer_output_thread();
            init_reporter_output_thread();

            sh_loop();
        }
    }

    return 0;
}

/* FUNCTIONS DEFINITIONS */

void start_analizer(char* main_pid) {
    fk_pipe_redirect_in(fk_main_to_analyzer_pipe);
    fk_pipe_redirect_out(fk_analyzer_to_main_pipe);

    execl("../analyzer/analyzer", "placeholder", "--is-shell", "--main-pid", main_pid, NULL);
}

void start_reporter(char* main_pid) {
    fk_pipe_redirect_in(fk_main_to_reporter_pipe);
    fk_pipe_redirect_out(fk_reporter_to_main_pipe);

    execl("../reporter/reporter", "placeholder", "--is-shell", "--main-pid", main_pid, NULL);
}