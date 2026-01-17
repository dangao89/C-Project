/**
     @file fraction.h
     This header file define functions for handling fractions, including conversion from decimal parts, arithmetic operations, and simplifications.
 */

typedef long long int64;
typedef int64 Fraction[2];   // [numerator, denominator]
typedef int64 DecimalParts[3]; // [integer_part, decimal_part, decimal_length]

// Convert a decimal number to a simplified fraction
void from_decimal_parts(const DecimalParts input, Fraction output);

// Create and simplify a fraction from two integers
void make_fraction(const Fraction input, Fraction output);

// Add two fractions: a + b → result
void add_fraction(const Fraction a, const Fraction b, Fraction result);

// Subtract two fractions: a - b → result
void subtract_fraction(const Fraction a, const Fraction b, Fraction result);

// Multiply two fractions: a * b → result
void multiply_fraction(const Fraction a, const Fraction b, Fraction result);

// Divide two fractions: a / b → result
void divide_fraction(const Fraction a, const Fraction b, Fraction result);

// Print a fraction in the form "numerator/denominator"
void print_fraction(const Fraction f);

// Simplify a fraction in-place
void simplify(Fraction f);

// Greatest common divisor (still raw int64s)
int64 gcd(int64 a, int64 b);
