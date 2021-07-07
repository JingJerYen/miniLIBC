#include "stdio.h"
#include "string.h"
#include "system_calls.h"
#include "io_flags.h"

FILE *fopen(const char *filename, const char *mode)
{
    int flags = 0;
    int access = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                 S_IROTH | S_IWOTH; // rw-rw-rw-

    if (strcmp(mode, "r") == 0)
        flags |= O_RDONLY;

    if (strcmp(mode, "w") == 0)
        flags |= O_WRONLY | O_CREAT | O_TRUNC;

    if (strcmp(mode, "r+") == 0)
        flags |= O_RDWR | O_CREAT;

    if (strcmp(mode, "w+") == 0)
        flags |= O_RDWR | O_CREAT | O_TRUNC;

    long fd = open(filename, flags, access);
    return (FILE *)fd;
}

size_t fread(void *ptr, size_t size, size_t count, FILE *stream)
{
    // ignore the I/O buffer mechanism now.
    return read((long)stream, ptr, size * count);
}

size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream)
{
    // ignore the I/O buffer mechanism now.
    return write((long)stream, ptr, size * count);
}

int fclose(FILE *stream)
{
    return close((long)stream);
}

int fputs(const char *str, FILE *stream)
{
    int len = strlen(str);
    if (fwrite(str, sizeof(char), len, stream) != len)
        return EOF;
    return len;
}