#include <stdio.h>
#include <ctype.h>

int main() 
{
    char str1[1001];
    char str2[1001];
    char ch;
    int i = 0, j = 0;
    while (islower(ch = getchar()) && ch != '\n' && ch != EOF) {
        str1[i++] = ch;
    }
    str1[i] = '\0';
    while (islower(ch = getchar()) && ch != '\n' && ch != EOF) {
        str2[j++] = ch;
    }
    str2[j] = '\0';

    int result = 0;
    for (i = 0; str1[i] != '\0'; i++) {
        result ^= str1[i];
    }
    for (j = 0; str2[j] != '\0'; j++) {
        result ^= str2[j];
    }

    printf("%c\n", (char)result);
    return 0;
}