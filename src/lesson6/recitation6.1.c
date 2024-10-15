#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/mman.h"
#include "string.h"

// compile with gcc recitation6.1.c -o recitation6.1 -fno-pic -no-pie

int key = 0x1337c0d3;

void wrapper() {
    if (key == 0xdeadbeef) {
	    puts("Here's a shell!");
	    system("/bin/sh");
    }
}

int main() {
    void* rwx_page = mmap(0, 0x1000, PROT_READ|PROT_WRITE|PROT_EXEC,
                    MAP_ANON|MAP_PRIVATE, -1, 0);
    puts("Give me some shellcode to exec!");
    int read_bytes = read(0, rwx_page, 0x1000);
    // write `push &wrapper ; ret`
    // instruction for push is 0x68 followed by 4 address bytes (in LE)
    // instruction for ret is 0xc3
    *((char*)rwx_page + read_bytes) = 0x68;
    *(int*)((char*)rwx_page + read_bytes + 1) = (int)(&wrapper);
    *((char*)rwx_page + read_bytes + 5) = 0xc3;
    void (*f)() = rwx_page;
    f();
    puts("Did you get a shell??");
    return 0;
}

