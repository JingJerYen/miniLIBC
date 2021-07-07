#include "stdio.h"
#include "string.h"

int main(int argc, char const *argv[])
{
    for (int i = 0; i < argc; i++)
    {
        fputs(argv[i], stdout);
    }
    return 0;
}
