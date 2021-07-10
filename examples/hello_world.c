#include "system_calls.h"
#include "stdio.h"

int main(int argc, char *argv[], char *env[])
{
    const char buffer[] = "Hello World !!\n";

    // directly call system calls
    write(STDOUT_FILENO, buffer, sizeof(buffer));

    // fputs is a wrapper, the bottom still calls write
    fputs(buffer, stdout);

    return 0;
}