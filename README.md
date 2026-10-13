# Genux
## Tapix is an operating system focused on the global open-source market, inspired by Linux. Built entirely from scratch without Vibecode.
## folder structures
```text
Genux/
├── .gitignore
├── LICENSE
├── Makefile
├── README.MD
├── linker.ld
└──arch
|    └──x86
|        └──x86 basic tools
└── kernel/
    ├── kernel.c
    ├── kernel.h
    ├── kernel_entry.asm
    └── libc/
    |    └── Minimal libc
    └── terminal/
            └── terminal archives for shell

```
## Technologies
```text
    Assembly X86_64
    C
    Grub
    linker.ld
    make
```
### How to use
```text
    sudo apt update
    sudo apt install -y make nasm qemu-system-x86 gcc binutils
    git clone https://github.com/Ryuzaki-Nightmare/Genux.git 
    cd Genux
    make clean && make run
```
##  Genux symbol
```
    ______                     
  / ____/__  ____  __  ___  __
 / / __/ _ \/ __ \/ / / / |/_/
/ /_/ /  __/ / / / /_/ />  <  
\____/\___/_/ /_/\__,_/_/|_|  
                              
      
```
