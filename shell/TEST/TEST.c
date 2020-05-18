#include "TEST.h"

/* HELPER CONSTANTS */

static const int _SH_INIT_BUFFER = 23;
static const char* _SH_PROMPT_SYMBOL = ">> ";

/* EXPORTED FUNCTIONS */

SH_STATE sh_handle_add(char **words, int n_words) {
    SH_STATE state = SH_CONTINUE;

    bool is_assigned_first;

    

    bool is_alias, finish = false;
    char *argument = NULL;
    int i;

    for (i = 1; i < n_words && !finish; i++) {
        argument = shu_extract_argument(words[i], &is_alias);

        if (argument == NULL) {
            shu_value_without_argument(words[i]);
        }
        else {
            
        }
    }

    

    if (!finish) {  
        state = ;
    }

    return state;
}

SH_STATE sh_handle_acc(char **words, int n_words) {
    SH_STATE state = SH_CONTINUE;

    bool is_assigned_numbers;

    

    bool is_alias, finish = false;
    char *argument = NULL;
    int i;

    for (i = 1; i < n_words && !finish; i++) {
        argument = shu_extract_argument(words[i], &is_alias);

        if (argument == NULL) {
            shu_value_without_argument(words[i]);
        }
        else {
            
        }
    }

    

    if (!finish) {  
        state = ;
    }

    return state;
}


SH_STATE sh_parse_command(char **words, int size) {
    SH_STATE state = SH_CONTINUE;

    if (size > 0) {
        char *command = words[0];

        if (strcmp(command, add) == 0) {
		state = sh_handle_add(words, size);
	}
	else if (strcmp(command, acc) == 0) {
		state = sh_handle_add(words, size);
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