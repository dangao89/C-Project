#include <stdio.h>

int main() 
{
    int height = 10;
    int width = 20;

    for (int i = 1; i <= height; i++) {
        char symbol = (i % 2 == 1) ? '*' : '#';
        for (int j = 0; j < width; j++) {
            printf("%c", symbol);
        }
        printf("\n");
    }

    return 0;
}
