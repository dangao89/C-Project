
/** 
// hello.c
// Name: Dan Gao
// Unity ID: dgao6
#include <stdio.h>

const char message[] = "Hello World.";

int main() {
    // Inline assembly to call puts(message)
    __asm__ __volatile__ (
        "mov %[msg], %%rdi\n\t"   // First argument in rdi (System V ABI)
        "call puts\n\t"           // Call puts from the C standard library
        :
        : [msg] "r" (message)     // Input: load address of 'message' into %rdi
        : "rdi"                  // Clobbered register
    );

    return 0;
}


*/


// swap.c
#include <stdio.h>

int main() {
    int a = 5, b = 10;
    scanf("%d%d", &a, &b);

    __asm__ __volatile__ (
        "movl %[a], %%eax\n\t"     // Move a into eax
        "xchgl %[b], %%eax\n\t"    // Exchange eax with b
        "movl %%eax, %[a]\n\t"     // Move result back to a
        : [a] "+r" (a), [b] "+r" (b)   // +r = read and write
        :
        : "%eax"                    // Clobbers eax
    );

    printf("%d %d", a, b);

    return 0;
}
