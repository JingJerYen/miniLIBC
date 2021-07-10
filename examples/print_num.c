#include "string.h"
#include "stdio.h"

int main(int argc, char const *argv[])
{
    char buf[256];
    fputs(itoa(1995, buf, 10), stdout);
    fputs(itoa(-325, buf, 10), stdout);

    return 0;
}
