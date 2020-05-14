#!/usr/bin/python

import sys
import json

def generate_command_signature(command_name):
    return f'STATE sh_command_{command_name}(char** words, int size)'

def generate_command_required_arguments(command_details):
    result = ''
    arguments = command_details['arguments']
    
    for argument, argument_details in arguments.items():
        if argument_details.get('default') is None:
            result += f'bool argument_{argument} = false;\n'

    return result

def generate_command_arguments(command_name, command_details):
    result = ''
    arguments = command_details.get('arguments')
    default_initial_size = 8

    for argument, argument_details in arguments.items():
        argument_type = argument_details.get('type')
        argument_default = argument_details.get('default')

        if argument_type == 'array':
            item_type = argument_details.get('itemType')

            result += f'int {argument}_size = {default_initial_size};\n'
            result += f'int {argument}_index = 0;\n'
            result += f'{item_type}* {argument} = malloc({argument}_size * sizeof({item_type}));\n'
        else:
            default_string = f' = {argument_default}' if argument_default is not None else ''

            result += f'{argument_type} {argument}{default_string};\n'

    return result

def interpretate_noval(command_name, argument_name):
   return '''if (++i >= size) {{
        sh_argument_noval("{0}", "{1}");
        free(argument);
        return CONTINUE;
    }}\n'''.format(command_name, argument_name)

def interpretate_bool(argument_name):
    return f'{argument_name} = true;'

def interpretate_string(argument_name, argument_default):
    first_line = '' if argument_default is None else f'argument_{argument_name} = true;\n'
    return f'{first_line}{argument_name} = words[i];\n'

def interpretate_min(command_name, argument_name, min):
    return '''\t\tif (!sh_argument_min("{0}", "{1}", {1}, {2})) {{
        free(argument);
        return CONTINUE;
    }}\n'''.format(command_name, argument_name, min)

def interpretate_max(command_name, argument_name, max):
    return '''if (!sh_argument_max("{0}", "{1}", {1}, {2})) {{
        free(argument);
        return CONTINUE;
    }}\n'''.format(command_name, argument_name, max)

def interpretate_int(command_name, argument_name, argument_default, argument_details):
    first_line = '' if argument_default is not None else f'argument_{argument_name} = true;\n'
    second_line = f'{argument_name} = atoi(words[i]);\n'

    min = argument_details.get('min')
    max = argument_details.get('max')
    min_str = interpretate_min(command_name, argument_name, min) if min is not None else ''
    max_str = interpretate_max(command_name, argument_name, max) if max is not None else ''

    return f'{first_line}{second_line}{min_str}{max_str}'

def interpretate_array(argument_name, argument_details):
    item_type = argument_details.get('itemType')
    assignment_str = 'words[i]' if item_type == 'string' else 'atoi(words[i])'

    return '''bool placeholder;
    while (i < size && sh_extract_argument(words[i], &placeholder) == NULL) {{
        {0}[{0}_index++] = {2};
        if ({0}_index == {0}_size) {{
            {0}_size *= 2;
            {0} = realloc({0}, {0}_size * sizeof({1}));
        }}
        argument_{0} = true;
        i++;
    }}

    if (i < size) {{
        i--;
    }}
    '''.format(argument_name, argument_details, assignment_str)

def interpretate_argument(command_name, argument_name, argument_details, is_first):
    argument_type = argument_details.get('type')
    argument_default = argument_details.get('default')
    argument_alias = argument_details.get('alias')
    
    costruct = 'if' if is_first else 'else if'
    alias_condition = f' || (is_alias && strcmp(argument, "{argument_alias}") == 0)' if argument_alias is not None else ''

    header = f'{costruct} (strcmp(argument, "{argument_name}") == 0{alias_condition}) {{\n'
    novalue = interpretate_noval(command_name, argument_name) if argument_type != 'bool' else ''
    if argument_type == 'bool':
        body = interpretate_bool(argument_name)
    elif argument_type == 'string':
        body = interpretate_string(argument_name, argument_default)
    elif argument_type == 'int':
        body = interpretate_int(command_name, argument_name, argument_default, argument_details)
    elif argument_type == 'array':
        body = interpretate_array(argument_name, argument_details)
    footer = '}\n'
    return f'{header}{novalue}{body}{footer}'

def generate_command_interpretation(command_name, command_details):
    result = ''
    arguments = command_details.get('arguments')
    is_first = True

    for argument_name, argument_details in arguments.items():
        function_name = command_details.get('function')

        result += interpretate_argument(command_name, argument_name, argument_details, is_first)
        is_first = False

    return result
        
def generate_command_required_check(command_name, command_details):
    result = ''
    arguments = command_details.get('arguments')

    for argument_name, argument_details in arguments.items():
        if argument_details.get('default') is  None:
            result += '''
            if (!argument_numbers) {{
                sh_argument_required("{0}", "{1}");
                return CONTINUE;
            }}
            '''.format(command_name, argument_name)

    return result

def generate_command_function(command_details):
    function_name = command_details.get('function')
    arguments = command_details.get('arguments')
    argument_names = arguments.keys()
    argument_len = len(argument_names)

    result = f'{function_name}('
    for i, argument_name in enumerate(argument_names):
        result += f'{argument_name}, {argument_name}_index' if arguments[argument_name].get('type') == 'array' else argument_name
        result += ');' if i == argument_len - 1 else ', '

    return result


def sh_command(command_name, command_details):
    result = '''{{SIGNATURE}} {
        {{REQUIRED_ARGUMENTS}}

        {{ARGUMENTS}}

        bool is_alias;
        char* argument = NULL;
        int i;

        for (i = 1; i < size; i++) {
            argument = sh_extract_argument(words[i], &is_alias);

            if (argument != NULL) {
                {{INTERPRETATION}}
            }
        }

        {{REQUIRED_CHECK}}

        {{FUNCTION}}
}'''
    result = result.replace('{{SIGNATURE}}', generate_command_signature(command_name))  
    result = result.replace('{{REQUIRED_ARGUMENTS}}', generate_command_required_arguments(command_details))
    result = result.replace('{{ARGUMENTS}}', generate_command_arguments(command_name, command_details))
    result = result.replace('{{INTERPRETATION}}', generate_command_interpretation(command_name, command_details))
    result = result.replace('{{REQUIRED_CHECK}}', generate_command_required_check(command_name, command_details))
    result = result.replace('{{FUNCTION}}', generate_command_function(command_details))
    return result

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
    sh_parse_command_code = sh_parse_command(commands)
    sh_commands_functions = ''
    
    for command, command_details in data.items():
        sh_commands_functions += sh_command(command, command_details)

    code = f'{sh_commands_functions}\n{sh_parse_command_code}'
    with open('./result.c', 'w') as out_file:
        out_file.write(code)
