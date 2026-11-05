#include  <pmm.h>
/*
 * Pmm code
 * Speak no to Vibecode
 *
 **/
/*
 * Alloc -> entregar endereco e tamanho (tamanho em kb) a ser allocado (kb = b, 1kb = 1000b)
 * 
 * */
void *MemoryMap;
UINTN MemoryMapSize;
UINTN DescriptorSize;
UINT32 DescriptorVersion;
MEMORY_DESCRIPTOR *desc;
uint32_t Type;
EFI_PHYSICAL_ADDRESS PhyStart;
EFI_VIRTUAL_ADDRESS VirStart;
uint64_t NumberOfPages;
uint64_t Attribute;
void init_pmm(BootInfo Info){
    MemoryMap = (void*) Info.MemoryMap;
    MemoryMapSize =Info.MemoryMapSize;
    DescriptorSize    = Info.DescriptorSize;
    DescriptorVersion = Info.DescriptorVersion;
    desc = (MEMORY_DESCRIPTOR *) MemoryMap;
    Type = desc->Type;
    PhyStart = desc->PhysicalStart;
    VirStart = desc->VirtualStart;
    NumberOfPages = desc->NumberOfPages;
    Attribute = desc->Attribute;

}
void pmm_alloc(uint32_t Size){

} 

