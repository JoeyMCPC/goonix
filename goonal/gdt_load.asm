[BITS 64]
[GLOBAL gdt_load_and_jump]

SECTION .text
gdt_load_and_jump:
    mov rax, [rdi]      ; limit (ignored)
    mov rbx, [rdi+8]    ; base
    lgdt [rdi]
    ; no ljmp needed
    ret

