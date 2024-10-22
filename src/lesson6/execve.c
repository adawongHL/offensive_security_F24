#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"

// compile with `gcc execve.c -o execve`

int main() {
	char* argv[2];
	argv[0] = "/bin/sh";
	argv[1] = NULL;
	execve(argv[0], argv, NULL);
	return 0;
}
