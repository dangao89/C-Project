#include <stdio.h>
#include <ctype.h>

int main()
{
    int ch;
    int alpha = 0, space = 0, digit = 0, lower = 0, upper = 0;

    while ((ch = getchar()) != EOF)
    {
        _Bool isAlpha = isalpha(ch);
        _Bool isSpace = isspace(ch);
        _Bool isDigit = isdigit(ch);
        _Bool isLower = islower(ch);
        _Bool isUpper = isupper(ch);

        if (isAlpha)
            alpha++;
        if (isSpace)
            space++;
        if (isDigit)
            digit++;
        if (isLower)
            lower++;
        if (isUpper)
            upper++;
    }
    printf("Alphabetic: %d\n", alpha);
    printf("Whitespace: %d\n", space);
    printf("Digits: %d\n", digit);
    printf("Lowercase: %d\n", lower);
    printf("Uppercase: %d\n", upper);

    return 0;
}
