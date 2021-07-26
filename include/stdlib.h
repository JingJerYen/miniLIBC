#ifndef STDLIB_H
#define STDLIB_H

#ifndef NULL
#define NULL (0)
#endif

#include "type.h"

#if defined(__cplusplus)
extern "C"
{
#endif

    void exit(int exit_code);

    int atexit(void (*func)(void));

    void do_global_ctors();

    void *malloc(size_t size);

    void free(void *ptr);

#if defined(__cplusplus)
}
#endif

#endif