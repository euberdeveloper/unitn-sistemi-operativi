#include "functions.h"

SH_STATE show(bool sensitive, bool percentage, bool realtime, bool detailed, char** files, int files_size) {
    printf("s = %d, p = %d, r = %d, d = %d\n", sensitive, percentage, realtime, detailed);
    printf("[\n");
    for (int i = 0; i < files_size; i++) {
        printf("%s\n", files[i]);
    }
    printf("]\n");

    return SH_CONTINUE;
}
SH_STATE quit() {
    printf("quit\n");
    return SH_EXIT;
}