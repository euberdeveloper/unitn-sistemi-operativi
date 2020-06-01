#include "functions.h"

SH_STATE init(int p_number, int q_number, char** inputs, int inputs_size, bool recursive) {
    printf("init: n = %d m = %d r = %d\n", p_number, q_number, recursive);

    printf("[\n");
    for (int i = 0; i < inputs_size; i++) {
        printf("%s\n", inputs[i]);
    }
    printf("]\n");

    return SH_CONTINUE;
}

SH_STATE set(int p_number, int q_number, char** inputs, int inputs_size, bool recursive, bool keep) {
    printf("init: n = %d m = %d r = %d k = %d\n", p_number, q_number, recursive, keep);

    printf("[\n");
    for (int i = 0; i < inputs_size; i++) {
        printf("%s\n", inputs[i]);
    }
    printf("]\n");

    return SH_CONTINUE;
}

SH_STATE restart(int p_number, int q_number, char** inputs, int inputs_size, bool recursive) {
    printf("init: n = %d m = %d r = %d\n", p_number, q_number, recursive);

    printf("[\n");
    for (int i = 0; i < inputs_size; i++) {
        printf("%s\n", inputs[i]);
    }
    printf("]\n");

    return SH_CONTINUE;
}

SH_STATE pop(char** inputs, int inputs_size) {
    printf("[\n");
    for (int i = 0; i < inputs_size; i++) {
        printf("%s\n", inputs[i]);
    }
    printf("]\n");

    return SH_CONTINUE;
}

SH_STATE status() {
    printf("status\n");

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