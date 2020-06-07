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

    

    bool is_shell = false;
	int main_pid = -1;
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
            shu_value_without_argument(words[i], false);
        }
        else {
            if (strcmp(argument, "is-shell") == 0) {
			    
			    if (!finish) {
			        
			        is_shell = true;         
			    }
			}
			else if (strcmp(argument, "main-pid") == 0) {
			    finish = !shu_check_noval("_arguments", "main-pid", n_words, &i, false);
			    if (!finish) {
			        
			        finish = !shu_get_int_value("_arguments", "main-pid", words[i], &main_pid, false);         
			    }
			}
			else if (strcmp(argument, "sensitive") == 0 || (is_alias && strcmp(argument, "s") == 0)) {
			    
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
			    finish = !shu_check_noval("_arguments", "files", n_words, &i, false);
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
				shu_unknown_argument("_arguments", words[i], false);
			}
        }
    }

    
	
	
	
	
	

    if (!finish) {  
        state = arguments(is_shell, main_pid, sensitive, percentage, realtime, detailed, files, files_index);
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


SH_STATE sh_parse_command(char **words, int size) {
    SH_STATE state = SH_CONTINUE;

    if (size > 0) {
        char *command = words[0];

        if (strcmp(command, "show") == 0) {
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
	
	int history_size = 8, history_index = 0, temp;
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
			history = realloc(history, history_size);
		}
		temp = strlen(command);
		history[history_index] = malloc(temp * sizeof(char));
		strncpy(history[history_index], command, temp - 1);
		history[history_index][temp - 1] = '\0';
		history_index++;

        words = txt_splitline(command, &n_words);
        state = sh_parse_command(words, n_words);

        free(command);
        txt_free_string_array(words, n_words);
    }
}