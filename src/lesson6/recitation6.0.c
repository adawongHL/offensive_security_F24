#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/mman.h"
#include "string.h"

char useful_string[] = "/bin/sh";
char command[] = "/bin/ls";

int wrapper() {
    char buf[0x40];
    int result;
    __asm__ (
        ".intel_syntax noprefix;"
        "mov rax, rsp;"
        "mov qword ptr [rax], rdi;"
        "mov qword ptr [rax + 8], 0x0;"
        "mov rsi, rsp;"
        "mov rdx, 0x0;"
        "mov rax, 0x3b;"
        "syscall;"
        ".att_syntax;"
        :"=r"(result));
    return result;
}

int main() {
    printf("I am going to execute %s\n", command);
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

