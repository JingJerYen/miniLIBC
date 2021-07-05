/*
gcc linker defaults to use _start as entry point. 
Use -e [entry function] can assign another function as entry.

For x86_64, the ABI announces following rules :

1. User-level applications use as integer registers for passing 
the sequence %rdi, %rsi, %rdx, %rcx, %r8 and %r9. The kernel 
interface uses %rdi, %rsi, %rdx, %r10, %r8 and %r9.

2. The number of the syscall has to be passed in register %rax.

3. System-calls are limited to six arguments, no argument is passed
directly on the stack.

4. Returning from the syscall, register %rax contains the result of the system-call.
A value in the range between -4095 and -1 indicates an error, it is -errno

*/
#include <linux/unistd.h>

.text
.global _start

_start:
	xorq %rbp,%rbp    /* user code should mark the deepest stack frame
	                   * by setting the frame pointer to zero
	                   */

	movq %rsp,%rdi	  /* rdi is the first args passed to mini_start */

	call mini_entry 

	movq %rax,%rdi	  /* rdi is the args passed to system call "exit" */
	movq $__NR_exit,%rax  /* rax is the system call number */
	syscall