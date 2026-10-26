#include <vga.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static volatile uint16_t* const vga = (uint16_t*)0xB8000;
static uint8_t current_color = (VGA_RED | (VGA_BLACK << 4));

static uint16_t cursor;
static uint16_t prompt_start = 0;
void vga_set_color(uint8_t fg, uint8_t bg) {
    current_color = fg | (bg << 4);
}

void vga_putchar(char c) {
    if (c == 8) {  // backspace
        if (cursor > prompt_start) {
            cursor--;
            vga[cursor] = (current_color << 8) | ' ';
            if(teclas_count > 0)
                teclas[--teclas_count] = 0;
        }
        return;
    }

    if (c == 13) {  // enter
        vga_newline();
        shell(); // call func "shell" in kernel/terminal/shell.c
        vga_set_color(VGA_GREEN, VGA_BLACK);
        kprintf(">");
        prompt_start = cursor;
        memset(teclas,0,sizeof(teclas)); /*Zera array do teclado para comecar dnv a contagem*/
        teclas_count = 0;
        
        return;

    }
    if (c == 9) {  // tab   go to next  multiple of  4
        do {
            vga[cursor++] = (current_color << 8) | ' ';
        } while (cursor % 4 != 0);
        return;
    }
    vga[cursor++] = (current_color << 8) | c;
}
void vga_kputchar(char c) {
    if(c == '\z'){ // "\n" for new lines with ">"
        vga_newline();
        vga_print(">");
        prompt_start = cursor;
        return; 
    }
    if(c == '\n'){ // this is to shell  commands
        cursor = (cursor / VGA_WIDTH + 1) * VGA_WIDTH;
        if (cursor >= VGA_WIDTH * VGA_HEIGHT) {
            cursor = 0;
        }
        
        return; 
    }
    vga[cursor++] = (current_color << 8) | c;
    if (cursor >= VGA_WIDTH * VGA_HEIGHT) {
        cursor = 0;
    }
}
void vga_print(const char* s) {
    for (int i = 0; s[i]; i++) {
        vga_kputchar(s[i]);
    }
}
 void vga_scroll(void) {
    
    for (int i = 0; i < VGA_WIDTH * (VGA_HEIGHT - 1); i++)
        vga[i] = vga[i + VGA_WIDTH];

   
    for (int i = VGA_WIDTH * (VGA_HEIGHT - 1); i < VGA_WIDTH * VGA_HEIGHT; i++)
        vga[i] = (current_color << 8) | ' ';

    cursor = VGA_WIDTH * (VGA_HEIGHT - 1);


    prompt_start = (prompt_start >= VGA_WIDTH) ? prompt_start - VGA_WIDTH : 0;
}
 void vga_newline(void) {
    cursor = (cursor / VGA_WIDTH + 1) * VGA_WIDTH;
    if (cursor >= VGA_WIDTH * VGA_HEIGHT)
        vga_scroll();
}

 void vga_put_cell(char c) {
    vga[cursor++] = (current_color << 8) | (uint8_t)c;
    if (cursor >= VGA_WIDTH * VGA_HEIGHT)
        vga_scroll();
}