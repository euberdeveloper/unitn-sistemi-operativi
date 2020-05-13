#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readline();
char **splitline(char *line, int *size);

int main() {
    char* a = readline();
    int size;
    char** words = splitline(a, &size);

    for (int i = 0; i < size; i++) {
        printf("%s\n", words[i]);
    }

    return 0;
}

char *readline() {
    char* line = NULL;
    size_t size;

    if (getline(&line, &size, stdin) == -1) {
        free(line);
        printf("Fucking error\n");
        exit(1);
    }

    return line;
}

char **splitline(char *line, int *size) {
    const char* delimiters = " \t\r\n\a";
    int index = 0;
    char **words;
    char *token;

    *size = 128;
    words = malloc(*size * sizeof(char*));

    if (!words) {
        printf("Fucking errors\n");
        exit(1);
    }

    for(token = strtok(line, delimiters); token != NULL; token = strtok(NULL, delimiters)) {
        words[index++] = token;

        if (index >= *size) {
            *size *= 2;
            words = realloc(words, *size * sizeof(char*));
            
            if(!words) {
                printf("Fucking errors\n");
                exit(1);
            }
        }
    }

    *size = index;
    words = realloc(words, *size * sizeof(char*));

    return words;
}