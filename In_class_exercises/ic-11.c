#include <stdio.h>

#define MAX 2147483647
#define MIN -2147483648

int reverse(int x) {
    int rev = 0;
    while (x != 0) {
        int digit = x % 10;  // This works for negatives too (-123 % 10 = -3)
        // Single overflow check that works for both positive and negative
        if (rev > MAX / 10 || rev < MIN / 10) 
            return 0;
        rev = rev * 10 + digit;  // Automatically builds correct sign
        x /= 10;
    }
    return rev;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", reverse(n));
    return 0;
}