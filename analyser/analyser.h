#ifndef ANLY_ANALYSER
#define ANLY_ANALYSER

#include <ctype.h>

typedef struct {
    int n_uppercases;
    int n_lowercases;
    int n_digits;
    int n_spaces;
    int n_puncts;
    int n_unknowns;
} anly_frequencies;

void anly_init(anly_frequencies *freqs);
void anly_update(char ch, anly_frequencies *freqs);

#endif