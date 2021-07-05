#include "system_calls.h"

int main(int argc, char *argv[])
{
    const char buffer[] = "Hello World !!\n";
    write(1, buffer, sizeof(buffer));       
    return 0;
}