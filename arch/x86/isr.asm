;This archive 

;extern
extern isr0
extern isr1
extern isr2
extern isr3
extern isr4
extern isr5
extern isr6
extern isr7
extern isr8
extern isr9
extern isr10
extern isr11
extern isr12
extern isr13
extern isr14
extern isr15
extern isr16
extern isr17
extern isr18
extern isr19
extern isr20
extern isr21
extern irq0
extern keyboard
extern irq2
extern irq3
extern irq4
extern irq5
extern irq6
extern irq7
extern irq8
extern irq9
extern irq10
extern irq11
extern irq12
extern irq13
extern irq14
extern irq15




global isr0asm
global isr1asm
global isr2asm
global isr3asm
global isr4asm
global isr5asm
global isr6asm
global isr7asm
global isr8asm
global isr9asm
global isr10asm
global isr11asm
global isr12asm
global isr13asm
global isr14asm
global isr15asm
global isr16asm
global isr17asm
global isr18asm
global isr19asm
global isr20asm
global isr21asm
global irq0asm
global irq1asm

%macro  pushad 0 ;macro func pushad em 64bits

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
%endmacro

%macro popad 0 ; macro func popad 64bits
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

%endmacro
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
section .note.GNU-stack noalloc noexec nowrite progbits

    
