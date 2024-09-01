#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "string.h"

void replace_nl(char* buf) {
    char* nl = strchr(buf, '\n');
    if (nl) {
        *nl = '\0';
    }
}

int main() {
    char buf[0x20];
    puts("Hello! Tell me your name");
    read(0, buf, sizeof(buf));
    replace_nl(buf);
    printf("Hi %s! Do you like pwntools so far?\n", buf);
    read(0, buf, sizeof(buf));
    replace_nl(buf);
    if (!strcmp(buf, "y")) {
        puts("Great!");
    } else {
        puts("Bummer! Hopefully you'll grow to like it soon!");
    }
    return 0;
}
