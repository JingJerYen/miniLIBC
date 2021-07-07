#ifndef SYSTEM_CALLS_H
#define SYSTEM_CALLS_H

#include "type.h"

void exit(int code);

int open(const char *path, int flags, mode_t mode);

int close(int fd);

off_t lseek(int fd, off_t offset, int whence);

/* Return the size of bytes that actually been read */
ssize_t read(int fd, void *buffer, size_t count);

/* Return the size of bytes that actually been written */
ssize_t write(int fd, const void *buffer, size_t count);

#endif