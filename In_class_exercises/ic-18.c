#include <stdio.h>
int main()
{
    int n;
    scanf("%d", &n);
    if (n < 1 && n > 1000) {
        printf("Invalid input.");
        return 1;
    }
    int num, missNum, sum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &num);
        sum += num;
    }
    missNum = (n * (n + 1)) / 2 - sum;
    printf("%d\n", missNum);
    return 0;
}