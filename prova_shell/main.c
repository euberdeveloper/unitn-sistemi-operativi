#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/utils.h"

int main() {
    sh_loop();
    return 0;
}



STATE sh_command_add(char** words, int size) {
    // Required arguments
    bool argument_first = false;

    // Arguments values
    int first;
    int second = 10;

    bool is_alias;
    char* argument = NULL;
    int i;

    for (i = 1; i < size; i++) {
        argument = sh_extract_argument(words[i], &is_alias);

        if (argument != NULL) {
            if (strcmp(argument, "first") == 0) {
                if (++i >= size) {
                    sh_argument_noval("add", "first");
                    free(argument);
                    return CONTINUE;
                }
                else {
                    argument_first = true;
                    first = atoi(words[i]);
                    if (!sh_argument_min("add", "first", first, 0)) {
                        free(argument);
                        return CONTINUE;
                    }
                    if (!sh_argument_max("add", "first", first, 5)) {
                        free(argument);
                        return CONTINUE;
                    }
                }
            }
            else if (strcmp(argument, "second") == 0 || (is_alias && strcmp(argument, "s") == 0)) {
                if (++i >= size) {
                    sh_argument_noval("add", "second");
                    free(argument);
                    return CONTINUE;
                }
                else {
                    second = atoi(words[i]);
                }
            }
        }
    }

    // check required arguments
    if (!argument_first) {
        sh_argument_required("add", "first");
        if (argument != NULL) {
            free(argument);
        }
        return CONTINUE;
    }

    // execute function
    //add_shit(first, second);
}

STATE sh_command_acc(char** words, int size) {
    // Required arguments
    bool argument_numbers = false;

    // Arguments values
    int numbers_size = 8;
    int numbers_index = 0;
    int* numbers = malloc(numbers_size * sizeof(int));

    bool is_alias;
    char* argument = NULL;
    int i;

    for (i = 1; i < size; i++) {
        argument = sh_extract_argument(words[i], &is_alias);

        if (argument != NULL) {
            if (strcmp(argument, "numbers") == 0 || (is_alias && strcmp(argument, "n") == 0)) {
                if (++i >= size) {
                    sh_argument_noval("acc", "numbers");
                    free(argument);
                    return CONTINUE;
                }
                else {
                    bool placeholder;
                    while (i < size && sh_extract_argument(words[i], &placeholder) == NULL) {
                        numbers[numbers_index++] = atoi(words[i]);
                        if (numbers_index == numbers_size) {
                            numbers_size *= 2;
                            numbers = realloc(numbers, numbers_size * sizeof(int));
                        }
                        argument_numbers = true;
                        i++;
                    }

                    if (i < size) {
                        i--;
                    }
                }
            }
        }
    }

    // check required arguments
    if (!argument_numbers) {
        sh_argument_required("acc", "numbers");
        return CONTINUE;
    }
 
    printf("[");
    for (int i = 0; i < numbers_index; i++) {
        printf("\t%i", numbers[i]);
    }
    printf("\t]\n");
    // execute function
    //acc(numbers, numbers_index);
}