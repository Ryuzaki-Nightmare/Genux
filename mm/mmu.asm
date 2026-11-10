format ELF64
public mmu_init
public paging

section '.bss' writable

Mode_enable equ (1 << 8) ; This is MSR
PSE equ (1 shl 4)
PAE equ (1 shl 5)
PGE equ (1 shl 7)
PKE equ (1 shl 22)
PKS equ (1 shl 24)
section '.text' executable

paging:
    mov rax,cr4
    or rax,PSE 
    mov cr4,rax
    
    mov rax,cr4
    or rax,PAE
    mov cr4,rax

    mov rax,cr4
    or rax, PGE
    mov cr4,rax

    mov rax,cr4
    or rax,PKE
    mov cr4,rax

    mov rax,cr4
    or rax,PKS
    mov cr4,rax
    ;finished Paging 
    ret
mmu_init:
    call paging
    call print
    ret


