#include "stdio.h"
#include "string.h"

int main(int argc, char const *argv[])
{
    char endl[] = "\n";

    for (int i = 0; i < argc; i++)
    {
        fputs(argv[i], stdout);
        fputs(endl, stdout);
    }

    return 0;
}