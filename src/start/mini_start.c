#include "stdlib.h"

int main(int argc, char *argv[], char *env[]);
int minicrt_init_heap();

int mini_entry(void *stack_pointer)
{
	long count;
	char **arguments;
	char **environment;

	count = *((long *)stack_pointer);
	arguments = ((char **)stack_pointer) + 1;
	environment = arguments + count + 1;

	// initialize heap
	minicrt_init_heap();

	// initialize IO

	do_global_ctors();

	int ret = main(count, arguments, environment);

	exit(ret);
}