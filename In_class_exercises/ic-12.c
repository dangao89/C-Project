#include <stdio.h>
#include <stdbool.h>

int main() 
{
    int n;
    scanf("%d", &n);

    //Check for valid input range
    if (n < 0 || n > 5000000) {
        printf("Invalid input\n");
        return 1;
    }

    // If n is less than 2, there are no primes
    if (n < 2) {
        printf("0\n");
        return 0;
    }

    // Create a boolean array to track prime numbers
    // is_prime[i] will be true if i is a prime number
    bool is_prime[n];
    for (int i = 0; i < n; i++) {
        is_prime[i] = true; // Assume all numbers are prime initially
    }
    is_prime[0] = is_prime[1] = false; // 0 and 1 are not prime numbers

    //Sieve of Eratosthenes algorithm
    // For each number i starting from 2, mark its multiples as non-prime
    for (int i = 2; i * i < n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j < n; j += i) {
                is_prime[j] = false; // Mark multiples of i as non-prime
            }
        }
    }

    // Count the number of prime numbers
    int count = 0;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            count++;
        }
    }

    printf("%d\n", count); // Output the count of prime numbers
    return 0; // Return success

}