#ifndef STDIO_H
#define STDIO_H

#include "type.h"

// This is provided by gcc compiler, not glibc.
// We need it to use va_list, because that strongly depends on
// compiler implementations and platform ABI.
#include <stdarg.h>

#define EOF (-1)
#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#if defined(__cplusplus)
extern "C"
{
#endif

    // FILE is actually a struct in glibc, but we ignore that, and make it
    // a number of file decriptor.
    typedef long FILE;

#define stdin ((FILE *)0)
#define stdout ((FILE *)1)
#define stderr ((FILE *)2)

    // Now only supports 4 modes r, r+, w, w+
    FILE *fopen(const char *filename, const char *mode);

    size_t fread(void *ptr, size_t size, size_t count, FILE *stream);

    size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream);

    int fclose(FILE *stream);

    // Writes the C string to stream.
    int fputs(const char *str, FILE *stream);

    int vfprintf(FILE *stream, const char *format, va_list arg);

    int printf(const char *format, ...);

    int fprintf(FILE *stream, const char *format, ...);

#if defined(__cplusplus)
} // extern C
#endif

#endif