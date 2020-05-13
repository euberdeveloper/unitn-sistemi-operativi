#ifndef SH_SHELL
#define SH_SHELL

#include "../utils/utils.h"

typedef enum {
    EXIT,
    CONTINUE
} STATE;

void sh_loop();
STATE sh_unknown_command(char* command);
void sh_argument_noval(const char* command, const char* argument);
void sh_argument_required(const char* command, const char* argument);
bool sh_argument_min(const char* command, const char* argument, int value, int min);
bool sh_argument_max(const char* command, const char* argument, int value, int max);
char *sh_extract_argument(char *word, bool* is_alias);

extern STATE sh_parse_command(char** words, int size);

#endif