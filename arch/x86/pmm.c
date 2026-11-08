#include  <pmm.h>
/*
 * Physical Memory Manager code
 * Speak no to Vibecode
 *
 **/
#define PAGE_SIZE 4096

void *MemoryMap;
UINTN MemoryMapSize;
UINTN DescriptorSize;
UINT32 DescriptorVersion;
MEMORY_DESCRIPTOR *desc;
uint64_t BitmapSize;
uint8_t *bitmap;
uint32_t Type;
EFI_PHYSICAL_ADDRESS PhyStart;
EFI_PHYSICAL_ADDRESS  Initial;
EFI_VIRTUAL_ADDRESS VirStart;
uint64_t NumberOfPages;
uint64_t Attribute;
void init_bitmap(void){
    uint64_t HighAddress = 0 ;
    uint64_t NumEntries = MemoryMapSize / DescriptorSize;

    for(int i = 0; i <= NumEntries; i++){
        MEMORY_DESCRIPTOR* desc = (MEMORY_DESCRIPTOR*) ((uint8_t*)MemoryMap + (i* DescriptorSize)) ;
        uint64_t MemoryEnd = desc->PhysicalStart + (desc-> NumberOfPages * 4096);
        if (MemoryEnd > HighAddress) {
            HighAddress = MemoryEnd;
        }
    }
    uint64_t TotalPages = HighAddress / 4096;
    BitmapSize = TotalPages / 64;
    if(TotalPages % 64 != 0 ) BitmapSize++;
    bitmap = (uint8_t *) BitmapSize;
    kprintf("one is %d\n second is %d",bitmap[1],BitmapSize);

}   
void pmm_alloc(uint32_t Size){



}

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
    init_bitmap();
}
