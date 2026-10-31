ASM = nasm
CC = gcc
SRC_DIR = kernel
BUILD_DIR = build
INC_DIR = -Iinclude -Iarch/x86 -Ikernel/terminal
#INC_DIR são diretorios que fazem parte da libc para include, por exemplo, #include <stdlib.h>
log = qemu.log

C_SOURCES := $(shell find $(SRC_DIR) arch  -name "*.c")
C_OBJECTS := $(patsubst %.c, $(BUILD_DIR)/%.o, $(C_SOURCES))

ASM_SOURCES := $(shell find $(SRC_DIR) arch -name "*.asm")
ASM_OBJECTS := $(patsubst %.asm, $(BUILD_DIR)/%.o, $(ASM_SOURCES))


ENTRY_OBJ := $(BUILD_DIR)/kernel/kernel_entry.o
#Arquivo de entrada 
.PHONY:  kernel clean always run

all: Compile

kernel: always $(ASM_OBJECTS) $(C_OBJECTS)
	$(CC) -m64 -ffreestanding -nostdlib -no-pie -T linker.ld \
		$(ENTRY_OBJ) $(sort $(filter-out $(ENTRY_OBJ), $(ASM_OBJECTS) $(C_OBJECTS))) \
		-o $(BUILD_DIR)/kernel.bin

$(BUILD_DIR)/%.o: %.asm always
	mkdir -p $(dir $@)
	$(ASM) $< -f elf64 -o $@

$(BUILD_DIR)/%.o: %.c always
	mkdir -p $(dir $@)
	$(CC) -m64 -ffreestanding -fno-stack-protector $(INC_DIR) -nostdlib -c $< -o $@ 
Compile: 
	mkdir -p build
	$ gcc boot/boot.c                \
	-c                                 \
	-fno-stack-protector               \
	-fpic                              \
	-fshort-wchar                      \
	-mno-red-zone                      \
	-I /usr/include/efi     \
	-I /usr/include/efi/x86_64   		\
	-DEFI_FUNCTION_WRAPPER             \
	-o boot.o
	$ ld boot.o                                    \
	/usr/lib/crt0-efi-x86_64.o          \
	-nostdlib                                \
	-znocombreloc                            \
	-T /usr/lib/elf_x86_64_efi.lds        \
	-shared                                  \
	-Bsymbolic                               \
	-L /usr/lib                        \
	-l:libgnuefi.a                           \
	-l:libefi.a                              \
	-o $(BUILD_DIR)/boot.so
	$ objcopy -j .text                             \
	-j .sdata                            \
	-j .data                             \
	-j .rodata                           \
	-j$ .dynamic                          \
	-j .dynsym                           \
	-j .rel                              \
	-j .rela                             \
	-j .reloc                            \
	--output-target=efi-app-x86_64       \
	$(BUILD_DIR)/boot.so                              \
	$(BUILD_DIR)/boot.efi
	mkdir -p build/esp/EFI/BOOT
	cp $(BUILD_DIR)/boot.efi build/esp/EFI/BOOT/BOOTX64.EFI
	rm -f boot.o

#in run, put -biod /your/path/to/OVM.4m.f
#in -m, put how many ram you want use
#in -smp put how many cores you want use
run: all
	qemu-system-x86_64 \
	-m 16G \
	-smp 8 \
	-bios /usr/share/edk2/x64/OVMF.4m.fd \
	-drive format=raw,file=fat:rw:build/esp \
	-d int,cpu_reset \
	-vga std    \
	-D qemu.log \
	-M smm=off  \
	-no-reboot \
	-no-shutdown \



clean:
	rm -rf $(BUILD_DIR)
	rm -f $(log)
help:
	printf "Comandos: make clean,make run\n"
