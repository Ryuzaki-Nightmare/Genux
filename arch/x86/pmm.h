#ifndef PMM_H
#define PMM_H

#include <stdint.h>
#include <stdio.h>
#include <boot.h>
union DividedChar {
    unsigned char full_byte;     
    struct {
        unsigned char bit0 : 1; // 1 bit
        unsigned char bit1 : 1; // 1 bit
    } bits;
};

typedef unsigned long long EFI_PHYSICAL_ADDRESS;
typedef unsigned long long EFI_VIRTUAL_ADDRESS;
typedef enum{
    EfiReservedMemoryTime,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPersistentMemory,
    EfiUnacceptedMemoryType,
    EfiMaxMemoryType
}EFI_MEMORY_TYPE;
typedef struct{
    uint32_t Type;
    EFI_PHYSICAL_ADDRESS PhysicalStart;
    EFI_VIRTUAL_ADDRESS VirtualStart;
    uint64_t NumberOfPages;
    uint64_t Attribute;
} MEMORY_DESCRIPTOR;



//MEMORY_DESCRIPITOR.Attribute Definitions
#define EFI_MEMORY_UC              0x0000000000000001
#define EFI_MEMORY_WC              0x0000000000000002
#define EFI_MEMORY_WT              0x0000000000000004
#define EFI_MEMORY_WB              0x0000000000000008
#define EFI_MEMORY_UCE             0x0000000000000010
#define EFI_MEMORY_WP              0x0000000000001000
#define EFI_MEMORY_RP              0x0000000000002000
#define EFI_MEMORY_XP              0x0000000000004000
#define EFI_MEMORY_NV              0x0000000000008000
#define EFI_MEMORY_MORE_RELIABLE   0x0000000000010000
#define EFI_MEMORY_RO              0x0000000000020000
#define EFI_MEMORY_SP              0x0000000000040000
#define EFI_MEMORY_CPU_CRYPTO      0x0000000000080000
#define EFI_MEMORY_RUNTIME         0x8000000000000000
#define EFI_MEMORY_ISA_VALID       0x4000000000000000
#define EFI_MEMORY_ISA_MASK        0x0FFFF00000000000


void init_pmm(BootInfo Info);
uint64_t pmm_alloc(uint64_t Size);
void pmm_free(uint64_t Page,uint64_t Size);


#endif
