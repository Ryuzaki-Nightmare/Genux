format ELF64
;extern



extrn isr0
extrn isr1
extrn isr2
extrn isr3
extrn isr4
extrn isr5
extrn isr6
extrn isr7
extrn isr8
extrn isr9
extrn isr10
extrn isr11
extrn isr12
extrn isr13
extrn isr14
extrn isr15
extrn isr16
extrn isr17
extrn isr18
extrn isr19
extrn isr20
extrn isr21
extrn irq0
extrn keyboard
extrn irq2
extrn irq3
extrn irq4
extrn irq5
extrn irq6
extrn irq7
extrn irq8
extrn irq9
extrn irq10
extrn irq11
extrn irq12
extrn irq13
extrn irq14
extrn irq15

public isr0asm
public isr1asm
public isr2asm
public isr3asm
public isr4asm
public isr5asm
public isr6asm
public isr7asm
public isr8asm
public isr9asm
public isr10asm
public isr11asm
public isr12asm
public isr13asm
public isr14asm
public isr15asm
public isr16asm
public isr17asm
public isr18asm
public isr19asm
public isr20asm
public isr21asm
public irq0asm
public irq1asm

;64 Bits Macro!!


macro pushad{

    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
}

macro popad{
; macro func popad 64bits
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
}
section '.text' executable
isr0asm:
    pushad
    call isr0
    popad
    iretq
isr1asm:
    pushad
    call isr1
    popad
    iretq
isr2asm:
    pushad
    call isr2
    popad
    iretq
isr3asm:
    pushad
    call isr3
    popad
    iretq
isr4asm:
    pushad
    call isr4
    popad
    iretq
isr5asm:
    pushad
    call isr5
    popad
    iretq
isr6asm:
    pushad
    call isr6
    popad
    iretq
isr7asm:
    pushad
    call isr7
    popad
    iretq
isr8asm:
    pushad
    call isr8
    popad
    add rsp,8
    iretq
isr9asm:
    pushad
    call isr9
    popad
    iretq
isr10asm:
    pushad
    call isr10
    popad
    add rsp,8
    iretq
isr11asm:
    pushad
    call isr11
    popad
    add rsp,8
    iretq
isr12asm:
    pushad
    call isr12
    popad
    add rsp,8
    iretq
isr13asm:
    pushad
    call isr13
    popad
    add rsp,8
    iretq
isr14asm:
    pushad
    call isr14
    popad
    add rsp,8
    iretq
isr15asm:
    pushad
    call isr15
    popad
    iretq
isr16asm:
    pushad
    call isr16
    popad
    iretq
isr17asm:
    pushad
    call isr17
    popad
    iretq
isr18asm:
    pushad
    call isr18
    popad
    iretq
isr19asm:
    pushad
    call isr19
    popad
    iretq
isr20asm:
    pushad
    call isr20
    popad
    iretq
isr21asm:
    pushad
    call isr21
    popad
    iretq
irq0asm:
    ; 1.193182mhz -> PIT
    ; Five modes
    pushad
    call irq0
    mov al,0x20
    out 0x20,al ; EOI
    popad
    iretq
irq1asm:;func teclado
    pushad ; salva register
    in al, 0x60


    movzx rdi,al

    call keyboard
    mov al, 0x20

    out 0x20, al ;Eoi Pic
    popad ;pusha resister
    iretq

    ;Irq a Fazer
    ;irq2
    ;irq3
    ;irq4
    ;irq5
    ;irq6
    ;irq7
    ;irq8
    ;irq9
    ;irq10
    ;irq11
    ;irq12
    ;irq13
    ;irq14
    ;irq15
