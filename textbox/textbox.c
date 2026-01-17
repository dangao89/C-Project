/**
    @file textbox.c
    This program reads lines of text from the standard input and displays them inside a
    fixed-width box made of border characters. Each line is padded with spaces or truncated
    to fit the width.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/** Width of each line of text in the box. */
#define LINE_WIDTH 60

/** Symbol used to draw the border around the box. */
#define BORDER '*'

/**
    This function reads a line of text from the standard input and prints it in a box.
    The line is padded with spaces to fit the specified width.
    @return true if the line was read successfully, false if EOF is reached.
 */
bool paddedLine()
{
  int ch;
  int count = 0;

  // Read the first character
  ch = getchar();
  // If EOF is reached, return false
  if (ch == EOF) {
    return false;
  }

  // Print the left border
  putchar(BORDER);

  // Print the line of text, up to LINE_WIDTH characters
  for (count = 0; count < LINE_WIDTH; count++) {
    if (ch == '\n' || ch == EOF) {
      putchar(' ');
    } else {
        putchar(ch);
        ch = getchar();
    }
  }

  // If the line is longer than LINE_WIDTH, continue reading the rest of the line but not print it
  while (ch != '\n' && ch != EOF && count >= LINE_WIDTH) {
    ch = getchar();
  }

  // Print the right border
  putchar(BORDER);
  putchar('\n');
  return true;
}

/**
    This function prints a line of characters.
    @param ch The character to print.
    @param count The number of times to print the character.
 */
void lineOfChars(char ch, int count)
{
  // Print the border line
  for (int i = 1; i <= count; i++) {
    putchar(ch);
  }
  putchar('\n');
}

/**
    Program starting point, reads lines of text and display them in a box.
    @return EXIT_SUCCESS if the program runs successfully, otherwise EXIT_FAILURE.
 */
int main()
{
  // Print the top border line
  lineOfChars(BORDER, LINE_WIDTH + 2);

  bool flag = true;

  // Continue reading and printing lines until EOF is reached
  while (flag) {
    flag = paddedLine();
  }

  // Print the bottom border line
  lineOfChars(BORDER, LINE_WIDTH + 2);

  return EXIT_SUCCESS;
}
