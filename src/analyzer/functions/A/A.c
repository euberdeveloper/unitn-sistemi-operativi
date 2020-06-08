#include "A.h"

/* HELPER VARIABLES */

static _an_state _state;

/* EXPORTED FUNCTIONS */

void an_init(int n, int m, char** inputs, int inputs_size, bool recursive, bool duplicates) {
    _state.n = n;
    _state.m = m;
    _state.inputs = inputs;
    _state.intputs_size = inputs_size;
    // todo _state.inputs = handle_inputs(inputs, inputs_size, recursive, duplicates);
}