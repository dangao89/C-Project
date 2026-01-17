#include <stdio.h>
#include <ctype.h>
int main() {
    int ch;
    while((ch = getchar()) != EOF) {
        if (isalpha (ch)) {
            ch = tolower (ch);
        }
        putchar(ch);
    }
    return 0;
}