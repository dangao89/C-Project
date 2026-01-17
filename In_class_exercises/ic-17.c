#include <stdio.h>
int main()
{
    int n;
    scanf("%d", &n);
    int result = 0;
    for (int i = 1; i <= n; i++) {
        int num;
        scanf("%d", &num);
        result ^= num;
    }
    printf("%d\n", result);
    return 0;
}