ENTRY(kernel_main)
SECTIONS{
    . = 0x100000; 
    .text :
    {
        KEEP(*(.text.kernel_main))
        *(.text)
    }
    .rodata :
    {
        *(.rodata)
    }
    .data :
    {
        *(.data)
    }
    .bss :
    {
        *(.bss)
    }
        /DISCARD/ :
    {
        *(.comment)
        *(.eh_frame)
        *(.note.*)
    }
} 
