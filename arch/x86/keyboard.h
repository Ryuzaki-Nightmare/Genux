#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gop.h>
#include <pic.h>
void keyboard( uint8_t scancode);
extern void irq1asm(void);
#define UNKNOWN 0x00
#define ESC 0x01
#define CTRL 0x1D
#define LSHFT 0x2A
#define RSHFT 0x36
#define ALT 0x38
#define F1 0x3B
#define F2 0x3C
#define F3 0x3D
#define F4 0x3E
#define F5 0x3F
#define F6 0x40
#define F7 0x41
#define F8 0x42
#define F9 0x43
#define F10 0x44
#define F11 0x57
#define F12 0x58
#define SCRLCK 0x46


#define HOME 0x47
#define UP 0x48
#define LEFT 0x4B
#define RIGHT 0x4D
#define DOWN 0x50
#define PGUP 0x49
#define PGDOWN 0x51
#define END 0x4F
#define INS 0x52
#define DEL 0x53

#define CAPS 0x3A
#define NONE 0x00
#define ALTGR 0x38
#define NUMLCK 0x45

#define ENTER 0x1C  /*\n*/
#define BACKSPACE 0x0E /*\b*/
#define SPACE 0x39
#define TAB 0x0D /*\t*/

extern uint8_t teclas[255];
extern uint8_t teclas_count;
#endif