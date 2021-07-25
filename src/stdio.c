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

// I design a simple IO buffer, nothing related with glibc.
#define BUFFER_SIZE 8
static char buffer[BUFFER_SIZE];
static int buffer_len = 0;

static int fputc_with_buffer(char c, FILE *stream)
{
    int context_len = 0;
    buffer[buffer_len++] = c;

    if (c == '\n' || c == '\0' || buffer_len >= BUFFER_SIZE - 1)
    {
        buffer[buffer_len] = '\0';
        context_len += fputs(buffer, stream);
        buffer_len = 0;
    }

    return context_len;
}

static int fputs_with_buffer(const char *p, FILE *stream)
{
    int context_len = 0;

    if (!p)
        return -1;

    while (*p != '\0')
    {
        char c = *p++;
        buffer[buffer_len++] = c;

        if (c == '\n' || buffer_len >= BUFFER_SIZE - 1)
        {
            buffer[buffer_len] = '\0';
            context_len += fputs(buffer, stream);
            buffer_len = 0;
        }
    }

    return context_len;
}
#undef BUFFER_SIZE

int vfprintf(FILE *stream, const char *format, va_list arg_list)
{
    if (!format)
        return 0;

    int ret = 0; // total length
    char arg_buffer[32];

    for (const char *p = format; *p != '\0'; p++)
    {
        switch (*p)
        {
        case '%':
            p++;

            switch (*p)
            {
            case 'd':
                itoa(va_arg(arg_list, int), arg_buffer, 10);
                ret += fputs_with_buffer(arg_buffer, stream);
                break;

            case 's':
                ret += fputs_with_buffer(va_arg(arg_list, const char *), stream);
                break;

            default:
                ret += fputc_with_buffer('%', stream);
                ret += fputc_with_buffer(*p, stream);
                break;
            }
            break;

        default:
            // normal char
            ret += fputc_with_buffer(*p, stream);
            break;
        }
    }

    ret += fputc_with_buffer('\0', stream);

    return ret;
}

int printf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    return vfprintf(stdout, format, ap);
}

int fprintf(FILE *stream, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    return vfprintf(stream, format, ap);
}