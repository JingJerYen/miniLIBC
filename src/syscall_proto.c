#include "syscall_proto.h"

// TODO : check rax and fill to errno
// TODO : can we minimize repeat?

long _syscall0(long num)
{
    register long rax __asm__("rax") = num;
    __asm__ volatile(
        "syscall"
        : "+r"(rax)
        :);
    return rax;
}

long _syscall1(long num, long arg1)
{
    register long rax __asm__("rax") = num;
    register long rdi __asm__("rdi") = arg1;
    __asm__ volatile(
        "syscall"
        : "+r"(rax)
        : "r"(rdi));
    return rax;
}

long _syscall2(long num, long arg1, long arg2)
{
    register long rax __asm__("rax") = num;
    register long rdi __asm__("rdi") = arg1;
    register long rsi __asm__("rsi") = arg2;
    __asm__ volatile(
        "syscall"
        : "+r"(rax)
        : "r"(rdi), "r"(rsi));
    return rax;
}

long _syscall3(long num, long arg1, long arg2, long arg3)
{
    register long rax __asm__("rax") = num;
    register long rdi __asm__("rdi") = arg1;
    register long rsi __asm__("rsi") = arg2;
    register long rdx __asm__("rdx") = arg3;
    __asm__ volatile(
        "syscall"
        : "+r"(rax)
        : "r"(rdi), "r"(rsi), "r"(rdx));
    return rax;
}