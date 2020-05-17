#include "text.h"

/* HELPER CONSTANTS */

static const char* _TXT_SPLIT_DELIMITERS = " \t\r\n\a";
static const int _TXT_INITIAL_BUFFER_SIZE = 8;

/* EXPORTED FUNCTIONS */

char *txt_readline() {
    char* line = NULL;
    size_t size;

    if (getline(&line, &size, stdin) == -1) {
        gn_abort("Error in getting line", 1);
    }

    return line;
}

char **txt_splitline(char *line, int *size) {
    int index = 0;
    char **words;
    char *token;

    *size = _TXT_INITIAL_BUFFER_SIZE;
    words = malloc(*size * sizeof(char*));

    if (!words) {
        gn_abort("Error in allocating words", 1);
    }

    for(token = strtok(line, _TXT_SPLIT_DELIMITERS); token != NULL; token = strtok(NULL, _TXT_SPLIT_DELIMITERS)) {
        words[index++] = token;

        if (index >= *size) {
            *size *= 2;
            words = realloc(words, *size * sizeof(char*));
            
            if(!words) {
                gn_abort("Error in reallocating words", 1);
            }
        }
    }

    *size = index;
    words = realloc(words, *size * sizeof(char*));

    return words;
}

void txt_free_string_array(char **array, int size) {
    int i;
    
    for (i = 0; i < size; i++) {
        free(array[i]);
    }
    free(array);
}
