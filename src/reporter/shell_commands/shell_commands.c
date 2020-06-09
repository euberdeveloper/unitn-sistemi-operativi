#include "shell_commands.h"

/* HELPER CONSTANTS */

static const int _SH_INIT_BUFFER = 23;

/* HELPER FUNCTIONS SIGNATURES */

void shu_print_command_help(char *command_name, char *command_description, sh_param_details *details, int details_size);

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
	bool detailed = false;
	bool total = false;
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
			else if (strcmp(argument, "detailed") == 0 || (is_alias && strcmp(argument, "d") == 0)) {
			    
			    if (!finish) {
			        
			        detailed = true;         
			    }
			}
			else if (strcmp(argument, "total") == 0 || (is_alias && strcmp(argument, "t") == 0)) {
			    
			    if (!finish) {
			        
			        total = true;         
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
        state = arguments(is_shell, main_pid, sensitive, percentage, detailed, total, files, files_index);
    }

    return state;
}

SH_STATE sh_handle_show(char **words, int n_words) {
    SH_STATE state = SH_CONTINUE;

    

    bool sensitive = false;
	bool percentage = false;
	bool detailed = false;
	bool total = false;
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
			else if (strcmp(argument, "detailed") == 0 || (is_alias && strcmp(argument, "d") == 0)) {
			    
			    if (!finish) {
			        
			        detailed = true;         
			    }
			}
			else if (strcmp(argument, "total") == 0 || (is_alias && strcmp(argument, "t") == 0)) {
			    
			    if (!finish) {
			        
			        total = true;         
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
        state = show(sensitive, percentage, detailed, total, files, files_index);
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


void sh_help__arguments() {
	sh_param_details details[7];

	details[0].name = "is-shell";
	details[0].alias = NULL;
	details[0].type = "bool";
	details[0].default_value = "false";
	details[0].description = NULL;
	
	details[1].name = "main-pid";
	details[1].alias = NULL;
	details[1].type = "int";
	details[1].default_value = "-1";
	details[1].description = NULL;
	
	details[2].name = "sensitive";
	details[2].alias = "s";
	details[2].type = "bool";
	details[2].default_value = "false";
	details[2].description = NULL;
	
	details[3].name = "percentage";
	details[3].alias = "p";
	details[3].type = "bool";
	details[3].default_value = "false";
	details[3].description = NULL;
	
	details[4].name = "detailed";
	details[4].alias = "d";
	details[4].type = "bool";
	details[4].default_value = "false";
	details[4].description = NULL;
	
	details[5].name = "total";
	details[5].alias = "t";
	details[5].type = "bool";
	details[5].default_value = "false";
	details[5].description = NULL;
	
	details[6].name = "files";
	details[6].alias = "f";
	details[6].type = "array<char*>";
	details[6].default_value = "NULL";
	details[6].description = NULL;

	shu_print_command_help("_arguments", NULL, details, 7);
}
void sh_help_show() {
	sh_param_details details[5];

	details[0].name = "sensitive";
	details[0].alias = "s";
	details[0].type = "bool";
	details[0].default_value = "false";
	details[0].description = NULL;
	
	details[1].name = "percentage";
	details[1].alias = "p";
	details[1].type = "bool";
	details[1].default_value = "false";
	details[1].description = NULL;
	
	details[2].name = "detailed";
	details[2].alias = "d";
	details[2].type = "bool";
	details[2].default_value = "false";
	details[2].description = NULL;
	
	details[3].name = "total";
	details[3].alias = "t";
	details[3].type = "bool";
	details[3].default_value = "false";
	details[3].description = NULL;
	
	details[4].name = "files";
	details[4].alias = "f";
	details[4].type = "array<char*>";
	details[4].default_value = "NULL";
	details[4].description = NULL;

	shu_print_command_help("show", NULL, details, 5);
}
void sh_help_quit() {
	

	

	shu_print_command_help("quit", NULL, NULL, 0);
}

void sh_help(char **words, int size) {
	if (size == 1) {
		sh_help__arguments();
		sh_help_show();
		sh_help_quit();
	}
	else {
        char* command = words[1];

		int i;
		for (i = 2; i < size; i++) {
			shu_help_misplaced_argument(words[i]);
		}

		if (strcmp(command, "_arguments") == 0) {
			sh_help__arguments();
		}
		else if (strcmp(command, "show") == 0) {
			sh_help_show();
		}
		else if (strcmp(command, "quit") == 0) {
			sh_help_quit();
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

/* HELPER FUNCTIONS DEFINITIONS */

void shu_print_command_help(char *command_name, char *command_description, sh_param_details *details, int details_size) {
  printf("%-15s", command_name);
  if (command_description != NULL) {
    printf("%s\n", command_description);
  } 
  else {
    printf("\n");
  }
  int i;
  for (i = 0; i < details_size; i++) {
    printf("--%-13s", details[i].name);
    
    printf("-%-9s", details[i].alias);
    printf("%-15s", details[i].type);
    if(details[i].default_value != NULL) {
      printf("default: %-11s", details[i].default_value);
    } 
    else {
      printf("%-20s", "required");
    }
    if(details[i].description != NULL) {
      printf("%-80s\n", details[i].description);
    } 
    else {
      printf("%-80s\n", "no description");
    }
  }
  printf("\n");
}