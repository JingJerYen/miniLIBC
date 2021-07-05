extern int main(int argc, char * argv[]);

int mini_entry(void *stack_pointer)
{
	long count;
	char **arguments;
	char **environment;

	count = *((long *) stack_pointer);
	arguments = ((char **) stack_pointer) + 1;
	environment = arguments + count + 1;

	// initialize heap
	// initialize IO 

	return main(count, arguments);
}