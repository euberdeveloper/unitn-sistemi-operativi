STATE sh_command_add(char** words, int size) {
        bool argument_first = false;


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
else if (strcmp(argument, "second") == 0 || (is_alias && strcmp(argument, "s") == 0)) {
if (++i >= size) {
        sh_argument_noval("add", "second");
        free(argument);
        return CONTINUE;
    }
second = atoi(words[i]);
}

            }
        }

        
            if (!argument_numbers) {
                sh_argument_required("add", "first");
                return CONTINUE;
            }
            

        add_shit(first, second);
}STATE sh_command_acc(char** words, int size) {
        bool argument_numbers = false;


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
bool placeholder;
    while (i < size && sh_extract_argument(words[i], &placeholder) == NULL) {
        numbers[numbers_index++] = atoi(words[i]);
        if (numbers_index == numbers_size) {
            numbers_size *= 2;
            numbers = realloc(numbers, numbers_size * sizeof({'type': 'array', 'itemType': 'int', 'alias': 'n'}));
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

        
            if (!argument_numbers) {
                sh_argument_required("acc", "numbers");
                return CONTINUE;
            }
            

        acc(numbers, numbers_index);
}
STATE sh_parse_command(char** words, int size) {
    STATE state = CONTINUE;

    if (size > 0) {
        char *command = words[0];

        if (strcmp(command, "add" == 0) {
            state = sh_command_add(words, size);
        }
        else if (strcmp(command, "acc" == 0) {
            state = sh_command_add(words, size);
        }
        
        else {
            state = sh_unknown_command(command);
        }

        free(command);
    }

    return state;
}