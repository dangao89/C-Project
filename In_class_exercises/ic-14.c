#include <stdio.h>
#include <string.h>

int main() {
    char binary[17]; // 16 digits max + 1 for '\0'
    int decimal = 0;

    // Read binary string
    scanf("%16s", binary);

    int length = strlen(binary); 

    // Loop through each character in the binary string
    for (int i = 0; i < length; i++) {
        // Convert character to digit (0 or 1)
        if (binary[i] == '1' || binary[i] == '0') {
            decimal = decimal * 2 + (binary[i] - '0');
        } else {
            printf("Invalid input.\n");
            return 1;
        }
    }
    // Output the decimal value
    printf("%d\n", decimal);
    return 0;
}
