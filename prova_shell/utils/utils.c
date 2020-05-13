#include "utils.h"

char *utl_abort(const char* message, int code) {
    fprintf(stderr, "%i:\t%s\n", code, message);
    exit(code);
}

char *utl_readline() {
    char* line = NULL;
    size_t size;

    if (getline(&line, &size, stdin) == -1) {
        free(line);
        utl_abort("Error in getting line", 1);
    }

    return line;
}

char **utl_splitline(char *line, int *size) {
    const char* delimiters = " \t\r\n\a";
    int index = 0;
    char **words;
    char *token;

    *size = 128;
    words = malloc(*size * sizeof(char*));

    if (!words) {
        utl_abort("Error in allocating words", 1);
    }

    for(token = strtok(line, delimiters); token != NULL; token = strtok(NULL, delimiters)) {
        words[index++] = token;

        if (index >= *size) {
            *size *= 2;
            words = realloc(words, *size * sizeof(char*));
            
            if(!words) {
                utl_abort("Error in reallocating words", 1);
            }
        }
    }

    *size = index;
    words = realloc(words, *size * sizeof(char*));

    return words;
}

void utl_free_string_array(char **array, int size) {
    int i;
    
    for (i = 0; i < size; i++) {
        free(array[i]);
    }
    free(array);
}
