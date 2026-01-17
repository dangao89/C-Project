/**
    @file pi.c
    This program compute the value of pi using the Leibniz formula. 
    The program reads input from the user to determine how many terms to compute or if it should continue until convergence.
    The output is formatted as a table showing the number of terms and the current estimate of pi.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** This constant defines the threshold for convergence. */
#define THRESHOLD 1e-6

/** This constant defines the maximum length of a line in the input. */
#define MAX_LINE_LENGTH 100

/**
    This constant defines the convergence mode. Convergence mode is when the program continues to compute terms until the 
    difference between two consecutive estimates of pi is less than the threshold.
 */
#define CONVERGE_MODE -1

/**
    This function reads the number of terms to compute from the user. If the user enters 'a', it sets the mode to convergence mode. 
    Otherwise, it print invalid input and exits the program.
    @return A positive integer if the input is valid and greater than 0.
    @return -1 if the user enters 'a' for convergence mode.
 */
int getTermLimit()
{
    int input;
    char next_char;
    
    // Try to read an integer from the user input.
    if (scanf("%d", &input) == 1) {
        // Check if the input is a positive integer.
        if (input <= 0) {
            printf("Invalid input\n");
            exit(1);
        }
        // Read the next character to check for invalid input.
        next_char = getchar();
        if (next_char != '\n' && next_char != ' ' && next_char != '\t' && next_char != EOF) {
            printf("Invalid input\n");
            exit(1);
        }
        // Return the number of terms to compute.
        return input;
     } else {
        char ch;
        // If the input is not an integer, check if it is 'a' for convergence mode.
        scanf(" %c", &ch);
        if (ch == 'a') {
            // Skip whitespaces and check for invalid input.
            do {
                next_char = getchar();
            } while (next_char == ' ' || next_char == '\t' || next_char == '\r');
            
            // If the next character is not a newline or EOF, print invalid input and exit.
            if (next_char != '\n' && next_char != EOF) {
                printf("Invalid input\n");
                exit(1);
            }
            // Return the convergence mode constant.
            return CONVERGE_MODE;
        } else {
            printf("Invalid input\n");
            exit(1); // Exit if the input is not valid.
        }
    }
}

/**
    This function computes the k-th term of the Leibniz formula for pi.
    @param k The term index.
    @return The k-th term of the series.
 */
double computePiTerm(int k)
{
    // Sign is determined by whether k is even or odd.
    double sign = (k % 2 == 0) ? 1.0 : -1.0;
    // Calculate the k-th term using the Leibniz formula.
    return sign * (4.0 / (2 * k + 1));
}

/**
    This function computes the absolute difference between two approximations.
    @param a The first approximation.
    @param b The second approximation.
    @return The absolute difference |a - b|. 
 */
double difference(double a, double b)
{
    // Calculate the absolute difference between two values and return it.
    return fabs(a - b);
}

/**
    This function prints the header of the table.
    The header includes the column names "terms" and "pi".
 */
void tableHeader()
{
    // Print "terms |       pi" and a separator line as the table header.
    printf("terms   |       pi\n");
    printf("--------+----------------\n");
}

/**
    This function prints a row in the table with the number of terms and the current estimate of pi.
    @param terms The number of terms computed so far.
    @param piEstimate The current estimate of pi.
 */
void tableRow(int terms, double piEstimate)
{
    // Print the table row with formatted output
    printf("%7d | %15.13f\n", terms, piEstimate);
}

/**
    The main function serves as the entry point of the program.
    It orchestrates the computation of pi using the Leibniz formula based on user input.
    It handles both convergence mode and a fixed number of terms.
    @return EXIT_SUCCESS if the program completes successfully.   
 */
int main()
{
    // Call the function to get the number of terms to compute.
    int limit = getTermLimit();

    // Initialize variables for pi, the previous value of pi, and the term index.
    double pi = 0.0;
    double prevPi = 0.0;
    int k = 0;

    // Print the table header.
    tableHeader();

    // Check if the user requested convergence mode or a fixed number of terms.
    if (limit == CONVERGE_MODE) {
        // Loop until convergence is achieved.
        while (1) {
            // Compute the k-th term of the series.
            double term = computePiTerm(k); 
            // Update the value of pi by adding the term.
            pi += term;
            // Print the current term and the estimate of pi.
            tableRow(k + 1, pi);

            // Check for convergence by comparing the absolute difference between the current and previous estimates of pi.
            if (difference(pi, prevPi) < THRESHOLD) {
                break;
            }

            // Update the previous value of pi for the next iteration and increment the term index.
            prevPi = pi;
            k ++;
        }
    } else {
        // Loop for a fixed number of terms.
        for (k = 0; k < limit; k ++) {
            // Compute the k-th term of the series.
            double term = computePiTerm(k);
            pi += term;
            // Print the current term and the estimate of pi.
            tableRow(k + 1, pi);
        }
    }

    return EXIT_SUCCESS;
}
