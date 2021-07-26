#include "stdlib.h"
#include "stdio.h"

typedef void (*ctor_func)(void);

static void example_dtor(void)
{
    fputs("======= GLOBAL DTOR =======\n", stdout);
}

static void example_ctor(void)
{
    fputs("======= GLOBAL CTOR =======\n", stdout);
    atexit(example_dtor);
    // in c++, many ctor functions are registed to the ctor array
    // each is responsible for constructing one global object.
    // e.g. _GLOBAL__sub_I_[object name]
    // But that depends on gcc. So here we skip implement it,
    // only leave this function as an example.
}

ctor_func ctors_begin[2] __attribute__((section(".ctors"))) = {example_ctor, NULL};

void do_global_ctors()
{
    for (ctor_func *list = ctors_begin; *list != 0; list++)
    {
        (*list)();
    }
}