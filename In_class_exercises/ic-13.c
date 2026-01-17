#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);

    if (n < 0 || n > 1000) {
        printf("Invalid input.\n");
        return 1;
    }

    if (n == 0) {
        printf("0\n");
        return 0;
    }

    int weight = 1;

    // Find the highest power of 2 less than or equal to n
    while (weight < n / 2) {
        weight *= 2;
    }

    // Print binary digits
    while (weight > 0) {
        if (n >= weight) {
            printf("1");
            n -= weight;
        } else {
            printf("0");
        }
        weight /= 2;
    }

    printf("\n");
    return 0;
}
