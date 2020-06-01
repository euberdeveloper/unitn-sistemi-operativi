#ifndef SH_SHELL_COMMANDS
#define SH_SHELL_COMMANDS

/* IMPORTS */

#include "../../../libs/general/general.h"
#include "../../../libs/text/text.h"

/* EXTERNS */

extern void shu_unknown_command(char *command);
extern void shu_value_without_argument(char* value);
extern void shu_unknown_argument(char *command, char* argument);
extern bool shu_check_noval(const char *command, const char *argument, int size, int *i);
extern bool shu_check_noval_array(const char *command, const char *argument, bool is_assigned);
extern bool shu_check_required(const char* command, const char* argument, bool is_assigned);
extern bool shu_check_min_int(const char *command, const char *argument, int value, int min);
extern bool shu_check_max_int(const char *command, const char *argument, int value, int max);
extern bool shu_check_min_long(const char *command, const char *argument, long value, long min);
extern bool shu_check_max_long(const char *command, const char *argument, long value, long max);
extern bool shu_check_min_float(const char *command, const char *argument, float value, float min);
extern bool shu_check_max_float(const char *command, const char *argument, float value, float max);
extern bool shu_check_min_double(const char *command, const char *argument, double value, double min);
extern bool shu_check_max_double(const char *command, const char *argument, double value, double max);
extern bool shu_get_int_value(const char* command, const char* argument, char* str_value, int* value);
extern bool shu_get_long_value(const char* command, const char* argument, char* str_value, long* value);
extern bool shu_get_float_value(const char* command, const char* argument, char* str_value, float* value);
extern bool shu_get_double_value(const char* command, const char* argument, char* str_value, double* value);
extern bool shu_get_char_value(const char* command, const char* argument, char* str_value, char* value);
extern char* shu_extract_argument(char *word, bool* is_alias);

extern SH_STATE show(bool sensitive, bool percentage, bool realtime, bool detailed, char** files, int files_size);
extern SH_STATE quit();

/* FUNCTIONS */

SH_STATE sh_handle_add(char** words, int n_words);
SH_STATE sh_handle_acc(char** words, int n_words);
SH_STATE sh_parse_command(char** words, int n_words);
void sh_loop();

#endif