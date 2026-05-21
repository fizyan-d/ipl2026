/*Design and test a structure bitfields.
Bitfield a;
a.firstbit = 1;*/
#include <stdio.h>
typedef struct {
    unsigned int firstbit : 1;  
    unsigned int second   : 3;  
    unsigned int third    : 4;  
} Bitfield;
int main() {
    Bitfield a;
    printf("--- Testing Bit-Fields ---\n\n");
    a.firstbit = 1;  
    a.second = 5;    
    a.third = 12;    
    printf("Successfully Stored Values:\n");
    printf("a.firstbit = %u\n", a.firstbit);
    printf("a.second   = %u\n", a.second);
    printf("a.third    = %u\n", a.third);
    printf("\n----------------------------------------\n");
    printf("Size of the Bitfield structure: %lu bytes\n", sizeof(Bitfield));
    printf("\n----------------------------------------\n");
    printf("Testing Overflow: Trying to store the number 3 into a 1-bit field...\n");
    a.firstbit = 3; 
    printf("Resulting value of a.firstbit: %u\n", a.firstbit);
    return 0;
}
