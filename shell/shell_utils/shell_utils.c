#include "shell_utils.h"

void sh_unknown_command(char* command) {
    char* message;
    asprintf(&message, "unknown command %s", command);
    log_error_ctx_del(message, strdup("SHELL"));
}

bool sh_check_noval(const char* command, const char* argument) {
    
}

void sh_check_required(const char* command, const char* argument) {

}

bool sh_check_min(const char* command, const char* argument, int value, int min) {

}

bool sh_check_max(const char* command, const char* argument, int value, int max) {

}

char *sh_extract_argument(char *word, bool* is_alias) {

}
