#include "ASMfunc.h"

#include <cstddef>

size_t strlenASM(const char *str) {
    size_t len = 0;
    __asm__ (
            "mov rdi, %1\n"
            "mov rcx, -1\n"
            "xor al, al\n"
            "repne scasb\n"
            "not rcx\n"
            "dec rcx\n"
            "mov %0, rcx\n"
            : "=r" (len)
            : "r" (str)
            : "rcx", "rdi", "al"
            );
    return len;
}