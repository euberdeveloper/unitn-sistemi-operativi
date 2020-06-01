#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../libs/shell_utils/shell_utils.h"
#include "shell_commands/shell_commands.h"
#include "functions/functions.h"

const int READ_END = 0;
const int WRITE_END = 1;
int analyzer_pipe[2];
int reporter_pipe[2];

int main() {
    pipe(analyzer_pipe);
    pipe(reporter_pipe);

    int pid = fork();
    if (pid == -1) {
        gn_abort("Error in forking", 1);
    }
	else if (pid == 0) {
        dup2(analyzer_pipe[READ_END], STDIN_FILENO);
        close(analyzer_pipe[READ_END]);
        close(analyzer_pipe[WRITE_END]);

		execl("../analyzer/analyzer", "", NULL);
	} 
    else {
        close(analyzer_pipe[READ_END]);

        int pid = fork();
        if (pid == -1) {
            gn_abort("Error in forking", 1);
        }
        else if (pid == 0) {
            dup2(reporter_pipe[READ_END], STDIN_FILENO);
            close(reporter_pipe[READ_END]);
            close(reporter_pipe[WRITE_END]);

            execl("../reporter/reporter", "", NULL);
        } 
        else {
            close(reporter_pipe[READ_END]);
            sh_loop();
        }
	}
    return 0;
}