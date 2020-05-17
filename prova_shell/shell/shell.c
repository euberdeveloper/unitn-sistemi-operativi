#include "shell.h"

void sh_loop() {
    STATE state = CONTINUE;

    int n_words;
    char *command, **words;

    while (state != EXIT) {
        command = utl_readline();
        words = utl_splitline(command, &n_words);
        state = sh_parse_command(words, n_words);
    }

    free(command);
    utl_free_string_array(words, n_words);
}

STATE sh_unknown_command(char* command) {
    printf("unknown command: %s\n", command);
    return CONTINUE;
}

void sh_argument_noval(const char* command, const char* argument) {
    printf("%s: argument %s has no value\n", command, argument);
}

void sh_argument_required(const char* command, const char* argument) {
    printf("%s: argument %s is required\n", command, argument);
}

bool sh_argument_min(const char* command, const char* argument, int value, int min) {
    bool result = true; 

    if (value < min) {
        printf("%s: argument %s is %i but must be greater or equal than %i\n", command, argument, value, min);
        result = false;
    }

    return result;
}

bool sh_argument_max(const char* command, const char* argument, int value, int max) {
    bool result = true; 

    if (value > max) {
        printf("%s: argument %s is %i but must be lower or equal than %i\n", command, argument, value, max);
        result = false;
    }

    return result;
}

char *sh_extract_argument(char *word, bool* is_alias) {
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