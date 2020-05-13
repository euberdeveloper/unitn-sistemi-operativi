#include <stdio.h>
#include <stdlib.h>

char* readline();


int main() {
    char* a = readline();
    printf("%s", a);
    return 0;
}

char* readline() {
    char* line = NULL;
    size_t size;

    if (getline(&line, &size, stdin) == -1) {
        free(line);
        printf("Fucking error");
        exit(1);
    }

    return line;
}