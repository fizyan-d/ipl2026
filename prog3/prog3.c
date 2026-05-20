/*Write a function to print the bits in an integer.
Write a function to count no of 1 bits in an integer.
Understand little endian and big endian.
Understand bits in a negative integer.
Understand bits in a floating point number.
Understand bints in a negative floating point number.*/
#include <stdio.h>
void printBits(unsigned int num);
int countOneBits(unsigned int num);
void checkEndianness();
void printFloatBits(float num);

int main() {
    int posInt = 5;
    int negInt = -5;
    float posFloat = 5.25f;
    float negFloat = -5.25f;

    printf("--- 1. Endianness Check ---\n");
    checkEndianness();
    printf("\n");

    printf("--- 2. Printing & Counting Bits in Integers ---\n");
    printf("Positive Integer (%d):\n", posInt);
    printBits(posInt);
    printf("Number of 1 bits: %d\n\n", countOneBits(posInt));

    printf("--- 3. Bits in a Negative Integer (Two's Complement) ---\n");
    printf("Negative Integer (%d):\n", negInt);
    printBits(negInt);
    printf("Notice how the left side is filled with 1s (Sign Extension).\n\n");

    printf("--- 4. Bits in a Floating Point Number (IEEE 754) ---\n");
    printf("Positive Float (%.2f):\n", posFloat);
    printFloatBits(posFloat);
    printf("\n");

    printf("--- 5. Bits in a Negative Floating Point Number ---\n");
    printf("Negative Float (%.2f):\n", negFloat);
    printFloatBits(negFloat);
    printf("Notice that only the absolute first bit (Sign Bit) changed from 0 to 1!\n");

    return 0;
}
void printBits(unsigned int num) {
    for (int i = 31; i >= 0; i--) {
        int bit = (num >> i) & 1;
        printf("%d", bit);
        if (i % 4 == 0) printf(" ");
    }
    printf("\n");
}
int countOneBits(unsigned int num) {
    int count = 0;
    while (num > 0) {
        count += (num & 1);
        num = num >> 1;
    }
    return count;
}
void checkEndianness() {
    unsigned int x = 1;
    char *ptr = (char*)&x;
    if (*ptr == 1) {
        printf("System Architecture: Little Endian\n");
    } else {
        printf("System Architecture: Big Endian\n");
    }
}
void printFloatBits(float num) {
    unsigned int *floatAsInt = (unsigned int *)&num;
    for (int i = 31; i >= 0; i--) {
        int bit = ((*floatAsInt) >> i) & 1;
        printf("%d", bit);
        if (i == 31) printf(" [Sign] ");
        else if (i == 23) printf(" [Exponent] ");
        else if (i % 4 == 0 && i != 0) printf(" ");
    }
    printf(" [Mantissa]\n");
}
