#include "text.h"

int main() {
    printf("Test readline\n");
    char* text = txt_readline();
    printf("Du hast geschrieben %s\n", text);
    int s;
    char** words = txt_splitline(text, &s);
    printf("Die %d woerter sind: \n", s);
    int i;
    for(i = 0; i < s; i++) {
        printf("%s\n", words[i]);
    }

    return 0;
}