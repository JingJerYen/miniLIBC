#include <linux/unistd.h>

#include "syscall_proto.h"
#include "system_calls.h"

void _exit(int code)
{
    system_call(__NR_exit, code);
}

int open(const char *path, int flags, mode_t mode)
{
    return system_call(__NR_open, (long)path, (long)flags, (long)mode);
}

ssize_t read(int fd, void *buffer, size_t count)
{
    return system_call(__NR_read, fd, (long)buffer, count);
}

ssize_t write(int fd, const void *buffer, size_t count)
{
    return system_call(__NR_write, fd, (long)buffer, count);
}

int close(int fd)
{
    return system_call(__NR_close, (long)fd);
}

int brk(void *end_data_segment)
{
    return system_call(__NR_brk, (long)end_data_segment);
}

void *mmap(void *address, size_t length, int protection, int flags,
           int file_descriptor, off_t offset)
{
    return (void *)system_call(__NR_mmap, address, length,
                               protection, flags,
                               file_descriptor, offset);
}