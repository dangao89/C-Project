#include <stdio.h>
#include <ctype.h>  // For isprint()

int main() {
    // Loop through ASCII codes 0 to 127
    for (int i = 0; i <= 127; i++) {
        char ch = (char) i;
        if (isprint(ch)) {
            // Print the code as a 3-digit right-aligned number, followed by the character
            printf("%3d: %c\n", i, ch);
        }
    }
    return 0;
}


/** 
int main() {
    // Loop through ASCII codes 0 to 127
    for (int i = 0; i <= 127; i++) {
        if (isprint(i)) {
            // Print the code as a 3-digit right-aligned number, followed by the character
            printf("%3d: %c\n", i, i);
        }
    }
    return 0;
}

*/