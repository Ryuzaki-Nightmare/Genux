#ifndef STDIO_H
#define STDIO_H
#include <string.h>
#include <vga.h>
#include <stdarg.h>
#include <limits.h>
#include <stdbool.h>

int kprintf(const char* restrict format, ...);
int putchar(int);
int puts(const char*);
#endif