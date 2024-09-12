#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// gcc recitation2.1.c -o recitation2.1

long long value = 0xdeadbeef1337c0de;
long long *value_ptr = &value;
long long **value_ptr_ptr = &value_ptr;

int main() {
    printf("The address of value is %p\n", &value);
    printf("The address of value_ptr is %p\n", &value_ptr);
    printf("The address of value_ptr_ptr is %p\n", &value_ptr_ptr);

    puts("");
    printf("The value of value is 0x%llx\n", value);
    printf("The value of value_ptr is 0x%llx\n", (long long)value_ptr);
    printf("The value of value_ptr_ptr is 0x%llx\n", (long long)value_ptr_ptr);

    puts("");
    puts("Let's set the value of value using value_ptr_ptr");
    **value_ptr_ptr = 0x1111111122222222;
    puts("The first * derferences value_ptr_ptr to get its value," \
         "the address of value_ptr");
    puts("The second * derferences value_ptr to get its value, " \
         "the address of value");
    puts("We then assign the value on the right of the = to that "\
         "address, which is value");

    puts("");
    printf("The value of value is 0x%llx\n", value);
    printf("The value of value_ptr is 0x%llx\n", (long long)value_ptr);
    printf("The value of value_ptr_ptr is 0x%llx\n", (long long)value_ptr_ptr);

    puts("This operation does not change either of the pointers");
    return 0;
}
