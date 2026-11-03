#ifndef GOP_H
#define GOP_H

#include <stdint.h>
#include <keyboard.h>
#include <string.h>
#include <shell.h>
#include <boot.h>
#include <font.h>
enum Color_Pixel_BGR {
    RED     = 0x00FF0000U,
    GREEN   = 0x0000FF00U,
    BLUE    = 0x000000FFU,
    WHITE   = 0x00FFFFFFU,
    BLACK   = 0x00000000U,
    YELLOW  = 0x00FFFF00U,
    MAGENTA = 0x00FF00FFU,
    CYAN    = 0x0000FFFFU
};

void set_color(uint64_t colour);
void gop_putchar(char c); 
void print(const char* s);
void backspace(void);
void newline(void);
void kputchar(char c);
void scrool(void);
void newline(void);
void put_cell(char c);
void gop(EFI_GOP_INFORMATION *gop);
void plot_pixel(uint32_t x,uint32_t y);
void init_console(EFI_GOP_INFORMATION *Gop);
#endif
