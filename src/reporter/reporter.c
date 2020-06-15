#include <stdio.h>
#include <stdlib.h>

#include "../../libs/shell_utils/shell_utils.h"
#include "shell_commands/shell_commands.h"
#include "functions/functions.h"

int main(int argc, char** argv) {
    sh_handle__arguments(argv, argc);
    sh_loop();
    return 0;
}