/**
    @file fraction.c
    This program provides functions for handling fractions, including creating, simplifying, 
    and performing arithmetic operations on fractions. It also includes functions for converting 
    decimal parts to fractions and printing fractions in a human-readable format.
 */
#include <stdio.h>
#include <stdlib.h>
#include "fraction.h"

/**
    This function is used to calculate the GCD of two integers using the Euclidean algorithm. 
    If either a or b is negative, it is treated as its absolute value.
    @param a First integer
    @param b Second integer
    @return The greatest common divisor (GCD) of a and b. If both a and b are zero, returns 1.
 */
int64 gcd(int64 a, int64 b) 
{
    // Handle negative values by converting them to positive
    if (a < 0) a = -a;
    if (b < 0) b = -b;

    // If b is zero, gcd(a, b) is either a (if a != 0) or undefined if a is also zero
    if (b == 0) {
        if (a != 0) {
            return a;
        } else {
            fprintf(stderr, "Error: gcd(0, 0) is undefined.\n");
            exit(EXIT_FAILURE);
        }
    }

    // Use the Euclidean algorithm to find the GCD
    return gcd(b, a % b);
}

/**
    This function simplifies a fraction by dividing both the numerator and denominator by their GCD.
    If the denominator is negative, it negates both the numerator and denominator to ensure the denominator is positive.
    @param f Fraction to simplify  
 */
void simplify(Fraction f) 
{
    // If the denominator is zero, do nothing
    if (f[1] == 0) {
        fprintf(stderr, "Error: Denominator cannot be zero in simplify.\n");
        exit(EXIT_FAILURE);
    }

    // If the denominator is negative, negate both numerator and denominator
    if (f[1] < 0) {
        f[0] = -f[0];
        f[1] = -f[1];
    }
    // Declare a variable to hold the GCD
    int64 g = gcd(f[0], f[1]);

    // If the GCD is greater than 1, divide both numerator and denominator by the GCD
    if (g > 1) {
        f[0] /= g;
        f[1] /= g;
    }
}

/**
    This function creates a new fraction from the input fraction and simplifies it.  
    @param input Fraction to convert
    @param output Fraction to store the result    
 */
void make_fraction(const Fraction input, Fraction output) 
{
    // Check if the denominator of the input fraction is zero
    if (input[1] == 0) {
        fprintf(stderr, "Error: invalid input (zero denominator) in make_fraction.\n");
        exit(EXIT_FAILURE);
    }
    // Copy the numerator and denominator
    output[0] = input[0];
    output[1] = input[1];

    // Call the simplify function to ensure the output fraction is simplified
    simplify(output);
}

/**
    This function converts a DecimalParts structure (which contains an integer part and a decimal part) 
    into a Fraction. It calculates the denominator based on the number of digits in the decimal part.
    @param input DecimalParts to convert
    @param output Fraction to store the result 
*/
void from_decimal_parts(const DecimalParts input, Fraction output) 
{
    // Declare variables for integer part, decimal part, and decimal length
    int64 integer_part = input[0];
    int64 decimal_part = input[1];
    int64 decimal_length = input[2];
   
    // If the decimal length is invalid, print an error message and exit
    if (decimal_length < 0 || decimal_length > 15) {
        fprintf(stderr, "Error: invalid decimal length %lld in from_decimal_parts.\n", decimal_length);
        exit(EXIT_FAILURE);
    }
    
    // Initialize the denominator to 1 (10^0)
    int64 denominator = 1;
    // Calculate the denominator based on the decimal length
    for (int i = 0; i < decimal_length; ++i) {
        denominator *= 10;
    }
    // Calculate the numerator based on the integer part and decimal part
    int64 numerator;
    if (decimal_length == 0) {
        numerator = integer_part;
        denominator = 1;
    } else {
        numerator = integer_part * denominator;
        if (integer_part >= 0) {
            numerator += decimal_part;
        } else {
            numerator -= decimal_part;
        }
    }
    // Store the result in the output fraction
    output[0] = numerator;
    output[1] = denominator;
    simplify(output);
}

/**
    This function adds two fractions together. It calculates the sum using the least common multiple (LCM) of the denominators.
    @param a First fraction
    @param b Second fraction
    @param result Fraction to store the result 
 */
void add_fraction(const Fraction a, const Fraction b, Fraction result) 
{
    // Check if the denominator of either fraction is zero
    if (a[1] == 0 || b[1] == 0) {
        fprintf(stderr, "Error: invalid input (zero denominator) in add_fraction.\n");
        exit(EXIT_FAILURE);
    }

    // Calculate the lcm of the denominators of a and b
    int64 g = gcd(a[1], b[1]);
    int64 lcm_den = (a[1] / g) * b[1];
    // Scale the numerators to the common denominator
    int64 a_num = a[0] * (lcm_den / a[1]);
    int64 b_num = b[0] * (lcm_den / b[1]);

    // Store the resulting fraction
    result[0] = a_num + b_num;
    result[1] = lcm_den;
    simplify(result);
}

/**
    This function subtracts one fraction from another using the least common multiple (LCM) of the denominators.
    @param a First fraction
    @param b Second fraction
    @param result Fraction to store the result
 */
void subtract_fraction(const Fraction a, const Fraction b, Fraction result) 
{
    // Check if the denominator of either fraction is zero
    if (a[1] == 0 || b[1] == 0) {
        fprintf(stderr, "Error: invalid input (zero denominator) in subtract_fraction.\n");
        exit(EXIT_FAILURE);
    }

    // Calculate the lcm of the denominators of a and b
    int64 g = gcd(a[1], b[1]);
    int64 lcm_den = (a[1] / g) * b[1];
    // Scale the numerators to the common denominator
    int64 a_num = a[0] * (lcm_den / a[1]);
    int64 b_num = b[0] * (lcm_den / b[1]);

    // Store the result in the output fraction
    result[0] = a_num - b_num;
    result[1] = lcm_den;
    simplify(result);
}

/**
    This function multiplies two fractions together. It multiplies the numerators and denominators directly.
    @param a First fraction
    @param b Second fraction
    @param result Fraction to store the result
 */
void multiply_fraction(const Fraction a, const Fraction b, Fraction result) 
{
    // Check if the denominator of either fraction is zero
    if (a[1] == 0 || b[1] == 0) {
        fprintf(stderr, "Error: invalid input (zero denominator) in multiply_fraction.\n");
        exit(EXIT_FAILURE);
    }
    // Calculate the numerator and denominator for the product of two fractions.
    result[0] = a[0] * b[0];
    result[1] = a[1] * b[1];
    simplify(result);
}

/**
    This function divides one fraction by another. It multiplies the first fraction's numerator by the second 
    fraction's denominator and the first fraction's denominator by the second fraction's numerator.
    @param a First fraction
    @param b Second fraction
    @param result Fraction to store the result
 */
void divide_fraction(const Fraction a, const Fraction b, Fraction result) 
{
    // Check if the denominator of either fraction is zero
    if (a[1] == 0 || b[1] == 0) {
        fprintf(stderr, "Error: invalid input (zero denominator) in divide_fraction.\n");
        exit(EXIT_FAILURE);
    }

    // Claculate the numerator and denominator for the division of two fractions.
    result[0] = a[0] * b[1];
    result[1] = a[1] * b[0];

    // Check for division by zero in the denominator
    if (result[1] == 0) {
        fprintf(stderr, "Error: Division by zero in divide_fraction.\n");
        exit(EXIT_FAILURE);
    }
    simplify(result);
}

/**
    This function prints a fraction in the format "numerator/denominator".
    @param f Fraction to print
    
 */
void print_fraction(const Fraction f) 
{
    printf("%lld/%lld\n", f[0], f[1]);
}
