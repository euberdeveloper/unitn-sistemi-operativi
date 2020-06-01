#include "general.h"

void gn_abort(char* message, int code) {
    fprintf(stderr, "%s (Code %d) %s", col_red("[FATAL ERROR]"), code, message);
    exit(code);
}