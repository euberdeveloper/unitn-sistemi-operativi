#include "shell_commands.h"

/* HELPER CONSTANTS */

static const int _SH_INIT_BUFFER = 23;

/* EXPORTED VARIABLES */

char *sh_last_command;
char *sh_prompt_symbol = ">> ";
bool sh_use_advanced_terminal = true;

/* EXPORTED FUNCTIONS */

SH_STATE sh_handle__arguments(char **words, int n_words) {
    SH_STATE state = SH_CONTINUE;

    

    int p_number = 3;
	int q_number = 4;
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
            shu_value_without_argument(words[i], false);
        }
        else {
            if (strcmp(argument, "p-number") == 0 || (is_alias && strcmp(argument, "n") == 0)) {
			    finish = !shu_check_noval("_arguments", "p-number", n_words, &i, false);
			    if (!finish) {
			        
			        finish = !shu_get_int_value("_arguments", "p-number", words[i], &p_number, false)
						|| !shu_check_min_int("_arguments", "p-number", p_number, 1, false);         
			    }
			}
			else if (strcmp(argument, "q-number") == 0 || (is_alias && strcmp(argument, "m") == 0)) {
			    finish = !shu_check_noval("_arguments", "q-number", n_words, &i, false);
			    if (!finish) {
			        
			        finish = !shu_get_int_value("_arguments", "q-number", words[i], &q_number, false)
						|| !shu_check_min_int("_arguments", "q-number", q_number, 1, false);         
			    }
			}
			else if (strcmp(argument, "inputs") == 0 || (is_alias && strcmp(argument, "i") == 0)) {
			    finish = !shu_check_noval("_arguments", "inputs", n_words, &i, false);
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
					    
					    i++;
					}
					if (i < n_words) {
					    i--;
					}
					          
			    }
			}
			else if (strcmp(argument, "recursive") == 0 || (is_alias && strcmp(argument, "r") == 0)) {
			    
			    if (!finish) {
			        
			        recursive = true;         
			    }
			}
			else {
				shu_unknown_argument("_arguments", words[i], false);
			}
        }
    }

    
	
	

    if (!finish) {  
        state = arguments(p_number, q_number, inputs, inputs_index, recursive);
    }

    return state;
}

SH_STATE sh_handle_init(char **words, int n_words) {
    SH_STATE state = SH_CONTINUE;

    bool is_assigned_inputs = false;

    int p_number = 3;
	int q_number = 4;
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
            shu_value_without_argument(words[i], true);
        }
        else {
            if (strcmp(argument, "p-number") == 0 || (is_alias && strcmp(argument, "n") == 0)) {
			    finish = !shu_check_noval("init", "p-number", n_words, &i, true);
			    if (!finish) {
			        
			        finish = !shu_get_int_value("init", "p-number", words[i], &p_number, true)
						|| !shu_check_min_int("init", "p-number", p_number, 1, true);         
			    }
			}
			else if (strcmp(argument, "q-number") == 0 || (is_alias && strcmp(argument, "m") == 0)) {
			    finish = !shu_check_noval("init", "q-number", n_words, &i, true);
			    if (!finish) {
			        
			        finish = !shu_get_int_value("init", "q-number", words[i], &q_number, true)
						|| !shu_check_min_int("init", "q-number", q_number, 1, true);         
			    }
			}
			else if (strcmp(argument, "inputs") == 0 || (is_alias && strcmp(argument, "i") == 0)) {
			    finish = !shu_check_noval("init", "inputs", n_words, &i, true);
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
					finish = !shu_check_noval_array("init", "inputs", is_assigned_inputs, true);          
			    }
			}
			else if (strcmp(argument, "recursive") == 0 || (is_alias && strcmp(argument, "r") == 0)) {
			    
			    if (!finish) {
			        
			        recursive = true;         
			    }
			}
			else {
				shu_unknown_argument("init", words[i], true);
			}
        }
    }

    
	
	if (!finish) {
		finish = !shu_check_required("init", "inputs", is_assigned_inputs, true);
	}

    if (!finish) {  
        state = init(p_number, q_number, inputs, inputs_index, recursive);
    }

    return state;
}

SH_STATE sh_handle_set(char **words, int n_words) {
    SH_STATE state = SH_CONTINUE;

    

    int p_number = 0;
	int q_number = 0;
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
            shu_value_without_argument(words[i], true);
        }
        else {
            if (strcmp(argument, "p-number") == 0 || (is_alias && strcmp(argument, "n") == 0)) {
			    finish = !shu_check_noval("set", "p-number", n_words, &i, true);
			    if (!finish) {
			        
			        finish = !shu_get_int_value("set", "p-number", words[i], &p_number, true)
						|| !shu_check_min_int("set", "p-number", p_number, 1, true);         
			    }
			}
			else if (strcmp(argument, "q-number") == 0 || (is_alias && strcmp(argument, "m") == 0)) {
			    finish = !shu_check_noval("set", "q-number", n_words, &i, true);
			    if (!finish) {
			        
			        finish = !shu_get_int_value("set", "q-number", words[i], &q_number, true)
						|| !shu_check_min_int("set", "q-number", q_number, 1, true);         
			    }
			}
			else if (strcmp(argument, "inputs") == 0 || (is_alias && strcmp(argument, "i") == 0)) {
			    finish = !shu_check_noval("set", "inputs", n_words, &i, true);
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
					    
					    i++;
					}
					if (i < n_words) {
					    i--;
					}
					          
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
				shu_unknown_argument("set", words[i], true);
			}
        }
    }

    
	
	
	

    if (!finish) {  
        state = set(p_number, q_number, inputs, inputs_index, recursive, keep);
    }

    return state;
}

SH_STATE sh_handle_restart(char **words, int n_words) {
    SH_STATE state = SH_CONTINUE;

    bool is_assigned_inputs = false;

    int p_number = 0;
	int q_number = 0;
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
            shu_value_without_argument(words[i], true);
        }
        else {
            if (strcmp(argument, "p-number") == 0 || (is_alias && strcmp(argument, "n") == 0)) {
			    finish = !shu_check_noval("restart", "p-number", n_words, &i, true);
			    if (!finish) {
			        
			        finish = !shu_get_int_value("restart", "p-number", words[i], &p_number, true)
						|| !shu_check_min_int("restart", "p-number", p_number, 1, true);         
			    }
			}
			else if (strcmp(argument, "q-number") == 0 || (is_alias && strcmp(argument, "m") == 0)) {
			    finish = !shu_check_noval("restart", "q-number", n_words, &i, true);
			    if (!finish) {
			        
			        finish = !shu_get_int_value("restart", "q-number", words[i], &q_number, true)
						|| !shu_check_min_int("restart", "q-number", q_number, 1, true);         
			    }
			}
			else if (strcmp(argument, "inputs") == 0 || (is_alias && strcmp(argument, "i") == 0)) {
			    finish = !shu_check_noval("restart", "inputs", n_words, &i, true);
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
					finish = !shu_check_noval_array("restart", "inputs", is_assigned_inputs, true);          
			    }
			}
			else if (strcmp(argument, "recursive") == 0 || (is_alias && strcmp(argument, "r") == 0)) {
			    
			    if (!finish) {
			        
			        recursive = true;         
			    }
			}
			else {
				shu_unknown_argument("restart", words[i], true);
			}
        }
    }

    
	
	if (!finish) {
		finish = !shu_check_required("restart", "inputs", is_assigned_inputs, true);
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
            shu_value_without_argument(words[i], true);
        }
        else {
            if (strcmp(argument, "inputs") == 0 || (is_alias && strcmp(argument, "i") == 0)) {
			    finish = !shu_check_noval("pop", "inputs", n_words, &i, true);
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
					finish = !shu_check_noval_array("pop", "inputs", is_assigned_inputs, true);          
			    }
			}
			else {
				shu_unknown_argument("pop", words[i], true);
			}
        }
    }

    if (!finish) {
		finish = !shu_check_required("pop", "inputs", is_assigned_inputs, true);
	}

    if (!finish) {  
        state = pop(inputs, inputs_index);
    }

    return state;
}

SH_STATE sh_handle_status(char **words, int n_words) {
    SH_STATE state = SH_CONTINUE;

    

    

    bool is_alias, finish = false;
    char *argument = NULL;
    int i;

    for (i = 1; i < n_words && !finish; i++) {
        argument = shu_extract_argument(words[i], &is_alias);

        if (argument == NULL) {
            shu_value_without_argument(words[i], true);
        }
        else {
            
			shu_unknown_argument("status", words[i], true);
        }
    }

    

    if (!finish) {  
        state = status();
    }

    return state;
}

SH_STATE sh_handle_stop(char **words, int n_words) {
    SH_STATE state = SH_CONTINUE;

    

    

    bool is_alias, finish = false;
    char *argument = NULL;
    int i;

    for (i = 1; i < n_words && !finish; i++) {
        argument = shu_extract_argument(words[i], &is_alias);

        if (argument == NULL) {
            shu_value_without_argument(words[i], true);
        }
        else {
            
			shu_unknown_argument("stop", words[i], true);
        }
    }

    

    if (!finish) {  
        state = stop();
    }

    return state;
}

SH_STATE sh_handle_show(char **words, int n_words) {
    SH_STATE state = SH_CONTINUE;

    

    bool sensitive = false;
	bool percentage = false;
	bool realtime = false;
	bool detailed = false;
	int files_size = 0;
	int files_index = 0;
	char* *files = NULL;

    bool is_alias, finish = false;
    char *argument = NULL;
    int i;

    for (i = 1; i < n_words && !finish; i++) {
        argument = shu_extract_argument(words[i], &is_alias);

        if (argument == NULL) {
            shu_value_without_argument(words[i], true);
        }
        else {
            if (strcmp(argument, "sensitive") == 0 || (is_alias && strcmp(argument, "s") == 0)) {
			    
			    if (!finish) {
			        
			        sensitive = true;         
			    }
			}
			else if (strcmp(argument, "percentage") == 0 || (is_alias && strcmp(argument, "p") == 0)) {
			    
			    if (!finish) {
			        
			        percentage = true;         
			    }
			}
			else if (strcmp(argument, "realtime") == 0 || (is_alias && strcmp(argument, "r") == 0)) {
			    
			    if (!finish) {
			        
			        realtime = true;         
			    }
			}
			else if (strcmp(argument, "detailed") == 0 || (is_alias && strcmp(argument, "d") == 0)) {
			    
			    if (!finish) {
			        
			        detailed = true;         
			    }
			}
			else if (strcmp(argument, "files") == 0 || (is_alias && strcmp(argument, "f") == 0)) {
			    finish = !shu_check_noval("show", "files", n_words, &i, true);
			    if (!finish) {
			        
			        bool _;
					while (i < n_words && !finish && shu_extract_argument(words[i], &_) == NULL) {
					    if (files == NULL) {
					        files = malloc(_SH_INIT_BUFFER * sizeof(char*));
					    }
					    else if (files_index == files_size) {
					        files_size *= 2;
					        files = realloc(files, files_size * sizeof(char*));
					    }
					    files[files_index++] = strdup(words[i]);
					    
					    i++;
					}
					if (i < n_words) {
					    i--;
					}
					          
			    }
			}
			else {
				shu_unknown_argument("show", words[i], true);
			}
        }
    }

    
	
	
	

    if (!finish) {  
        state = show(sensitive, percentage, realtime, detailed, files, files_index);
    }

    return state;
}

SH_STATE sh_handle_quit(char **words, int n_words) {
    SH_STATE state = SH_CONTINUE;

    

    

    bool is_alias, finish = false;
    char *argument = NULL;
    int i;

    for (i = 1; i < n_words && !finish; i++) {
        argument = shu_extract_argument(words[i], &is_alias);

        if (argument == NULL) {
            shu_value_without_argument(words[i], true);
        }
        else {
            
			shu_unknown_argument("quit", words[i], true);
        }
    }

    

    if (!finish) {  
        state = quit();
    }

    return state;
}

void sh_help_init() {//todo
	sh_param_details details[4];

	details[0].name = "p-number";
	details[0].alias = "n";
	details[0].type = "int";
	details[0].default_value = "3";
	details[0].description = "The number of P processes. It must be at least 1.";

	details[1].name = "q-number";
	details[1].alias = "m";
	details[1].type = "int";
	details[1].default_value = "4";
	details[1].description = "The number of Q processes. It must be at least 1.";

	details[2].name = "inputs";
	details[2].alias = "i";
	details[2].type = "array<char*>";
	details[2].default_value = NULL;
	details[2].description = "The inputs as file or directory paths.";

	details[3].name = "recursive";
	details[3].alias = "r";
	details[3].type = "bool";
	details[3].default_value = "false";
	details[3].description = "If the directories will be read recusively.";

	//shu_print_command_help("init", "init description", &details, 4);

	puts("init");
}
void sh_help_set() { //todo
	sh_param_details details[5];

	details[0].name = "p-number";
	details[0].alias = "n";
	details[0].type = "int";
	details[0].default_value = "0";
	details[0].description = "The number of P processes. It must be at least 1.";

	details[1].name = "q-number";
	details[1].alias = "m";
	details[1].type = "int";
	details[1].default_value = "0";
	details[1].description = "The number of Q processes. It must be at least 1.";

	details[2].name = "inputs";
	details[2].alias = "i";
	details[2].type = "array<char*>";
	details[2].default_value = "NULL";
	details[2].description = "The inputs as file or directory paths.";

	details[3].name = "recursive";
	details[3].alias = "r";
	details[3].type = "bool";
	details[3].default_value = "false";
	details[3].description = "If the directories will be read recusively.";

	details[4].name = "keep";
	details[4].alias = "k";
	details[4].type = "bool";
	details[4].default_value = "false";
	details[4].description = "If instead of reset the precedent inputs the new inputs will be only added.";

	//shu_print_command_help("set", "set description", &details, 5);
	puts("set");
}

void sh_help(char **words, int size) {//todo
	if (size == 1) {
		sh_help_init();
		sh_help_set();
	}
	else {
		int i;
		for (i = 2; i < size; i++) {
			shu_help_misplaced_argument(words[i]);
		}

		if (strcmp(words[1], "init") == 0) {
			sh_help_init();
		}
		else if (strcmp(words[1], "set") == 0) {
			sh_help_set();
		}
		else {
			shu_help_unknown_command(words[1]);
		}
	}
}


SH_STATE sh_parse_command(char **words, int size) {
    SH_STATE state = SH_CONTINUE;

    if (size > 0) {
        char *command = words[0];

		if (strcmp(command, "help") == 0)  {
			sh_help(words, size);
		}
        else if (strcmp(command, "init") == 0) {
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
		else if (strcmp(command, "status") == 0) {
			state = sh_handle_status(words, size);
		}
		else if (strcmp(command, "stop") == 0) {
			state = sh_handle_stop(words, size);
		}
		else if (strcmp(command, "show") == 0) {
			state = sh_handle_show(words, size);
		}
		else if (strcmp(command, "quit") == 0) {
			state = sh_handle_quit(words, size);
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
	
	int history_size = 8, history_index = 0, length;
	char** history = malloc(history_size * sizeof(char*));

    sh_last_command = strdup("");

    while (state != SH_EXIT) {
        printf("%s", sh_prompt_symbol);
        fflush(stdout);

        command = sh_use_advanced_terminal 
            ? txt_readline_special(history, history_index)
            : txt_readline();

        free(sh_last_command);
        sh_last_command = strdup(command);

		if (history_index == history_size) {
			history_size *= 2;
			history = realloc(history, history_size * sizeof(char*));
		}

		history[history_index] = strdup(command);
		history[history_index][strlen(command) - 1] = '\0';
		history_index++;

        words = txt_splitline(command, &n_words);
        state = sh_parse_command(words, n_words);

        free(command);
        txt_free_string_array(words, n_words);
    }
}