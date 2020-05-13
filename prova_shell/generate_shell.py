#!/usr/bin/python

import sys
import json

def generate_commands(commands):
    res = ''

    for index, command in enumerate(commands):
        costruct = 'if' if index == 0 else 'else if'
        condition = f' (strcmp(command, "{command}" == 0) '
        fixed = '''{
            state = sh_command_add(words, size);
        }
        '''
        res += costruct + condition + fixed

    return res


def sh_parse_command(commands):
    template = '''STATE sh_parse_command(char** words, int size) {
    STATE state = CONTINUE;

    if (size > 0) {
        char *command = words[0];

        {{COMMANDS}}
        else {
            state = sh_unknown_command(command);
        }

        free(command);
    }

    return state;
}'''
    return  template.replace('{{COMMANDS}}', generate_commands(commands))

json_path = (sys.argv[1] if len(sys.argv) > 1 else "./commands.json")

with open(json_path) as json_file:
    data = json.load(json_file)

    commands = data.keys()
    sh_parse_command_code = sh_parse_command(commands))
    
    for command, command_details in data.items():
        print(command, str(command_details))