#!/usr/bin/python

import sys
import json
from pathlib import Path

# Template files

HEADER_TEMPLATE = './templates/header.template.txt'
C_TEMPLATE = './templates/c.template.txt'
SH_PARSE_COMMAND_TEMPLATE = './templates/sh_parse_command.template.txt'
SH_HANDLE_COMMAND_TEMPLATE = './templates/sh_handle_command.template.txt'
SH_HANDLE_COMMAND_CONDITION_TEMPLATE = './templates/sh_handle_command_condition.template.txt'
SH_HANDLE_COMMAND_UNKNOWN_ARGUMENT_TEMPLATE = './templates/sh_handle_command_unknown_argument.template.txt'
SH_HANDLE_COMMAND_ARRAY_ASSIGNMENT_TEMPLATE = './templates/sh_handle_command_array_assignment.template.txt'

# Arguments

JSON_COMMANDS = sys.argv[1] if len(sys.argv) > 1 else '../commands.json'
OUTPUT_PATH = sys.argv[2] if len(sys.argv) > 1 else '../shell_commands'

# Read template files

with open(HEADER_TEMPLATE) as header_template_file:
    header_template = header_template_file.read()

with open(C_TEMPLATE) as c_template_file:
    c_template = c_template_file.read()

with open(SH_PARSE_COMMAND_TEMPLATE) as sh_parse_command_template_file:
    sh_parse_command_template = sh_parse_command_template_file.read()

with open(SH_HANDLE_COMMAND_TEMPLATE) as sh_handle_command_template_file:
    sh_handle_command_template = sh_handle_command_template_file.read()

with open(SH_HANDLE_COMMAND_CONDITION_TEMPLATE) as sh_handle_command_condition_template_file:
    sh_handle_command_condition_template = sh_handle_command_condition_template_file.read()

with open(SH_HANDLE_COMMAND_UNKNOWN_ARGUMENT_TEMPLATE) as sh_handle_command_unknown_argument_template_file:
    sh_handle_command_unknown_argument_template = sh_handle_command_unknown_argument_template_file.read()

with open(SH_HANDLE_COMMAND_ARRAY_ASSIGNMENT_TEMPLATE) as sh_handle_command_array_assignment_file:
    sh_handle_command_array_assignment = sh_handle_command_array_assignment_file.read()

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

def get_function_arguments(arguments: dict):
    args = []

    for argument_name, argument_details in arguments.items():
        argument_raw_type = argument_details.get('type')
        argument_type, _ = split_array_argument(argument_raw_type)

        if argument_type == 'array':
           args.append(f'{argument_name}, {argument_name}_index')
        else:
           args.append(f'{argument_name}')
    
    return ', '.join(args)

def get_strcmp_condition(first: str, second: str):
    return f'strcmp({first}, {second}) == 0'

def get_conditional(condition: str, content: str, *, index=0):
    if index == 0:
        return f'if ({condition}) {{\n\t{content}\n}}'
    else:
        return f'else if ({condition}) {{\n\t{content}\n}}'

def tab(text: str, n_tabs: int, *, tab_first=False):
    return '\n'.join([(('\t' * n_tabs) if tab_first or index != 0 else '') + line for index, line in enumerate(text.splitlines())])

def get_argument_assignment(command_name: str, argument_name: str, argument_type: str):
    return f'!shu_get_{argument_type}_value("{command_name}", "{argument_name}", words[i], &{argument_name})'

def get_argument_max(command_name: str, argument_name: str, argument_type: str, max_value: str):
    return f'\n\t|| !shu_check_max_{argument_type}("{command_name}", "{argument_name}", {argument_name}, {max_value})'

def get_argument_min(command_name: str, argument_name: str, argument_type: str, min_value: str):
    return f'\n\t|| !shu_check_min_{argument_type}("{command_name}", "{argument_name}", {argument_name}, {min_value})'

# Generate output directory

Path(OUTPUT_PATH).mkdir(parents=True, exist_ok=True)

# Generate header file

def generate_header_extern_function(command_details: dict):
    function_name = command_details.get('function')
    arguments = command_details.get('arguments')
    params = get_function_params(arguments)

    return f'extern SH_STATE {function_name}({params});'

def generate_header_extern_functions(commands: dict):
    functions = [generate_header_extern_function(command_details) for _, command_details in commands.items()]
    return '\n'.join(functions)

def generate_header_file(commands: dict):
    extern_functions = generate_header_extern_functions(commands)
    return header_template.format(extern_functions = extern_functions)

h_output = f'{OUTPUT_PATH}/{library_name(OUTPUT_PATH)}.h'
with open(h_output, 'w') as h_output_file:
    h_output_file.write(generate_header_file(commands)) 

# Generate c file

def generate_c_handle_command_required_declarations(arguments: dict):
    lines = [f'bool is_assigned_{argument_name} = false;' for argument_name, argument_details in arguments.items() if argument_details.get('default') is None or argument_details.get('type') == 'bool']
    return '\n'.join(lines)

def generate_c_handle_command_argument_declaration(argument_name: str, argument_details: dict):
    argument_raw_type = argument_details.get('type')
    argument_type, argument_item_type = split_array_argument(argument_raw_type)
    argument_default = argument_details.get('default')

    if argument_type == 'array':
        return f'int {argument_name}_size = 0;\nint {argument_name}_index = 0;\n{argument_item_type} *{argument_name} = NULL;'
    elif argument_type == 'bool':
        return f'{argument_type} {argument_name} = false;'
    else:
        default_str = '' if argument_default is None else f'= {argument_default}'
        return f'{argument_type} {argument_name}{default_str};'

def generate_c_handle_command_arguments_declarations(arguments: dict):
    lines = [generate_c_handle_command_argument_declaration(argument_name, argument_details) for argument_name, argument_details in arguments.items()]
    return '\n'.join(lines)

def generate_c_handle_command_arguments_condition_assign_argument_array(command_name: str, argument_name: str, argument_item_type: str):
    if argument_item_type == 'char*':
        assignment = f'{argument_name}[{argument_name}_index++] = strdup(words[i]);'
    else:
        assignment = f'finish = !shu_get_{argument_item_type}_value("{command_name}", "{argument_name}", words[i], &{argument_name}[{argument_name}_index++]);'

    return sh_handle_command_array_assignment.format(command_name=command_name, argument_name=argument_name, argument_item_type=argument_item_type, assignment=assignment)

def generate_c_handle_command_arguments_condition_assign_argument(command_name: str, argument_name: str, argument_details: dict):
    argument_raw_type = argument_details.get('type')
    argument_type, argument_item_type = split_array_argument(argument_raw_type)
    argument_max, argument_min = argument_details.get('max'), argument_details.get('min')

    if argument_type == 'array':
        return generate_c_handle_command_arguments_condition_assign_argument_array(command_name, argument_name, argument_item_type)
    elif argument_type == 'bool':
        return f'{argument_name} = true;'
    elif argument_type == 'char*':
        return f'{argument_name} = strdup(words[i]);'
    else:
        assign_str = get_argument_assignment(command_name, argument_name, argument_type)
        max_str = get_argument_max(command_name, argument_name, argument_type, argument_max) if argument_max is not None else ''
        min_str = get_argument_min(command_name, argument_name, argument_type, argument_min) if argument_min is not None else ''
        return f'finish = {assign_str}{max_str}{min_str};'
    

def generate_c_handle_command_arguments_condition(command_name, argument_name, argument_details, *, index):
    argument_alias = argument_details.get('alias')
    argument_default = argument_details.get('default')
    argument_raw_type = argument_details.get('type')
    argument_type, argument_item_type = split_array_argument(argument_raw_type)
    
    
    condition_construct = 'if' if index == 0 else 'else if'
    condition_main = f'strcmp(argument, "{argument_name}") == 0'
    condition_alias = f' || (is_alias && strcmp(argument, "{argument_alias}") == 0)' if argument_alias is not None else ''
    condition = f'{condition_construct} ({condition_main}{condition_alias})'

    check_noval = f'finish = !shu_check_noval("{command_name}", "{argument_name}", n_words, &i);' if argument_type != 'bool' else ''

    assign_is_assigned = tab(f'is_assigned_{argument_name} = true;' if argument_default is None and argument_type != 'bool' and argument_type != 'array' else '', 1)

    assign_argument = tab(generate_c_handle_command_arguments_condition_assign_argument(command_name, argument_name, argument_details), 2)

    return sh_handle_command_condition_template.format(condition=condition, check_noval=check_noval, assign_is_assigned=assign_is_assigned, assign_argument=assign_argument)

def generate_c_handle_command_arguments_conditions(command_name: str, command_details: dict):
    arguments = command_details.get('arguments')

    command_conditions_blocks = [generate_c_handle_command_arguments_condition(command_name, argument_name, argument_details, index=index) for index, (argument_name, argument_details) in enumerate(arguments.items())]
    command_conditions = '\n'.join(command_conditions_blocks)
    
    unknown_construct = 'if' if arguments is None else 'else'
    unknown_argument = sh_handle_command_unknown_argument_template.format(construct=unknown_construct, command_name=command_name)

    return f'{command_conditions}\n{unknown_argument}'

def generate_c_handle_command_required_check(command_name: str, argument_name: str, argument_details: dict):
    argument_default = argument_details.get('default')
    argument_type = argument_details.get('type')

    return (
        get_conditional('!finish', f'finish = !shu_check_required("{command_name}", "{argument_name}", is_assigned_{argument_name});') 
        if argument_default is None and argument_type != 'bool'
        else '')

def generate_c_handle_command_required_checks(command_name: str, arguments: dict):
    blocks = [generate_c_handle_command_required_check(command_name, argument_name, argument_details) for argument_name, argument_details in arguments.items()]
    return '\n'.join(blocks)

def generate_c_handle_command_command_function(command_details: dict):
    function_name = command_details.get('function')
    arguments = command_details.get('arguments')
    args = get_function_arguments(arguments)

    return f'{function_name}({args});'

def generate_c_handle_command_function(command_name: str, command_details: dict):
    arguments = command_details.get('arguments')

    required_declarations = tab(generate_c_handle_command_required_declarations(arguments), 1)
    arguments_declarations = tab(generate_c_handle_command_arguments_declarations(arguments), 1)
    arguments_conditions = tab(generate_c_handle_command_arguments_conditions(command_name, command_details), 3)
    required_check = tab(generate_c_handle_command_required_checks(command_name, arguments), 1)
    command_function = generate_c_handle_command_command_function(command_details)

    return sh_handle_command_template.format(command_name = command_name, required_declarations = required_declarations, arguments_declarations = arguments_declarations, arguments_conditions = arguments_conditions, required_check = required_check, command_function = command_function)

def generate_c_handle_command_functions(commands: dict):
    functions = [generate_c_handle_command_function(command_name, command_details) for command_name, command_details in commands.items()]
    return '\n'.join(functions)

def generate_c_parse_command_function(commands: dict):
    command_names = commands.keys()
    gen_condition = lambda command_name, index: get_conditional(get_strcmp_condition('command', f'"{command_name}"'), f'state = sh_handle_{command_name}(words, size);', index=index)

    conditions = [gen_condition(command_name, index) for index, command_name in enumerate(command_names)]
    commands_conditions = tab('\n'.join(conditions), 2)

    return sh_parse_command_template.format(commands_conditions = commands_conditions)

def generate_c_file(name: str, commands: dict):
    include = f'{name}.h'
    prompt_symbol = commands.get('promptSymbol') if commands.get('promptSymbol') else '>> '
    parse_command_function = generate_c_parse_command_function(commands)
    handle_command_functions = generate_c_handle_command_functions(commands)
    return c_template.format(include = include, prompt_symbol = prompt_symbol, parse_command_function = parse_command_function, handle_command_functions = handle_command_functions)

c_output = f'{OUTPUT_PATH}/{library_name(OUTPUT_PATH)}.c'
with open(c_output, 'w') as c_output_file:
    c_output_file.write(generate_c_file(library_name(OUTPUT_PATH), commands)) 
