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
uint64_t BitmapSize = 0 ;;
uint8_t *bitmap;
uint32_t Type;
uint64_t NumberOfPages;
uint64_t Attribute;
uint8_t NumberPage = 0 ;
int  init_bitmap(void){
    uint64_t HighAddress = 0 ;
    uint64_t NumEntries = MemoryMapSize / DescriptorSize;

    for(int i = 0; i < NumEntries; i++){
        MEMORY_DESCRIPTOR* desc = (MEMORY_DESCRIPTOR*) ((uint8_t*)MemoryMap + (i* DescriptorSize)) ;
        uint64_t MemoryEnd = desc->PhysicalStart + (desc-> NumberOfPages * 4096);
        if (MemoryEnd > HighAddress) {
            HighAddress = MemoryEnd;
        }
    }
    uint64_t TotalPages = HighAddress / 4096;
    BitmapSize = TotalPages / 8;
    if(TotalPages % 8 != 0 ) BitmapSize++;
    bitmap = (uint8_t *) BitmapSize;
    if (bitmap == NULL) return 1;
    for (int i = 0 ; i < BitmapSize;i++){
        bitmap[i] = 0; 
    }
    return 0;
}
void free_page(uint64_t Page){
    bitmap[Page] = 0 ;
}
void alloc_page(uint64_t page_size){
    union DividedChar x;
    x.full_byte = 5;
    x.bits.bit0; // 1
    x.bits.bit1; // 0
    bitmap[NumberPage]  = x.bits.bit0; // alloc 4kb
    NumberPage++;
}
uint64_t pmm_alloc(uint64_t Size){
    uint64_t start_page = NumberPage;
    UINTN offset = 0;
    while(offset < MemoryMapSize){
        if(desc->Type == EfiConventionalMemory){
            if (Size <= 4 ){
                alloc_page(Size); // alloc 4kb
            }
            if (Size > 4){
                //size > 4kb
                uint64_t PageNumber = (Size + 3 ) / 4;
                for(int i = 0; i < PageNumber; i++){
                    alloc_page(i);
                }
            }
        }
    offset += DescriptorSize;
    desc = (MEMORY_DESCRIPTOR *) ((uint8_t*)desc + DescriptorSize);
    }   
    return start_page;
}
void pmm_free(uint64_t Page,uint64_t Size){
    if(Size <= 4){
        free_page(Page);
    }
    if(Size > 4){
        uint64_t PageNumber = (Size + 3) / 4;
        for (uint64_t i = 0; i < PageNumber; i++) {
            free_page(Page + i);
        }
    }
}

void init_pmm(BootInfo Info){
    MemoryMap = (void*) Info.MemoryMap;
    MemoryMapSize =Info.MemoryMapSize;
    DescriptorSize    = Info.DescriptorSize;
    DescriptorVersion = Info.DescriptorVersion;
    desc = (MEMORY_DESCRIPTOR *) MemoryMap;
    Type = desc->Type;
    NumberOfPages = desc->NumberOfPages;
    Attribute = desc->Attribute;
    init_bitmap();
    
    //EXAMPLE USE pmm_alloc and pmm_free
    uint64_t minha_memoria = pmm_alloc(16); // Alloc 16kb
    pmm_free(minha_memoria, 16); //free 16kb
}
