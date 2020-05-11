#include <assert.h>
#include "analyser.h"

anly_frequencies frequencies;

void test_init();

int main() {
    test_init();
}

void test_init() {
    anly_init(&frequencies);

    assert(frequencies.n_lowercases == 0);
    assert(frequencies.n_uppercases == 0);
    assert(frequencies.n_digits == 0);
    assert(frequencies.n_spaces == 0);
    assert(frequencies.n_puncts == 0);
    assert(frequencies.n_unknowns == 0);
}