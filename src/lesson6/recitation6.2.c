#include "stdio.h"
#include "stdlib.h"

// compile with gcc -Wl,-z,relro -no-pie -fno-pic recitation6.2.c -o recitation6.2

int main() {
	puts("Nothing to see here!");
    puts("Just me printing my favorite string...");
    puts("/bin/sh");
	return 0;
}
