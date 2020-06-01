#include "./analyser.h"

void anly_init(anly_frequencies *freqs) {
    freqs->n_lowercases = 0;
    freqs->n_uppercases = 0;
    freqs->n_digits = 0;
    freqs->n_spaces = 0;
    freqs->n_puncts = 0;
    freqs->n_unknowns = 0;
}

void anly_update(char ch, anly_frequencies *freqs) {
    if (isupper(ch)) {
        freqs->n_uppercases++;
    }
    else if (islower(ch)) {
        freqs->n_lowercases++;
    }
    else if (isdigit(ch)) {
        freqs->n_digits++;
    }
    else if (isspace(ch)) {
        freqs->n_spaces++;
    }
    else if (ispunct(ch)) {
        freqs->n_puncts++;
    }
    else {
        freqs->n_unknowns++;
    }
}
