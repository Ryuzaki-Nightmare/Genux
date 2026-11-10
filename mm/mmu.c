#include <mmu.h>

void init_mmu(void){
    paging();
    mmu_init();
}

