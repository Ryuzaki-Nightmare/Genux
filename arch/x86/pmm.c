#include  <pmm.h>
/*
 * Physical Memory Manager code
 * Speak no to Vibecode
 *
 **/
void *MemoryMap;
UINTN MemoryMapSize;
UINTN DescriptorSize;
UINT32 DescriptorVersion;
MEMORY_DESCRIPTOR *desc;

uint32_t Type;
EFI_PHYSICAL_ADDRESS PhyStart;
EFI_PHYSICAL_ADDRESS  Initial;
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
    pmm_alloc(4);
}
void pmm_alloc(uint32_t Size){
    //KB = B = NumOfPages * 4096
    Initial = PhyStart;
    uint32_t Bytes = desc->NumberOfPages * 4096;
    UINTN offset = 0;
    uint64_t offset2 = Bytes + Initial;
    while(offset < MemoryMapSize){
        if(desc->Type == EfiConventionalMemory){
            //IF CAN USE MEMORY!!!
        }
    offset += DescriptorSize;
    desc = (MEMORY_DESCRIPTOR *) ((uint8_t*)desc + offset);
    }

} 

