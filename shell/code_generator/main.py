#!/usr/bin/python

import sys
import json
from pathlib import Path

# Template files

HEADER_TEMPLATE = './templates/header.template.txt'
CODE_TEMPLATE = './templates/code.template.txt'

# Arguments

JSON_COMMANDS = sys.argv[1] if len(sys.argv) > 1 else '../commands.json'
OUTPUT_PATH = sys.argv[2] if len(sys.argv) > 1 else '../TEST'

# Read template files

with open(HEADER_TEMPLATE) as header_template_file:
    header_template = header_template_file.read()

with open(CODE_TEMPLATE) as code_template_file:
    code_template = code_template_file.read()

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
