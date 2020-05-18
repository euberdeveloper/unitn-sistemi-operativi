#!/usr/bin/python

import sys
import json
from pathlib import Path

# Template files

HEADER_TEMPLATE = './templates/header.template.txt'
C_TEMPLATE = './templates/c.template.txt'
SH_PARSE_COMMAND_TEMPLATE = './templates/sh_parse_command.template.txt'
SH_HANDLE_COMMAND_TEMPLATE = './templates/sh_handle_command.template.txt'

# Arguments

JSON_COMMANDS = sys.argv[1] if len(sys.argv) > 1 else '../commands.json'
OUTPUT_PATH = sys.argv[2] if len(sys.argv) > 1 else '../TEST'

# Read template files

with open(HEADER_TEMPLATE) as header_template_file:
    header_template = header_template_file.read()

with open(C_TEMPLATE) as c_template_file:
    c_template = c_template_file.read()

with open(SH_PARSE_COMMAND_TEMPLATE) as sh_parse_command_file:
    sh_parse_command = sh_parse_command_file.read()

with open(SH_HANDLE_COMMAND_TEMPLATE) as sh_handle_command_file:
    sh_handle_command = sh_handle_command_file.read()

# Read json file

with open(JSON_COMMANDS) as json_commands_file:
    commands = json.load(json_commands_file)

# Utils functions

def library_name(path: str):
    von = path.rfind('/')
    return path[von+1:]

def split_array_argument(argument_type: str):
    if argument_type.startswith('array'):
        von, bis = argument_type.find('<'), argument_type.find('>')
        return 'array', argument_type[von+1:bis]
    else:
        return argument_type, None

def get_function_params(arguments: dict):
    params = []

    for argument_name, argument_details in arguments.items():
        argument_raw_type = argument_details.get('type')
        argument_type, argument_item_type = split_array_argument(argument_raw_type)

        if argument_type == 'array':
           params.append(f'{argument_item_type}* {argument_name}, int {argument_name}_size')
        else:
           params.append(f'{argument_type} {argument_name}')
    
    return ', '.join(params)

def get_strcmp_condition(first: str, second: str):
    return f'strcmp({first}, {second}) == 0'

def get_conditional(condition: str, content: str, *, index=0):
    if index == 0:
        return f'if ({condition}) {{\n\t{content}\n}}'
    else:
        return f'else if ({condition}) {{\n\t{content}\n}}'

def tab(text: str, n_tabs: int, *, tab_first=False):
    return '\n'.join([(('\t' * n_tabs) if tab_first or index != 0 else '') + line for index, line in enumerate(text.splitlines())])

# Generate output directory

Path(OUTPUT_PATH).mkdir(parents=True, exist_ok=True)

# Generate header file

def generate_header_external_function(command_details: dict):
    function_name = command_details.get('function')
    arguments = command_details.get('arguments')
    params = get_function_params(arguments)

    return f'extern SH_STATE {function_name}({params});'

def generate_header_extern_functions(commands: dict):
    functions = [generate_header_external_function(command_details) for _, command_details in commands.items()]
    return '\n'.join(functions)

def generate_header_file(commands: dict):
    extern_functions = generate_header_extern_functions(commands)
    return header_template.format(extern_functions = extern_functions)

h_output = f'{OUTPUT_PATH}/{library_name(OUTPUT_PATH)}.h'
with open(h_output, 'w') as h_output_file:
    h_output_file.write(generate_header_file(commands)) 

# Generate c file

def generate_c_handle_command_required_declarations(arguments: dict):
    lines = [f'bool is_assigned_{argument_name};' for argument_name, argument_details in arguments.items() if argument_details.get('default') is None]
    return '\n'.join(lines)

def generate_c_handle_command_function(command_name: str, command_details: dict):
    arguments = command_details.get('arguments')

    required_declarations = generate_c_handle_command_required_declarations(arguments)

    return sh_handle_command.format(command_name = command_name, required_declarations = required_declarations, arguments_declarations = '', arguments_conditions = '', required_check = '', command_function = '')

def generate_c_handle_command_functions(commands: dict):
    functions = [generate_c_handle_command_function(command_name, command_details) for command_name, command_details in commands.items()]
    return '\n'.join(functions)

def generate_c_parse_command_function(commands: dict):
    command_names = commands.keys()
    gen_condition = lambda command_name, index: get_conditional(get_strcmp_condition('command', command_name), 'state = sh_handle_add(words, size);', index=index)

    conditions = [gen_condition(command_name, index) for index, command_name in enumerate(command_names)]
    commands_conditions = tab('\n'.join(conditions), 1)

    return sh_parse_command.format(commands_conditions = commands_conditions)

def generate_c_file(name: str, commands: dict):
    include = f'{name}.h'
    prompt_symbol = commands.get('promptSymbol') if commands.get('promptSymbol') else '>> '
    parse_command_function = generate_c_parse_command_function(commands)
    handle_command_functions = generate_c_handle_command_functions(commands)
    return c_template.format(include = include, prompt_symbol = prompt_symbol, parse_command_function = parse_command_function, handle_command_functions = handle_command_functions)

c_output = f'{OUTPUT_PATH}/{library_name(OUTPUT_PATH)}.c'
with open(c_output, 'w') as c_output_file:
    c_output_file.write(generate_c_file(library_name(OUTPUT_PATH), commands)) 