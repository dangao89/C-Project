#include<stdio.h>

int main()
{
    FILE *in = fopen("1.in", "r");
    FILE *out = fopen("1.out", "w");

    if (!in || !out) {
        return 1;

    }

    char buffer[100];
    fgets(buffer, sizeof(buffer), in);
    int i;
    while (buffer[i] == '\n'){
            buffer[i] = '\0';  
            break;

        }
        fprintf(out, "%s!", buffer);     

    fclose(in);
    fclose(out);
    return 0;
}
        