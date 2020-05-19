#include "shell_utils/shell_utils.h"
#include "shell_commands/shell_commands.h"

SH_STATE init(int p_number, int q_number, char** inputs, int inputs_size, bool recursive) {
    printf("Init\n");
    printf("n: %d, m: %d, i_size: %d, rec: %d\n", p_number, q_number, inputs_size, recursive);
    int i;
    for (i = 0; i < inputs_size; i++) {
        printf("%s\n", inputs[i]);
    }
    return SH_CONTINUE;
}

int main() {
    sh_loop();
    return 0;
}