#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "string.h"

static long SECRET = 0xdeadbeef;

void replace_nl(char* buf) {
    char* nl = strchr(buf, '\n');
    if (nl) {
        *nl = '\0';
    }
}

int main() {
    char buf[0x20];
    puts("Hello! Can I tell you a secret?");
    read(0, buf, sizeof(buf));
    replace_nl(buf);
    if (!strcmp(buf, "y")) {
        printf("My favorite number is %lx\n", SECRET);
        puts("Can you read that back to me?");
        read(0, buf, sizeof(buf));
        replace_nl(buf);
        long num = strtol(buf, NULL, 16);
        if (num == SECRET) {
            puts("Yeah, that's it!");
        } else {
            printf("Nope, not quite. You entered %lx\n", num);
        }
    } else {
        puts("Ok! Nevermind then");
    }
    return 0;
}
