#ifndef AN_ANALIZER
#define AN_ANALIZER

/* IMPORTS */

#include "../../../../libs/general/general.h"
#include <unistd.h>

/* STRUCTS */

typedef struct {
    int n;
    int m;
    char** inputs;
    int intputs_size;
} _an_state;

/* FUNCTIONS */

void an_init(int n, int m, char** inputs, int inputs_size, bool recursive);

#endif