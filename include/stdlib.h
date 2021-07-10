#ifndef STDLIB_H
#define STDLIB_H

#ifndef NULL
#define NULL (0)
#endif

#if defined(__cplusplus)
extern "C"
{
#endif

    void exit(int exit_code);

    int atexit(void (*func)(void));

    void do_global_ctors();

#if defined(__cplusplus)
}
#endif

#endif