#include "system_calls.h"
#include "stdio.h"

int main(int argc, char *argv[], char *env[])
{
    const char buffer[] = "Hello World !!\n";

    // directly call system calls
    write(STDOUT_FILENO, buffer, sizeof(buffer));

    // fputs is a wrapper, the bottom still calls write
    fputs(buffer, stdout);

    // printf is a wrapper of fputs with buffer mechanism
    printf("%s\n", buffer);

    return 0;
}