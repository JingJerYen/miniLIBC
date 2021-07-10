#ifndef STRING_H
#define STRING_H

#include "type.h"

#if defined(__cplusplus)
extern "C"
{
#endif

    int strcmp(const char *p1, const char *p2);

    char *strcpy(char *dest, const char *src);

    size_t strlen(const char *str);

    char *itoa(int value, char *str, int base);

#if defined(__cplusplus)
} // extern C
#endif

#endif