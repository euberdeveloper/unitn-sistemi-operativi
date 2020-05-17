#ifndef SHU_SHELL_UTILS
#define SHU_SHELL_UTILS

/* IMPORTS */

#include "../general/general.h"
#include "../logger/logger.h"

/* FUNCTIONS */

void sh_unknown_command(char* command);
bool sh_check_noval(const char* command, const char* argument);
void sh_check_required(const char* command, const char* argument);
bool sh_check_min(const char* command, const char* argument, int value, int min);
bool sh_check_max(const char* command, const char* argument, int value, int max);
char *sh_extract_argument(char *word, bool* is_alias);

#endif