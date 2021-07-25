#include "stdio.h"
#include "string.h"

int main(int argc, char const *argv[], char *env[])
{
    char endl[] = "\n";

    for (int i = 0; i < argc; i++)
    {
        printf("Arg #%d : %s\n", i, argv[i]);
    }

    for (int i = 0; i < 3; i++)
    {
        printf("Arg #%d : %s\n", i, env[i]);
    }

    // This is tested OK.
    // fprintf(fopen("./tmp.txt", "w+"), "%s", "JJ cobra\n");

    return 0;
}