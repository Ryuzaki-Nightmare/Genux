format ELF64
public load_IDT
extrn idt
section '.text' executable



align 8

KERNEL_CS = 0x08

; void load_IDT(void);
load_IDT:
    lidt [idtr]
    sti
    ret
section '.data' writeable
idtr:
    dw 256*16 -1
    dq idt
