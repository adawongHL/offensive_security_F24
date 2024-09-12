#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// gcc recitation2.0.c -o recitation2.0

long long value = 0xdeadbeef1337c0de;

int main() {
    printf("64 bits prints %llx\n", value);
    printf("32 bits prints %x\n", (int)value);
    printf("16 bits prints %hx\n", (short)value);
    printf("8 bits prints %hhx\n", (char)value);
    printf("Next 8 bits prints %hhx\n", *((char*)(&value) + 1));
    printf("Second 32 bits prints %x\n", *((int*)(&value) + 1));
    return 0;
}
