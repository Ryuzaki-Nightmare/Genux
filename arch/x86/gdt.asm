format ELF64
public load_GDT

section '.text' executable
load_GDT:
    lgdt [gdtr]
    push 0x08
    lea rax, [.label]
    push rax
    retfq

.label:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    xor ax, ax
    mov fs, ax
    mov gs, ax
    ret
section '.data' writeable
gdtr:
    dw gdt_end - gdt_start -1
    dq gdt_start

gdt_start:
    ;null segment
    dq 0x0000000000000000
    ;code segment
    dw 0xffff
    dw 0x0000
    db 0x00
    db 10011010b
    db 10101111b
    db 0x00

    ;data segment
    dw 0xffff
    dw 0x0000
    db 0x00
    db 10010010b
    db 11001111b
    db 0x00
gdt_end:
