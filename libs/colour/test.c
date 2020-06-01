#include <stdio.h>
#include <string.h>
#include "colour.h"

int main() {
    printf("%s\n", col_cyan("ciao"));
    printf("%s\n", col_gray("ciao"));
    printf("%s\n", col_green("ciao"));
    printf("%s\n", col_magenta("ciao"));
    printf("%s\n", col_red("ciao"));
    printf("%s\n", col_yellow("ciao"));
    printf("%s\n", col_blue("ciao"));

    printf("%s\n", col_cyan_del(strdup("ciao")));
    printf("%s\n", col_gray_del(strdup("ciao")));
    printf("%s\n", col_green_del(strdup("ciao")));
    printf("%s\n", col_magenta_del(strdup("ciao")));
    printf("%s\n", col_red_del(strdup("ciao")));
    printf("%s\n", col_yellow_del(strdup("ciao")));
    printf("%s\n", col_blue_del(strdup("ciao")));

    return 0;
}