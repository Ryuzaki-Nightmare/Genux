#include <mmu.h>
#include <stdint.h>
#include <stdio.h>
void init_mmu(void){
    paging();
    mmu_init();
    //kprintf("GG in Initial Paging and MMu");
}

