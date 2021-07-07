#include "string.h"

int strcmp(const char *p1, const char *p2)
{
    const unsigned char *s1 = (const unsigned char *)p1;
    const unsigned char *s2 = (const unsigned char *)p2;
    int ret = 0;

    while (*s1 != '\0')
    {
        if ((ret = *s1 - *s2) != 0)
            return ret;
        s1++, s2++;
    }
    return *s1 - *s2;
}

size_t strlen(const char *str)
{
    if (!str)
        return 0;
    size_t len = 0;
    while (*str++ != '\0')
        len++;
    return len;
}

char *strcpy(char *dest, const char *src)
{
    char *ret = dest;
    if (!src)
        return ret;
    while (*src != '\0')
        *dest++ = *src++;
    *dest = '\0';
    return ret;
}

char *itoa(int value, char *str, int base)
{
    char digit[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *head = str;

    // unreasonable base
    if (!str || base < 2 || base > 36)
        return str;

    // some checks on the sign
    if (value < 0)
    {
        // ignore this hard case
        if (base != 10)
            return str;
        *str++ = '-';
        head++;
        value = -value;
    }

    do
    {
        *str++ = digit[value % base];
        value /= base;
    } while (value > 0);
    *str = '\0';

    // reverse string
    str--;
    for (; head != str; head++, str--)
    {
        char tmp = *head;
        *head = *str;
        *str = tmp;
    }
    return str;
}