#include <idt.h>



/*Estrutura do Descritor 64bits 
* De "https://wiki.osdev.org/Interrupt_Descriptor_Table#Structure_on_x86-64"
*/
typedef struct {
    uint16_t offset_1;
    uint16_t selector;
    uint8_t  ist;
    uint8_t  type_attributes;
    uint16_t offset_2;
    uint32_t offset_3;
    uint32_t zero;
} __attribute__((packed)) idt_entry_t;
idt_entry_t idt[256];

void set_idt(int vector, void *isr_handler, uint16_t selector, uint8_t flags, uint8_t ist) 
{
    uint64_t handler_addr = (uint64_t)isr_handler;
    
    idt[vector].offset_1 = (uint16_t)(handler_addr & 0xFFFF);
    idt[vector].selector = selector;
    idt[vector].ist = ist & 0x07;
    idt[vector].type_attributes = flags;
    idt[vector].offset_2 = (uint16_t)((handler_addr >> 16) & 0xFFFF);
    idt[vector].offset_3 = (uint32_t)(handler_addr >> 32);
    idt[vector].zero = 0;
}






extern void isr0(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("Division Error");
    asm("cli");
    asm("hlt");
}

extern void isr1(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("Debug");
    asm("cli");
    asm("hlt");
}

extern void isr2(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("NMI");
    asm("cli");
    asm("hlt");
}

extern void isr3(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("Breakpoint");
    asm("cli");
    asm("hlt");
}

extern void isr4(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("Overflow");
    asm("cli");
    asm("hlt");
}

extern void isr5(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("Bound Range Exceeded");
    asm("cli");
    asm("hlt");
}

extern void isr6(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("Invalid Opcode");
    asm("cli");
    asm("hlt");
}

extern void isr7(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("Device Not Available");
    asm("cli");
    asm("hlt");
}

extern void isr8(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("Double Fault");
    asm("cli");
    asm("hlt");
}

extern void isr9(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("Coprocessor Segment Overrun");
    asm("cli");
    asm("hlt");
}

extern void isr10(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("Invalid TSS");
    asm("cli");
    asm("hlt");
}

extern void isr11(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("Segment Not Present");
    asm("cli");
    asm("hlt");
}

extern void isr12(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("Stack-Segment Fault");
    asm("cli");
    asm("hlt");
}

extern void isr13(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("General Protection Fault");
    asm("cli");
    asm("hlt");
}

extern void isr14(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("Page Fault");
    asm("cli");
    asm("hlt");
}

extern void isr15(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("Reserved");
    asm("cli");
    asm("hlt");
}

extern void isr16(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("x87 FP Exception");
    asm("cli");
    asm("hlt");
}

extern void isr17(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("Alignment Check");
    asm("cli");
    asm("hlt");
}

extern void isr18(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("Machine Check");
    asm("cli");
    asm("hlt");
}

extern void isr19(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("SIMD FP Exception");
    asm("cli");
    asm("hlt");
}

extern void isr20(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("Virtualization Exception");
    asm("cli");
    asm("hlt");
}

extern void isr21(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("Control Protection Exception");
    asm("cli");
    asm("hlt");
}

//IRQS

extern void irq0(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("IRQ0: Timer");
    asm("cli");
    asm("hlt");
}
/*IRQ 1  in keyboard.c*/

extern void irq2(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("IRQ2: Cascade");
    asm("cli");
    asm("hlt");
}

extern void irq3(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("IRQ3: COM2");
    asm("cli");
    asm("hlt");
}

extern void irq4(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("IRQ4: COM1");
    asm("cli");
    asm("hlt");
}

extern void irq5(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("IRQ5: LPT2/Sound");
    asm("cli");
    asm("hlt");
}

extern void irq6(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("IRQ6: Floppy");
    asm("cli");
    asm("hlt");
}

extern void irq7(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("IRQ7: LPT1/Spurious");
    asm("cli");
    asm("hlt");
}

extern void irq8(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("IRQ8: RTC");
    asm("cli");
    asm("hlt");
}

extern void irq9(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("IRQ9: ACPI");
    asm("cli");
    asm("hlt");
}

extern void irq10(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("IRQ10: Livre");
    asm("cli");
    asm("hlt");
}

extern void irq11(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("IRQ11: Livre");
    asm("cli");
    asm("hlt");
}

extern void irq12(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("IRQ12: Mouse PS/2");
    asm("cli");
    asm("hlt");
}

extern void irq13(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("IRQ13: FPU");
    asm("cli");
    asm("hlt");
}

extern void irq14(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("IRQ14: ATA Primario");
    asm("cli");
    asm("hlt");
}

extern void irq15(void)
{
    vga_set_color(VGA_LIGHT_RED, VGA_BLACK);
    kprintf("IRQ15: ATA Secundario");
    asm("cli");
    asm("hlt");
}
