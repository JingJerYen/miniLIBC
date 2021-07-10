// TODO : check rax and assign to errno

extern int errno;

long system_call(long call_num, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6)
{
    register long rax __asm__("rax") = call_num;
    register long rdi __asm__("rdi") = arg1;
    register long rsi __asm__("rsi") = arg2;
    register long rdx __asm__("rdx") = arg3;
    register long r10 __asm__("r10") = arg4;
    register long r8 __asm__("r8") = arg5;
    register long r9 __asm__("r9") = arg6;

    __asm__ volatile(
        "syscall"
        : "+r"(rax),
          "+r"(r8), "+r"(r9), "+r"(r10)
        : "r"(rdi), "r"(rsi), "r"(rdx));

    if (rax < 0)
        errno = -1;

    return rax;
}