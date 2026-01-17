#include <stdio.h>

int main() {
    int height = 10;
    int width = 20;

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}
