format ELF64
public mmu_init
public paging

section '.bss' writable align 4096
pml4_table:
    rb 4096
pdpt_table:
    rb 4096
pd_table:
    rb 4096
section '.data' writable
Mode_enable equ (1 shl 8) ; This is MSR
PSE equ (1 shl 4)
PAE equ (1 shl 5)
PGE equ (1 shl 7)
PKE equ (1 shl 22)
PKS equ (1 shl 24)
PE equ (1 shl 0)
PG equ (1 shl 31)
section '.text' executable
setup_page_tables:
      mov rax, pdpt_table
    or rax, 11b             
    mov [pml4_table], rax

   
    mov rax, pd_table
    or rax, 11b            
    mov [pdpt_table], rax

   
    mov rax, 0x0           
    or rax, 10000011b     
    mov [pd_table], rax

    ret
paging:
    mov rax, pml4_table
    mov cr3, rax

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
    
    mov ecx, 0xC0000080
    rdmsr
    or eax, Mode_enable 
    wrmsr
    
    mov rax,cr0
    mov rax,PE
    mov cr0,rax

    mov rax,cr0
    mov rax,PG
    mov cr0,rax

    ;finished Paging 
    ret
mmu_init:
    call paging
    call setup_page_tables

    ret


