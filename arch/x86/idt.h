#ifndef IDT_H
#define IDT_H

#include <stdint.h>
#include <gop.h>
#include <stdbool.h>

extern void load_IDT(void);

void set_idt(int vector, void *isr_handler, uint16_t selector, uint8_t flags, uint8_t ist);


// Exceções da CPU
extern void isr0(void);   // #DE  Division Error
extern void isr1(void);   // #DB  Debug
extern void isr2(void);   // NMI  Non-Maskable Interrupt
extern void isr3(void);   // #BP  Breakpoint
extern void isr4(void);   // #OF  Overflow
extern void isr5(void);   // #BR  Bound Range Exceeded
extern void isr6(void);   // #UD  Invalid Opcode
extern void isr7(void);   // #NM  Device Not Available
extern void isr8(void);   // #DF  Double Fault
extern void isr9(void);   // Coprocessor Segment Overrun (obsoleto)
extern void isr10(void);  // #TS  Invalid TSS
extern void isr11(void);  // #NP  Segment Not Present
extern void isr12(void);  // #SS  Stack-Segment Fault
extern void isr13(void);  // #GP  General Protection Fault
extern void isr14(void);  // #PF  Page Fault
extern void isr15(void);  // Reserved
extern void isr16(void);  // #MF  x87 FP Exception
extern void isr17(void);  // #AC  Alignment Check
extern void isr18(void);  // #MC  Machine Check
extern void isr19(void);  // #XM  SIMD FP Exception
extern void isr20(void);  // #VE  Virtualization Exception
extern void isr21(void);  // #CP  Control Protection Exception

//ISR Asm

extern void isr0asm(void);
extern void isr1asm(void);
extern void isr2asm(void);
extern void isr3asm(void);
extern void isr4asm(void);
extern void isr5asm(void);
extern void isr6asm(void);
extern void isr7asm(void);
extern void isr8asm(void);
extern void isr9asm(void);
extern void isr10asm(void);
extern void isr11asm(void);
extern void isr12asm(void);
extern void isr13asm(void);
extern void isr14asm(void);
extern void isr15asm(void);
extern void isr16asm(void);
extern void isr17asm(void);
extern void isr18asm(void);
extern void isr19asm(void);
extern void isr20asm(void);
extern void isr21asm(void);

// IRQs (vetor = IRQ + 32)
void irq0(void);   // Timer
void irq1();   // Teclado
void irq2(void);   // Cascade
void irq3(void);   // COM2
void irq4(void);   // COM1
void irq5(void);   // LPT2 / Sound
void irq6(void);   // Floppy
void irq7(void);   // LPT1 / Spurious
void irq8(void);   // RTC
void irq9(void);   // ACPI
void irq10(void);  // Livre
void irq11(void);  // Livre
void irq12(void);  // Mouse PS/2
void irq13(void);  // FPU
void irq14(void);  // ATA Primário
void irq15(void);  // ATA Secundário


#endif
