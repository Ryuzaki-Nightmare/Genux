ASM = nasm
CC = gcc
SRC_DIR = kernel
BUILD_DIR = build
ISO_DIR = iso
INC_DIR = -Iinclude -Iarch/x86 -Ikernel/terminal
#INC_DIR são diretorios que fazem parte da libc para include, por exemplo, #include <stdlib.h>
log = qemu.log

C_SOURCES := $(shell find $(SRC_DIR) arch  -name "*.c")
C_OBJECTS := $(patsubst %.c, $(BUILD_DIR)/%.o, $(C_SOURCES))

ASM_SOURCES := $(shell find $(SRC_DIR) arch -name "*.asm")
ASM_OBJECTS := $(patsubst %.asm, $(BUILD_DIR)/%.o, $(ASM_SOURCES))


ENTRY_OBJ := $(BUILD_DIR)/kernel/kernel_entry.o
#Arquivo de entrada 
.PHONY: all iso kernel clean always run

all: iso

iso: kernel
	cp $(BUILD_DIR)/kernel.bin $(ISO_DIR)/boot/kernel.bin
	grub-mkrescue -o $(BUILD_DIR)/Tapix.iso $(ISO_DIR)

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
	
#Flag -I (da linha 34 includi os cabechalhos)
always:
	mkdir -p $(BUILD_DIR)

run: iso
	qemu-system-x86_64 -cdrom $(BUILD_DIR)/Tapix.iso -d int,cpu_reset -D qemu.log -M smm=off -no-reboot -no-shutdown 



clean:
	rm -rf $(BUILD_DIR)
	rm -f $(ISO_DIR)/boot/kernel.bin
	rm -f $(log)
help:
	printf "Comandos: make clean,make run\n"
