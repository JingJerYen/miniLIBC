#ifndef SYSCALL_PROTO_H
#define SYSCALL_PROTO_H

long _syscall0 (long num);
long _syscall1 (long num, long arg1);
long _syscall2 (long num, long arg1, long arg2);
long _syscall3 (long num, long arg1, long arg2, long arg3);
long _syscall4 (long num, long arg1, long arg2, long arg3, long arg4);
long _syscall5 (long num, long arg1, long arg2, long arg3, long arg4, long arg5);
long _syscall6 (long num, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6);

#endif