// Func Principal do Kernel
#include "kernel.h"
volatile char last_key = 0;

void ISRs(void) {

  set_idt(0, isr0asm, 0x08, 0x8E, 0);
  set_idt(1, isr1asm, 0x08, 0x8E, 0);
  set_idt(2, isr2asm, 0x08, 0x8E, 0);
  set_idt(3, isr3asm, 0x08, 0x8E, 0);
  set_idt(4, isr4asm, 0x08, 0x8E, 0);
  set_idt(5, isr5asm, 0x08, 0x8E, 0);
  set_idt(6, isr6asm, 0x08, 0x8E, 0);
  set_idt(7, isr7asm, 0x08, 0x8E, 0);
  set_idt(8, isr8asm, 0x08, 0x8E, 0);
  set_idt(9, isr9asm, 0x08, 0x8E, 0);
  set_idt(10, isr10asm, 0x08, 0x8e, 0);
  set_idt(11, isr11asm, 0x08, 0x8e, 0);
  set_idt(12, isr12asm, 0x08, 0x8e, 0);
  set_idt(13, isr13asm, 0x08, 0x8e, 0);
  set_idt(14, isr14asm, 0x08, 0x8e, 0);
  set_idt(15, isr15asm, 0x08, 0x8e, 0);
  set_idt(16, isr16asm, 0x08, 0x8e, 0);
  set_idt(17, isr17asm, 0x08, 0x8e, 0);
  set_idt(18, isr18asm, 0x08, 0x8e, 0);
  set_idt(19, isr19asm, 0x08, 0x8e, 0);
  set_idt(20, isr20asm, 0x08, 0x8e, 0);
  set_idt(21, isr21asm, 0x08, 0x8e, 0);
  set_idt(33, irq1asm, 0x8, 0x8e, 0);
}

void kernel_main(void) {
    vga_set_color(VGA_LIGHT_GREEN, VGA_BLACK);
  
    kprintf(">");                   
    vga_set_color(VGA_WHITE, VGA_BLACK);

    geral_pic();
    /*ISRs 1 -> 21 and IRQs*/
    ISRs();
    load_IDT();
    asm volatile("sti");

    while (1) {
        __asm__ volatile("hlt");
        asm("cli");

        if (last_key != 0) {
        vga_set_color(VGA_WHITE, VGA_BLACK);
        vga_putchar(last_key);

        last_key = 0;
    }
        asm("sti");
  }
}
