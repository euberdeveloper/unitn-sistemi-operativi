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

SH_STATE set(int p_number, int q_number, char** inputs, int inputs_size, bool recursive, bool keep) {
    printf("set\n");
    printf("n: %d, m: %d, i_size: %d, rec: %d\n", p_number, q_number, inputs_size, recursive);
    int i;
    for (i = 0; i < inputs_size; i++) {
        printf("%s\n", inputs[i]);
    }
    return SH_CONTINUE;
}

SH_STATE restart(int p_number, int q_number, char** inputs, int inputs_size, bool recursive) {
    printf("restart\n");
    printf("n: %d, m: %d, i_size: %d, rec: %d\n", p_number, q_number, inputs_size, recursive);
    int i;
    for (i = 0; i < inputs_size; i++) {
        printf("%s\n", inputs[i]);
    }
    return SH_CONTINUE;
}

SH_STATE pop(char** inputs, int inputs_size) {
    printf("pop\n");

    return SH_CONTINUE;
}

SH_STATE stop() {
    printf("stop\n");

    return SH_CONTINUE;
}

SH_STATE quit() {
    printf("quit\n");

    return SH_EXIT;
}

int main() {
    sh_loop();
    return 0;
}