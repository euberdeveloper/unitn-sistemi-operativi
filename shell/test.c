#include "shell_utils/shell_utils.h"
#include "shell_commands/shell_commands.h"

SH_STATE add_shit(int first, int second) {
    printf("Adding shit...\n");
    printf("First %i, Second %i\n", first, second);
}
SH_STATE acc(int* numbers, int numbers_size) {
    printf("Acc\n");
    printf("Size: %i\n", numbers_size);
    int i;
    for (i = 0; i < numbers_size; i++) {
        printf("%i - %i\n", i, numbers[i]);
    }
}

int main() {
    sh_loop();
    return 0;
}