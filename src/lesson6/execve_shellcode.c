#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "sys/mman.h"

const char str[] = "/bin/sh";
long long two_quadwords[2] = { 0xdeadbeef, 0x1337c0d3 };

int main() {
    void* rwx_page;
    rwx_page = mmap(0, 0x1000, PROT_READ|PROT_WRITE|PROT_EXEC,
                    MAP_ANON|MAP_PRIVATE, -1, 0);
    puts("Give me some shellcode to exec!");
    read(0, rwx_page, 0x1000);
    void (*f)() = rwx_page;
    f();
    return 0;
}
