#include "shell_commands.h"

/* HELPER CONSTANTS */

static const int _SH_INIT_BUFFER = 23;
static const char* _SH_PROMPT_SYMBOL = ">> ";

/* EXPORTED FUNCTIONS */

SH_STATE sh_handle_add(char **words, int n_words) {
    SH_STATE state = SH_CONTINUE;

    bool is_assigned_first = false;

    int first;
    int second = 10;

    bool is_alias, finish = false;
    char *argument = NULL;
    int i;

    for (i = 1; i < n_words && !finish; i++) {
        argument = shu_extract_argument(words[i], &is_alias);

        if (argument == NULL) {
            shu_value_without_argument(words[i]);
        }
        else {
            if (strcmp(argument, "first") == 0) {
                finish = !shu_check_noval("add", "first", n_words, &i);
                if (!finish) {
                    is_assigned_first = true;
                    finish = !shu_get_int_value("add", "first", words[i], &first) 
                        || !shu_check_min_int("add", "first", first, 0) 
                        || !shu_check_max_int("add", "first", first, 5);
                    
                }
            }
            else if (strcmp(argument, "second") == 0 || (is_alias && strcmp(argument, "s") == 0)) {
               finish = !shu_check_noval("add", "second", n_words, &i);
                if (!finish) {
                    finish = !shu_get_int_value("add", "second", words[i], &second);
                }
            }
            else {
                shu_unknown_argument("add", words[i]);
            }
        }
    }

    if (!finish) {
        finish = !shu_check_required("add", "first", is_assigned_first);
    }


    if (!finish) {  
        state = add_shit(first, second);
    }

    return state;
}

SH_STATE sh_handle_acc(char **words, int n_words) {
    SH_STATE state = SH_CONTINUE;

    bool is_assigned_numbers = false;

    int numbers_size = 0, 
        numbers_index = 0, 
        *numbers = NULL;

    bool is_alias, finish = false;
    char *argument = NULL;
    int i;

    for (i = 1; i < n_words && !finish; i++) {
        argument = shu_extract_argument(words[i], &is_alias);

        if (argument == NULL) {
            shu_value_without_argument(words[i]);
        }
        else {
            if (strcmp(argument, "numbers") == 0 || (is_alias && strcmp(argument, "n") == 0)) {
                finish = !shu_check_noval("acc", "numbers", n_words, &i);
                if (!finish) {
                    is_assigned_numbers = true;

                    bool _;
                    while (i < n_words && !finish && shu_extract_argument(words[i], &_) == NULL) {
                        if (numbers == NULL) {
                            numbers = malloc(_SH_INIT_BUFFER * sizeof(int));
                        }
                        else if (numbers_index == numbers_size) {
                            numbers_size *= 2;
                            numbers = realloc(numbers, numbers_size * sizeof(int));
                        }
                        finish = !shu_get_int_value("acc", "numbers", words[i], &numbers[numbers_index++]);
                        is_assigned_numbers = true;
                        i++;
                    }
                    if (i < n_words)
                    {
                        i--;
                    }    
                    finish = !shu_check_noval_array("acc", "numbers", is_assigned_numbers);                
                }
            }
            else {
                shu_unknown_argument("acc", words[i]);
            }
        }
    }

    if (!finish) {
        finish = !shu_check_required("acc", "numbers", is_assigned_numbers);
    }

    if (!finish) {  
        state = acc(numbers, numbers_index);
    }

    return state;
}


SH_STATE sh_parse_command(char **words, int size) {
    SH_STATE state = SH_CONTINUE;

    if (size > 0) {
        char *command = words[0];

        if (strcmp(command, "add") == 0) {
            state = sh_handle_add(words, size);
        }
        else if (strcmp(command, "acc") == 0) {
            state = sh_handle_acc(words, size);
        }
        else {
            shu_unknown_command(command);
            state = SH_CONTINUE;
        }
    }

    return state;
}

void sh_loop() {
    SH_STATE state = SH_CONTINUE;

    int n_words;
    char *command, **words;

    while (state != SH_EXIT) {
        printf("%s", _SH_PROMPT_SYMBOL);
        command = txt_readline();
        words = txt_splitline(command, &n_words);
        state = sh_parse_command(words, n_words);

        free(command);
        txt_free_string_array(words, n_words);
    }
}