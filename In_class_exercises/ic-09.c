#include <stdio.h>
int main() {
    int n;
    // Keep reading integers until EOF
    while (scanf("%d,", &n) == 1) {
        printf("%c", (char)n);
    }
    return 0;
}