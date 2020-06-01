#ifndef SHU_SHELL_UTILS
#define SHU_SHELL_UTILS

/* IMPORTS */

#define _GNU_SOURCE 
#include <stdio.h>
#include <string.h>

#include "../general/general.h"
#include "../logger/logger.h"

/* FUNCTIONS */

void shu_unknown_command(char *command);
void shu_unknown_argument(char *command, char* argument);
void shu_value_without_argument(char* value);

bool shu_check_noval(const char *command, const char *argument, int size, int *i);
bool shu_check_noval_array(const char *command, const char *argument, bool is_assigned);
bool shu_check_required(const char* command, const char* argument, bool is_assigned);
bool shu_check_min_int(const char *command, const char *argument, int value, int min);
bool shu_check_max_int(const char *command, const char *argument, int value, int max);
bool shu_check_min_long(const char *command, const char *argument, long value, long min);
bool shu_check_max_long(const char *command, const char *argument, long value, long max);
bool shu_check_min_float(const char *command, const char *argument, float value, float min);
bool shu_check_max_float(const char *command, const char *argument, float value, float max);
bool shu_check_min_double(const char *command, const char *argument, double value, double min);
bool shu_check_max_double(const char *command, const char *argument, double value, double max);

bool shu_get_int_value(const char *command, const char *argument, char* str_value, int* value);
bool shu_get_long_value(const char *command, const char *argument, char* str_value, long* value);
bool shu_get_float_value(const char *command, const char *argument, char* str_value, float* value);
bool shu_get_double_value(const char *command, const char *argument, char* str_value, double* value);
bool shu_get_char_value(const char *command, const char *argument, char* str_value, char* value);

char* shu_extract_argument(char *word, bool* is_alias);

#endif