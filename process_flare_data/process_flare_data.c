/**
    @file process_flare_data.c
    This program processes solar flare data from input file, formats dates and fractions, 
    and prints the results to output file.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fraction.h"

#define MAX_LINE 512 // Maximum line length for reading
#define WIDTH 39 // Output width for formatted fractions
#define SECOND_PER_DAY 86400 // Seconds in a day
#define MAX_DATE_FORMAT 32 // Maximum length for date format string
#define MAX_HEADER_LINES 7 // Number of header lines to skip
/**
    Converts a time string (HH:MM:SS) to total seconds.
    @param time_str The time string to convert.
    @return total seconds 
 */
int convert_time_to_seconds(const char *time_str) {
    int h, m, sec;
    sscanf(time_str, "%d:%d:%d", &h, &m, &sec);
    return h * 3600 + m * 60 + sec;
}

/**
    Converts a date string into a specified format.
    @param input the input date string
    @param output the output buffer for the formatted date
    @param format the desired output format
 */
void convert_date_format(const char *input, char *output, const char *format) {
    // Buffer to store the 3-letter month abbreviation
    char mon_str[4];
    int day, year, month = 0; 
     
    // Array of 3-letter month abbreviations
    static const char *months[] = {
        "Jan","Feb","Mar","Apr","May","Jun",
        "Jul","Aug","Sep","Oct","Nov","Dec"
    };
    // Read the date string into day, month abbreviation, and year
    sscanf(input, "%d-%3s-%d", &day, mon_str, &year);

    // Convert the month abbreviation to a number value (1 -12)
    for (int i = 0; i < 12; i++) {
        if (strcmp(mon_str, months[i]) == 0) {
            month = i + 1;
            break;
        }
    }
    // Format the output string based on the specified format
    if (strcmp(format, "YYYY-MM-DD") == 0)
        sprintf(output, "%04d-%02d-%02d", year, month, day);
    else if (strcmp(format, "MM-DD-YYYY") == 0)
        sprintf(output, "%02d-%02d-%04d", month, day, year);
    else if (strcmp(format, "MM/DD/YYYY") == 0)
        sprintf(output, "%02d/%02d/%04d", month, day, year);
    else
        strcpy(output, input);
}
 
/**
    Formats a fraction into a centered string representation.
    @param f the fraction array
    @param buf buffer to hold the formatted output 
 */
void center_format_fraction(const Fraction f, char *buf) {
    // Buffers to store the string representations of the numerator(f[0]) and denominator(f[1])
    char str_f0[21], str_f1[21];
    
    // Convert f[0] and f[1] to strings
    sprintf(str_f0, "%lld", f[0]);
    sprintf(str_f1, "%lld", f[1]);

    // Calculate the lengths of f[0] and f[1] strings
    int len_f0 = strlen(str_f0);
    int len_f1 = strlen(str_f1);

    // Determine the position of slash '/' and calculate spaces on its left and right sides
    int slash_pos = WIDTH / 2;
    int left_spaces = slash_pos - len_f0;
    int right_spaces = WIDTH - slash_pos - 1 - len_f1;
    
    // Format the centered fraction into the output buffer
    sprintf(buf, "%*s%s/%s%*s", left_spaces, "", str_f0, str_f1, right_spaces, "");
}

/**
    Program starting point. Reads solar flare data from input file, processes it, and prints formatted output.
    @param argc number of command-line arguments
    @param argv list of command-line arguments
    @return program exit status
 */
int main(int argc, char *argv[]) {
    // Check for correct number of command-line arguments
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file> [--date-format=FORMAT]\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Get the input filename
    const char *filename = argv[1];
    // Default date format is empty
    char date_format[MAX_DATE_FORMAT] = "";
    // Check for date format argument
    if (argc == 3 && strncmp(argv[2], "--date-format=", 14) == 0) {
        if (strlen(argv[2] + 14) == 10) { // Valid date format length
            strcpy(date_format, argv[2] + 14); // Copy the date format
        } else {
            fprintf(stderr, "Error: Invalid date format. \n");
            return EXIT_FAILURE;
        }
    }

    // Open the input file for reading
    FILE *fp = fopen(filename, "r");
    // Check if file opened successfully
    if (fp == NULL) {
        printf("Error opening file");
        return EXIT_FAILURE;
    }

    // Declare a buffer to read lines from the file
    char line[MAX_LINE];
    // Loop to skip the header lines
    for (int i = 0; i < 7; i++) {
        fgets(line, sizeof(line), fp);
    }

    // Declare variables to hold the data fields
    char flare_id[32], start_date[32], finalFormatted_date[32], start_time[16], peak_time[16], end_time[16];
    long long peak_int = 0, peak_decimal = 0, avg_int = 0, avg_decimal = 0;
    char detectors[32];

    // Loop to read and process each line of the file
    while (1) {
        // Read a line from the file
        int num_fields = fscanf(fp, "%31s %31s %15s %15s %15s %lld.%lld %lld.%lld %31[^\n]",
            flare_id, start_date, start_time, peak_time, end_time,
            &peak_int, &peak_decimal, &avg_int, &avg_decimal, detectors);

        // Check for end of file
        if (num_fields == EOF) {
            break;
        }
        // Check for line format error
        if (num_fields != 10) {
            fprintf(stderr, "Warning: line format error, skipping line.\n");
            fgets(line, sizeof(line), fp); // Skip the invalid line
            continue;
        }
        // Convert the date format
        convert_date_format(start_date, finalFormatted_date, date_format);

        // Declare DecimalParts structure to hold integer parts, decimals parts and lengths
        DecimalParts peak_parts = {peak_int, peak_decimal, 3};
        DecimalParts avg_parts = {avg_int, avg_decimal, 10};
        // Declare Fraction structure to hold the fractions
        Fraction peak_frac, avg_count_rate_frac, duration_frac, total_count_frac;

        // Convert peak and average decimal parts to fractions
        from_decimal_parts(peak_parts, peak_frac);
        from_decimal_parts(avg_parts, avg_count_rate_frac);

        // Convert time strings to seconds and calculate the total duration
        int start_in_sec = convert_time_to_seconds(start_time);
        int end_in_sec = convert_time_to_seconds(end_time);
        int duration = end_in_sec - start_in_sec;
        if (duration < 0) {
            duration += SECOND_PER_DAY; // Handle overnight
        }
        // Convert duration to fraction
        duration_frac[0] = duration;
        duration_frac[1] = 1;

        // Calculate total count in fraction
        multiply_fraction(avg_count_rate_frac, duration_frac, total_count_frac);

        // Declare buffers for formatted output
        char peak_fmt[WIDTH + 1], avg_count_rate_fmt[WIDTH + 1], total_count_fmt[WIDTH + 1];
        
        // Call the center_format_fraction function to format the fractions
        center_format_fraction(peak_frac, peak_fmt);
        center_format_fraction(avg_count_rate_frac, avg_count_rate_fmt);
        center_format_fraction(total_count_frac, total_count_fmt);
 
        // If date format is not empty, print the formatted output with date. Otherwise, print with start date
        if (date_format[0] != '\0') {        
            printf("%12s%11s%9s%9s%9s%6d %4lld.%03lld (%39s) %7lld.%010lld (%39s) (%39s) %12s\n",
            flare_id, finalFormatted_date, start_time, peak_time, end_time, duration,
            peak_int, peak_decimal, peak_fmt, avg_int, avg_decimal, avg_count_rate_fmt, total_count_fmt, detectors);
        } else {
            printf("%12s%12s%9s%9s%9s%6d %4lld.%03lld (%39s) %7lld.%010lld (%39s) (%39s) %12s\n",
            flare_id, start_date, start_time, peak_time, end_time, duration,
            peak_int, peak_decimal, peak_fmt, avg_int, avg_decimal, avg_count_rate_fmt, total_count_fmt, detectors);
        }        
    }

    fclose(fp);
    return 0;
}
