#ifndef SYSCALL_PROTO_H
#define SYSCALL_PROTO_H

#if defined(__cplusplus)
extern "C"
{
#endif

    long system_call(long call_num, ...);

#if defined(__cplusplus)
} // extern C
#endif

#endif