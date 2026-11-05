#include <stdio.h>

/*
* PRINTF TYPES
* %d type = int
* %f type = double 
* %c types = char
* %s type = String
* %x Unsignet interger in hexadecimal (optional)
* %p type = Pointer    
*/

char* itoap(unsigned long num, int base) {
    static const char digits[] = "0123456789abcdef";
    static char buffer[17];
    int i = 15;
    buffer[16] = '\0';

    if (num == 0) {
        buffer[i] = '0';
        i--;
    }

    while (num > 0) {
        buffer[i] = digits[num % base];
        num = num / base;
        i--;
    }

    return &buffer[i + 1];
}

int kprintf(const char* restrict format, ...)
{
    va_list args;
    va_start(args,format);
    while(*format != '\0'){
        if(*format != '%')
        {
            kputchar(*format);
        }
        if(*format == '%')
        {
                if(format[1] == 'd')
                {
                    int num = va_arg(args,int);
                    char *s = itoap(num,10); 
                    // s e o ponteiro que o itoa (que está em stdlib.h ) devolve de int para este ponteiro 
                    while(*s != '\0'){
                        kputchar(*s);
                        s++;
                    }
                    format++;
                }
                else if(format[1] == 'c' )
                {
                    int cha = (char)va_arg(args,int);
                    kputchar(cha);
                }
                else if(format[1] == 's'){
                    char *str = va_arg(args,char*);
                    print(str);
                }
                else if(format[1] == 'f'){
                    
                    //TODO
                    
                }
            
        }
        format++;
    }
}
