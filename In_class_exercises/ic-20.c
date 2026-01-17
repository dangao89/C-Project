#include <stdio.h>

int main() 
{
    int n;
    scanf("%d", &n);
    if (n < 1 || n > 1000) {
        printf("Invalid input\n");
        return 1;
    }
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int prefix = 0;
    for (int i = 0; i < n; i++) {
        prefix = (prefix * 2 + a[i]) % 5;
        printf("%s ", (prefix == 0) ? "true" : "false");
    }
    printf("\n");

    return 0;  
}