#ifndef MMU_H
#define MMU_H
#include <pmm.h>
extern void setup_tables();
extern void paging();
void init_mmu(void);
#endif
