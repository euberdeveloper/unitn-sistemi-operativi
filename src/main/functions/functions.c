#include "functions.h"
extern char* last_command;

SH_STATE init(int p_number, int q_number, char** inputs, int inputs_size, bool recursive) {
    write(analyzer_pipe[1], last_command, strlen(last_command) * sizeof(char));
    return SH_CONTINUE;
}

SH_STATE set(int p_number, int q_number, char** inputs, int inputs_size, bool recursive, bool keep) {
    write(analyzer_pipe[1], last_command, strlen(last_command) * sizeof(char));

    return SH_CONTINUE;
}

SH_STATE restart(int p_number, int q_number, char** inputs, int inputs_size, bool recursive) {
    write(analyzer_pipe[1], last_command, strlen(last_command) * sizeof(char));

    return SH_CONTINUE;
}

SH_STATE pop(char** inputs, int inputs_size) {
    write(analyzer_pipe[1], last_command, strlen(last_command) * sizeof(char));

    return SH_CONTINUE;
}

SH_STATE status() {
    write(analyzer_pipe[1], last_command, strlen(last_command) * sizeof(char));

    return SH_CONTINUE;
}
SH_STATE stop() {
    write(analyzer_pipe[1], last_command, strlen(last_command) * sizeof(char));

    return SH_CONTINUE;
}

SH_STATE show(bool sensitive, bool percentage, bool realtime, bool detailed, char** files, int files_size) {
    write(reporter_pipe[1], last_command, strlen(last_command) * sizeof(char));

    return SH_CONTINUE;
}

SH_STATE quit() {
    write(analyzer_pipe[1], last_command, strlen(last_command) * sizeof(char));

    return SH_EXIT;
}