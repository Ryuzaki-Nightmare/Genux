#ifndef PAGING_H
#define PAGING_H
#include <pmm.h>

extern void paging();
extern uint64_t pml4;
void init_vmm(void);
#endif
