#include <gop.h>
uint32_t X = 0;
uint32_t Y  = -5;
/*GOP VARIABLES*/
uint32_t Version;
uint32_t Width;
uint32_t Height;
EFI_GRAPHICS_PIXEL PixelFormat;
EFI_PIXEL_MASK PixelInformation;
Uint64_t FrameBufferBase;
UINTN FrameBufferSize;
uint32_t PixelsPerScanLine; 
uint32_t* FrameBuffer;
uint32_t color;

void gop(EFI_GOP_INFORMATION *gop){
    Version = gop->Version;
    Width = gop->WidthResolution;
    Height = gop->HeightResolution;
    PixelFormat = gop->PixelFormat;
    PixelsPerScanLine = gop->PixelsPerScanLine;
    PixelInformation = gop->PixelInformation;
    FrameBufferBase = gop->FrameBufferBase;
    FrameBufferSize = gop->FrameBufferSize;
}
/*
 *GOP OFFSET
 *Offset in Bytes = (Y * PixelsPerScanLine + X) * 4
 * */
void init_console(EFI_GOP_INFORMATION *Gop){
    uint32_t *fb = (uint32_t *)Gop->FrameBufferBase;
    uint32_t totalPixels = Gop->PixelsPerScanLine * Gop->HeightResolution;

    FrameBuffer = (uint32_t *) FrameBufferBase;
    set_color(GREEN);
    kprintf("$");
    set_color(WHITE);

}
void set_color(uint64_t colour){
    color = colour;
}
void gop_putchar(char c) {
    if (c == 8) {  // backspace
        backspace();
    }

    

    if (c == 13) {  // enter
        newline();
        shell(); // call func "shell" in kernel/terminal/shell.c
        set_color(GREEN);
        newline();
        kprintf("$");
        memset(teclas,0,sizeof(teclas)); /*Zera array do teclado para comecar dnv a contagem*/
        teclas_count = 0;
        
        return;

    }
    if (c == 9) {  // tab   go to next  multiple of  4
        X += 32;
        return;
    }else{
        kputchar(c);
    }
}
void backspace(void){
    if(X >= 16){
        X -= 8;
    }
    for(int i = 0; i < 16;i++){
        for(int j = 0 ;j < 8; j ++){
            set_color(BLACK);
            plot_pixel(X+ j, Y + i);
        }
    }
    if(teclas_count > 0 )
        teclas[--teclas_count] = 0;
    X -= 8;
}
void kputchar(char c) {
    uint32_t byte_line;
    uint32_t pixel_x;
    uint32_t pixel_y;
    if(c == '\n'){
        newline();
    }
    for(int i = 0 ;i < 16;i++){
        uint8_t byte_line = font[(unsigned char)c][i];
        //byte_line = byte_line | (byte_line >> 1);
        for(int bit = 7; bit >= 0 ; bit--){
            if(((byte_line >> bit)& 1 ) == 1) {
                pixel_x = X + (7-bit);
                pixel_y = Y + i;
                plot_pixel(pixel_x,pixel_y);
                pixel_x++;
            }
        }
    }
    X += 8;
}
void plot_pixel(uint32_t x,uint32_t y){
    uint32_t offset = (y* PixelsPerScanLine ) + x;
    FrameBuffer[offset] = color;
}
void print(const char* s) {
    for (int i = 0; s[i]; i++) {
        kputchar(s[i]);
    }
}
 void scroll(void) {
}
 void newline(void) {
        X = -8;
        Y += 8;
        X = 0;
 
}
 void put_cell(char c) {
 
}
