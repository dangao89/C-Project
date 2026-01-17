#include <stdio.h>
#include <limits.h>

int main() 
{
    printf("%-20s %-14s %-26s %-26s\n", "Type", "Size (bytes)", "Minimum Value", "Maximum Value");
    printf("---------------------------------------------------------------------------\n");

    printf("%-20s %-14lu %-26d %-26d\n", "signed char", sizeof(signed char), SCHAR_MIN, SCHAR_MAX);
    printf("%-20s %-14lu %-26d %-26u\n", "unsigned char", sizeof(unsigned char), 0, UCHAR_MAX);
    printf("%-20s %-14lu %-26d %-26d\n", "signed short", sizeof(signed short), SHRT_MIN, SHRT_MAX);
    printf("%-20s %-14lu %-26d %-26u\n", "unsigned short", sizeof(unsigned short), 0, USHRT_MAX);
    printf("%-20s %-14lu %-26d %-26d\n", "signed int", sizeof(signed int), INT_MIN, INT_MAX);
    printf("%-20s %-14lu %-26d %-26u\n", "unsigned int", sizeof(unsigned int), 0, UINT_MAX);
    printf("%-20s %-14lu %-26ld %-26ld\n", "signed long", sizeof(signed long), LONG_MIN, LONG_MAX);
    printf("%-20s %-14lu %-26d %-26lu\n", "unsigned long", sizeof(unsigned long), 0, ULONG_MAX);
    printf("%-20s %-14lu %-26lld %-26lld\n", "signed long long", sizeof(signed long long), LLONG_MIN, LLONG_MAX);
    printf("%-20s %-14lu %-26d %-26llu\n", "unsigned long long", sizeof(unsigned long long), 0, ULLONG_MAX);
    return 0;
}
