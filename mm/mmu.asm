format ELF64
public setup_tables  
public paging

section '.bss' writable align 4096
align 4096
pml4: 
    rb 4096
pdpt:
    rb 4096
pt: 
    rb 4096
pd: 
     rb 4096

section '.data' writable
ADDR_MASK equ 0x000FFFFFFFFFF000; mask bits 12 to 51
Mode_enable equ (1 shl 8) ; This is MSR
PSE equ (1 shl 4)
PAE equ (1 shl 5)
PGE equ (1 shl 7)
PE equ (1 shl 0)
PG equ (1 shl 31)
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



section '.text' executable

setup_tables:
    ;define pml4, pdpt, pd and pt here!
    ret
paging:
    mov rax,cr4
    or rax,PSE 
    mov cr4,rax
    
    mov rax,cr4
    or rax,PAE
    mov cr4,rax

    mov ecx, 0xC0000080
    rdmsr
    or eax, Mode_enable 
    wrmsr

    mov rax,cr4
    or rax, PGE
    mov cr4,rax
    
    
    mov rax,cr0
    or rax,PE
    mov cr0,rax

    mov rax,cr0
    or eax,PG
    mov cr0,rax
    cli 
    lgdt[gdtr]
    ;far jump
    push 0x08             
    lea rax, [mmu_init]    
    push rax               
    retfq                 
mmu_init:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret


