#include <linux/unistd.h>

#include "syscall_proto.h"
#include "system_calls.h"

void exit(int code)
{
    _syscall1(__NR_exit, code);
}

int open(const char *path, int flags, mode_t mode)
{
    return _syscall3(__NR_open, (long)path, (long)flags, (long)mode);
}

ssize_t read(int fd, void *buffer, size_t count)
{
    return _syscall3(__NR_read, fd, (long)buffer, count);
}

ssize_t write(int fd, const void *buffer, size_t count)
{
    return _syscall3(__NR_write, fd, (long)buffer, count);
}

int close(int fd)
{
    return _syscall1(__NR_close, (long)fd);
}