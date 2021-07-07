#ifndef IO_FLAGS
#define IO_FLAGS

// file flags are defined in <bits/fcntl.h>, and <linux/stat.h>,
// but include them would cause #error So we declare them here.

#define O_RDONLY 00   // read only
#define O_WRONLY 01   // write only
#define O_RDWR 02     // read and write
#define O_CREAT 0100  // if not exist, creat a new one
#define O_TRUNC 01000 // clean contents in the file

// file access mode
#define S_IRWXU 00700
#define S_IRUSR 00400
#define S_IWUSR 00200
#define S_IXUSR 00100

#define S_IRWXG 00070
#define S_IRGRP 00040
#define S_IWGRP 00020
#define S_IXGRP 00010

#define S_IRWXO 00007
#define S_IROTH 00004
#define S_IWOTH 00002
#define S_IXOTH 00001

#endif