global _strncpy

section .text
_strncpy:
    mov rcx, rdx
    cmp rsi, rdi
    je quit

    cmp rsi, rdi

    jg def_copy

    mov rax, rdi
    sub rax, rsi

    cmp rax, rcx
    jge def_copy

rev_copy:
    add rdi, rcx
    dec rdi
    add rsi, rcx
    dec rsi
    std
def_copy:
    rep movsb
    cld

quit:
    ret