/* We skip lots of stuff such as __cxa_exit, which are in gcc, 
   because they're very close to the language properties (global
   contruction and destruction of C++ objects) and also related
   with the construct and destruct of dynamic library.
   So, this file only demonstrates the key functionality.
*/

#include "stdlib.h"
#include "system_calls.h"

typedef void (*atexit_func_t)(void);

typedef struct _func_node
{
    atexit_func_t func;
    struct _func_node *next;
} func_node;

// registered function list
static func_node *atexit_list = 0;

/* Call functions in atexit_list */
static void mini_libc_call_exit_list()
{
    for (func_node *node = atexit_list; node != 0; node = node->next)
    {
        node->func();
    }
}

/* "preppend" func to the atexit_list,
    because the order of destructors should be reversal of constructors
 */
int atexit(atexit_func_t func)
{
    if (!func)
        return -1;

    // func_node *node = (func_node *)malloc(sizeof(func_node));
    func_node *node;

    // if malloc fail
    if (!node)
        return -1;

    node->func = func;
    node->next = atexit_list;
    atexit_list = node;
    return 0;
}

void exit(int exit_code)
{
    mini_libc_call_exit_list();
    _exit(exit_code);
}