// decompiler_example.c
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// gcc decompiler_example.c -o decompiler_example

#define BUFLEN 0x20

void say_hello(char* buf) {
    char hello[6] = "Hello\0";
    printf("%s %s\n", hello, buf);
}

void get_name(char* buf) {
    printf("What is your name?\n > ");
    fgets(buf, BUFLEN, stdin);
    char* newline = strchr(buf, '\n');
    if (newline) { *newline = '\0'; }
}

int main() {
    char buf[BUFLEN];
    memset(buf, 0, BUFLEN);
    get_name(buf);
    say_hello(buf);
    return 0;
}
