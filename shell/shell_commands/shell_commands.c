#include "shell_commands.h"

/* HELPER CONSTANTS */

static const int _SH_INIT_BUFFER = 23;
static const char* _SH_PROMPT_SYMBOL = ">> ";

/* EXPORTED FUNCTIONS */

SH_STATE sh_handle_init(char **words, int n_words) {
    SH_STATE state = SH_CONTINUE;

    bool is_assigned_p_number = false;
	bool is_assigned_q_number = false;
	bool is_assigned_inputs = false;
	bool is_assigned_recursive = false;

    int p_number;
	int q_number;
	int inputs_size = 0;
	int inputs_index = 0;
	char* *inputs = NULL;
	bool recursive = false;

    bool is_alias, finish = false;
    char *argument = NULL;
    int i;

    for (i = 1; i < n_words && !finish; i++) {
        argument = shu_extract_argument(words[i], &is_alias);

        if (argument == NULL) {
            shu_value_without_argument(words[i]);
        }
        else {
            if (strcmp(argument, "p_number") == 0 || (is_alias && strcmp(argument, "n") == 0)) {
			    finish = !shu_check_noval("init", "p_number", n_words, &i);
			    if (!finish) {
			        is_assigned_p_number = true;
			        finish = !shu_get_int_value("init", "p_number", words[i], &p_number)
						|| !shu_check_min_int("init", "p_number", p_number, 1);         
			    }
			}
			else if (strcmp(argument, "q_number") == 0 || (is_alias && strcmp(argument, "m") == 0)) {
			    finish = !shu_check_noval("init", "q_number", n_words, &i);
			    if (!finish) {
			        is_assigned_q_number = true;
			        finish = !shu_get_int_value("init", "q_number", words[i], &q_number)
						|| !shu_check_min_int("init", "q_number", q_number, 1);         
			    }
			}
			else if (strcmp(argument, "inputs") == 0 || (is_alias && strcmp(argument, "i") == 0)) {
			    finish = !shu_check_noval("init", "inputs", n_words, &i);
			    if (!finish) {
			        
			        bool _;
					while (i < n_words && !finish && shu_extract_argument(words[i], &_) == NULL) {
					    if (inputs == NULL) {
					        inputs = malloc(_SH_INIT_BUFFER * sizeof(char*));
					    }
					    else if (inputs_index == inputs_size) {
					        inputs_size *= 2;
					        inputs = realloc(inputs, inputs_size * sizeof(char*));
					    }
					    inputs[inputs_index++] = strdup(words[i]);
					    is_assigned_inputs = true;
					    i++;
					}
					if (i < n_words) {
					    i--;
					}
					finish = !shu_check_noval_array("init", "inputs", is_assigned_inputs);               
			    }
			}
			else if (strcmp(argument, "recursive") == 0 || (is_alias && strcmp(argument, "r") == 0)) {
			    
			    if (!finish) {
			        
			        recursive = true;         
			    }
			}
			else {
			    shu_unknown_argument("init", words[i]);
			}
        }
    }

    if (!finish) {
		finish = !shu_check_required("init", "p_number", is_assigned_p_number);
	}
	if (!finish) {
		finish = !shu_check_required("init", "q_number", is_assigned_q_number);
	}
	if (!finish) {
		finish = !shu_check_required("init", "inputs", is_assigned_inputs);
	}

    if (!finish) {  
        state = init(p_number, q_number, inputs, inputs_index, recursive);
    }

    return state;
}

SH_STATE sh_handle_set(char **words, int n_words) {
    SH_STATE state = SH_CONTINUE;

    bool is_assigned_inputs = false;
	bool is_assigned_recursive = false;
	bool is_assigned_keep = false;

    int p_number= 0;
	int q_number= 0;
	int inputs_size = 0;
	int inputs_index = 0;
	char* *inputs = NULL;
	bool recursive = false;
	bool keep = false;

    bool is_alias, finish = false;
    char *argument = NULL;
    int i;

    for (i = 1; i < n_words && !finish; i++) {
        argument = shu_extract_argument(words[i], &is_alias);

        if (argument == NULL) {
            shu_value_without_argument(words[i]);
        }
        else {
            if (strcmp(argument, "p_number") == 0 || (is_alias && strcmp(argument, "n") == 0)) {
			    finish = !shu_check_noval("set", "p_number", n_words, &i);
			    if (!finish) {
			        
			        finish = !shu_get_int_value("set", "p_number", words[i], &p_number)
						|| !shu_check_min_int("set", "p_number", p_number, 1);         
			    }
			}
			else if (strcmp(argument, "q_number") == 0 || (is_alias && strcmp(argument, "m") == 0)) {
			    finish = !shu_check_noval("set", "q_number", n_words, &i);
			    if (!finish) {
			        
			        finish = !shu_get_int_value("set", "q_number", words[i], &q_number)
						|| !shu_check_min_int("set", "q_number", q_number, 1);         
			    }
			}
			else if (strcmp(argument, "inputs") == 0 || (is_alias && strcmp(argument, "i") == 0)) {
			    finish = !shu_check_noval("set", "inputs", n_words, &i);
			    if (!finish) {
			        
			        bool _;
					while (i < n_words && !finish && shu_extract_argument(words[i], &_) == NULL) {
					    if (inputs == NULL) {
					        inputs = malloc(_SH_INIT_BUFFER * sizeof(char*));
					    }
					    else if (inputs_index == inputs_size) {
					        inputs_size *= 2;
					        inputs = realloc(inputs, inputs_size * sizeof(char*));
					    }
					    inputs[inputs_index++] = strdup(words[i]);
					    is_assigned_inputs = true;
					    i++;
					}
					if (i < n_words) {
					    i--;
					}
					finish = !shu_check_noval_array("set", "inputs", is_assigned_inputs);               
			    }
			}
			else if (strcmp(argument, "recursive") == 0 || (is_alias && strcmp(argument, "r") == 0)) {
			    
			    if (!finish) {
			        
			        recursive = true;         
			    }
			}
			else if (strcmp(argument, "keep") == 0 || (is_alias && strcmp(argument, "k") == 0)) {
			    
			    if (!finish) {
			        
			        keep = true;         
			    }
			}
			else {
			    shu_unknown_argument("set", words[i]);
			}
        }
    }

    
	
	if (!finish) {
		finish = !shu_check_required("set", "inputs", is_assigned_inputs);
	}
	

    if (!finish) {  
        state = set(p_number, q_number, inputs, inputs_index, recursive, keep);
    }

    return state;
}

SH_STATE sh_handle_restart(char **words, int n_words) {
    SH_STATE state = SH_CONTINUE;

    bool is_assigned_inputs = false;
	bool is_assigned_recursive = false;

    int p_number= 0;
	int q_number= 0;
	int inputs_size = 0;
	int inputs_index = 0;
	char* *inputs = NULL;
	bool recursive = false;

    bool is_alias, finish = false;
    char *argument = NULL;
    int i;

    for (i = 1; i < n_words && !finish; i++) {
        argument = shu_extract_argument(words[i], &is_alias);

        if (argument == NULL) {
            shu_value_without_argument(words[i]);
        }
        else {
            if (strcmp(argument, "p_number") == 0 || (is_alias && strcmp(argument, "n") == 0)) {
			    finish = !shu_check_noval("restart", "p_number", n_words, &i);
			    if (!finish) {
			        
			        finish = !shu_get_int_value("restart", "p_number", words[i], &p_number)
						|| !shu_check_min_int("restart", "p_number", p_number, 1);         
			    }
			}
			else if (strcmp(argument, "q_number") == 0 || (is_alias && strcmp(argument, "m") == 0)) {
			    finish = !shu_check_noval("restart", "q_number", n_words, &i);
			    if (!finish) {
			        
			        finish = !shu_get_int_value("restart", "q_number", words[i], &q_number)
						|| !shu_check_min_int("restart", "q_number", q_number, 1);         
			    }
			}
			else if (strcmp(argument, "inputs") == 0 || (is_alias && strcmp(argument, "i") == 0)) {
			    finish = !shu_check_noval("restart", "inputs", n_words, &i);
			    if (!finish) {
			        
			        bool _;
					while (i < n_words && !finish && shu_extract_argument(words[i], &_) == NULL) {
					    if (inputs == NULL) {
					        inputs = malloc(_SH_INIT_BUFFER * sizeof(char*));
					    }
					    else if (inputs_index == inputs_size) {
					        inputs_size *= 2;
					        inputs = realloc(inputs, inputs_size * sizeof(char*));
					    }
					    inputs[inputs_index++] = strdup(words[i]);
					    is_assigned_inputs = true;
					    i++;
					}
					if (i < n_words) {
					    i--;
					}
					finish = !shu_check_noval_array("restart", "inputs", is_assigned_inputs);               
			    }
			}
			else if (strcmp(argument, "recursive") == 0 || (is_alias && strcmp(argument, "r") == 0)) {
			    
			    if (!finish) {
			        
			        recursive = true;         
			    }
			}
			else {
			    shu_unknown_argument("restart", words[i]);
			}
        }
    }

    
	
	if (!finish) {
		finish = !shu_check_required("restart", "inputs", is_assigned_inputs);
	}

    if (!finish) {  
        state = restart(p_number, q_number, inputs, inputs_index, recursive);
    }

    return state;
}

SH_STATE sh_handle_pop(char **words, int n_words) {
    SH_STATE state = SH_CONTINUE;

    bool is_assigned_inputs = false;

    int inputs_size = 0;
	int inputs_index = 0;
	char* *inputs = NULL;

    bool is_alias, finish = false;
    char *argument = NULL;
    int i;

    for (i = 1; i < n_words && !finish; i++) {
        argument = shu_extract_argument(words[i], &is_alias);

        if (argument == NULL) {
            shu_value_without_argument(words[i]);
        }
        else {
            if (strcmp(argument, "inputs") == 0 || (is_alias && strcmp(argument, "i") == 0)) {
			    finish = !shu_check_noval("pop", "inputs", n_words, &i);
			    if (!finish) {
			        
			        bool _;
					while (i < n_words && !finish && shu_extract_argument(words[i], &_) == NULL) {
					    if (inputs == NULL) {
					        inputs = malloc(_SH_INIT_BUFFER * sizeof(char*));
					    }
					    else if (inputs_index == inputs_size) {
					        inputs_size *= 2;
					        inputs = realloc(inputs, inputs_size * sizeof(char*));
					    }
					    inputs[inputs_index++] = strdup(words[i]);
					    is_assigned_inputs = true;
					    i++;
					}
					if (i < n_words) {
					    i--;
					}
					finish = !shu_check_noval_array("pop", "inputs", is_assigned_inputs);               
			    }
			}
			else {
			    shu_unknown_argument("pop", words[i]);
			}
        }
    }

    if (!finish) {
		finish = !shu_check_required("pop", "inputs", is_assigned_inputs);
	}

    if (!finish) {  
        state = pop(inputs, inputs_index);
    }

    return state;
}


SH_STATE sh_parse_command(char **words, int size) {
    SH_STATE state = SH_CONTINUE;

    if (size > 0) {
        char *command = words[0];

        if (strcmp(command, "init") == 0) {
			state = sh_handle_init(words, size);
		}
		else if (strcmp(command, "set") == 0) {
			state = sh_handle_set(words, size);
		}
		else if (strcmp(command, "restart") == 0) {
			state = sh_handle_restart(words, size);
		}
		else if (strcmp(command, "pop") == 0) {
			state = sh_handle_pop(words, size);
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