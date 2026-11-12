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
P equ (1 shl  0) ; Bit 0, Present Flag
RW equ (1 shl 1); Bit 1, Read/Write Flag
US equ (1 shl 2) ; Bit 2,is the User/Supervisor flag.
RSVD equ (1 shl 3) ; Bit 3, indicates whether a reserved bit was set in some page-structure entry
ID equ (1 shl 4) ; Bit 4, is the Instruction/Data flag (1=instruction fetch, 0=data access)
PK equ (1 shl 5); Bit 5, indicates a protection-key violation
SS equ (1 shl 6); Bit 6, indicates a shadow-stack access fault
SGX equ (1 shl 15); Bit 7, indicates an SGX violaton

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


