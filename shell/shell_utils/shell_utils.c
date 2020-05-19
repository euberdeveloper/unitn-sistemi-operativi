#include "shell_utils.h"

void shu_unknown_command(char* command) {
    char *message;
    asprintf(&message, "unknown command %s", command);
    log_error_del_ctx(message, strdup("SHELL"));
}

void shu_unknown_argument(char *command, char* argument) {
    char *message;
    asprintf(&message, "command %s: unknown argument %s", command, argument);
    log_warning_del_ctx(message, strdup("SHELL"));
}

void shu_value_without_argument(char* value) {
    char *message;
    asprintf(&message, "value without argument, %s ignored", value);
    log_warning_del_ctx(message, strdup("SHELL"));
}

bool shu_check_noval(const char *command, const char *argument, int size, int *i) {
    bool result = true;
    
    if (++(*i) >= size) {
        char* message;

        result = false;
        asprintf(&message, "%s: argument %s has no value\n", command, argument);
        log_error_del_ctx(message, strdup("SHELL"));
    }

    return result;
}

bool shu_check_noval_array(const char *command, const char *argument, bool is_assigned) {    
    if (!is_assigned) {
        char* message;
        asprintf(&message, "%s: argument %s can not be an empty array\n", command, argument);
        log_error_del_ctx(message, strdup("SHELL"));
    }

    return is_assigned;
}

bool shu_check_required(const char* command, const char* argument, bool is_assigned) {
    if (!is_assigned) {
        char *message;
        asprintf(&message, "%s: argument %s is required\n", command, argument);
        log_error_del_ctx(message, strdup("SHELL"));
    }

    return is_assigned;
}

bool shu_check_min_int(const char* command, const char* argument, int value, int min) {
    bool result = true; 

    if (value < min) {
        char *message;
        asprintf(&message, "%s: argument %s is %i but must be greater or equal than %i\n", command, argument, value, min);
        log_error_del_ctx(message, strdup("SHELL"));
        result = false;
    }

    return result;
}
bool shu_check_max_int(const char* command, const char* argument, int value, int max) {
    bool result = true; 

    if (value > max) {
        char *message;
        asprintf(&message, "%s: argument %s is %i but must be lower or equal than %i\n", command, argument, value, max);
        log_error_del_ctx(message, strdup("SHELL"));
        result = false;
    }

    return result;
}
bool shu_check_min_long(const char* command, const char* argument, long value, long min) {
    bool result = true; 

    if (value < min) {
        char *message;
        asprintf(&message, "%s: argument %s is %li but must be greater or equal than %li\n", command, argument, value, min);
        log_error_del_ctx(message, strdup("SHELL"));
        result = false;
    }

    return result;
}
bool shu_check_max_long(const char* command, const char* argument, long value, long max) {
    bool result = true; 

    if (value > max) {
        char *message;
        asprintf(&message, "%s: argument %s is %li but must be lower or equal than %li\n", command, argument, value, max);
        log_error_del_ctx(message, strdup("SHELL"));
        result = false;
    }

    return result;
}
bool shu_check_min_float(const char* command, const char* argument, float value, float min) {
    bool result = true; 

    if (value < min) {
        char *message;
        asprintf(&message, "%s: argument %s is %f but must be greater or equal than %f\n", command, argument, value, min);
        log_error_del_ctx(message, strdup("SHELL"));
        result = false;
    }

    return result;
}
bool shu_check_max_float(const char* command, const char* argument, float value, float max) {
    bool result = true; 

    if (value > max) {
        char *message;
        asprintf(&message, "%s: argument %s is %f but must be lower or equal than %f\n", command, argument, value, max);
        log_error_del_ctx(message, strdup("SHELL"));
        result = false;
    }

    return result;
}
bool shu_check_min_double(const char* command, const char* argument, double value, double min) {
    bool result = true; 

    if (value < min) {
        char *message;
        asprintf(&message, "%s: argument %s is %f but must be greater or equal than %f\n", command, argument, value, min);
        log_error_del_ctx(message, strdup("SHELL"));
        result = false;
    }

    return result;
}
bool shu_check_max_double(const char* command, const char* argument, double value, double max) {
    bool result = true; 

    if (value > max) {
        char *message;
        asprintf(&message, "%s: argument %s is %f but must be lower or equal than %f\n", command, argument, value, max);
        log_error_del_ctx(message, strdup("SHELL"));
        result = false;
    }

    return result;
}

bool shu_get_int_value(const char *command, const char *argument, char* str_value, int* value) {
    *value = atoi(str_value);
    return true;
}

bool shu_get_long_value(const char *command, const char *argument, char* str_value, long* value) {
    *value = atol(str_value);
    return true;
}

bool shu_get_float_value(const char *command, const char *argument, char* str_value, float* value) {
    *value = (float) atof(str_value);
    return true;
}

bool shu_get_double_value(const char *command, const char *argument, char* str_value, double* value) {
    *value = atof(str_value);
    return true;
}

bool shu_get_char_value(const char *command, const char *argument, char* str_value, char* value) {
    bool result;

    if (strlen(str_value) == 1) {
        *value = str_value[0];
        result = true;
    }
    else {
        char *message;
        asprintf(&message, "%s: argument %s has not a valid char value\n", command, argument, value);
        log_error_del_ctx(message, strdup("SHELL"));
        result = false;
    }

    return result;
}

char* shu_extract_argument(char *word, bool* is_alias) {
    const int len = strlen(word);
    char* argument = NULL;

    if (len > 2) {
        if (word[0] == '-' && word[1] == '-') {
            *is_alias = false;
            asprintf(&argument, "%.*s", len - 2, word + 2);
        }
    } 
    else if (len == 2) {
        if (word[0] == '-') {
            *is_alias = true;
            asprintf(&argument, "%c", word[1]);
        }
    } 
    
    return argument;    
}
