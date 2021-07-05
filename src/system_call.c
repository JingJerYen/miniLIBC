#include <linux/unistd.h>

#include "system_calls.h"
#include "syscall_proto.h"

void exit(int code) 
{
	_syscall1(__NR_exit, code);
}

ssize_t read(int fd, void* buffer, size_t count)
{
	return _syscall3(__NR_read, fd, (long) buffer, count);
}

ssize_t write(int fd, const void* buffer, size_t count)
{
	return _syscall3(__NR_write, fd, (long) buffer, count);
}
