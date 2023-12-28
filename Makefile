SYSROOT=~/sysroot/
ROOTDIR=$(shell pwd)
SRCDIR=$(ROOTDIR)/src
INCDIR=$(SRCDIR)/include
GRUBDIR=~/sysroot/grub/

CC=$(SYSROOT)/bin/i686-elf-gcc
CFLAGS=
KCFLAGS= -I$(INCDIR) -fno-builtin -fno-leading-underscore -ffreestanding -Wall -O2 -nostdlib $(CFLAGS)

LD=$(SYSROOT)/bin/i686-elf-ld
LINKERSCRIPT=$(SRCDIR)/boot/link.ld
LIBGCC_PATH=$(shell $(CC) -print-libgcc-file-name)
LDFLAGS= -T$(LINKERSCRIPT)

AS=$(SYSROOT)/bin/i686-elf-as
ASFLAGS=

NASM=nasm 
NASMFLAGS=-f elf32 -g -F dwarf -O2 -w+zeroing
OBJCOPY=$(SYSROOT)/bin/i686-elf-objcopy
OBJDUMP=$(SYSROOT)/bin/i686-elf-objdump

QEMU=qemu-system-i386
QEMUFLAGS=-cdrom $(ISOFILE) -m 512M -boot d -enable-kvm
QEMUDFLAGS=-s -S -daemonize -no-reboot -d int

KERNEL_NAME=arthur
OS_NAME=SectorOS

KERNEL_IMAGE=$(KERNEL_NAME).elf 
ISOFILE=$(OS_NAME).iso 

OBJECTS= $(SRCDIR)/boot/multiboot2.o \
				$(SRCDIR)/boot/boot.o \
				$(SRCDIR)/kernel/kernel.o \
				$(SRCDIR)/common/debug.o \
				$(SRCDIR)/common/printf.o \
				$(SRCDIR)/common/string.o \
				$(SRCDIR)/common/errno.o \
				$(SRCDIR)/descriptors/gdt.o \
				$(SRCDIR)/descriptors/gdt_helper.o \
				$(SRCDIR)/descriptors/idt.o \
				$(SRCDIR)/descriptors/idt_helper.o \
				$(SRCDIR)/drivers/cpu/pic.o \
				$(SRCDIR)/interrupts/exception.o \
				$(SRCDIR)/interrupts/exception_helper.o \
				$(SRCDIR)/interrupts/interrupt.o \
				$(SRCDIR)/interrupts/interrupt_helper.o \
				$(SRCDIR)/drivers/io/ports.o \
				$(SRCDIR)/drivers/video/textmode.o 

kernel : $(KERNEL_IMAGE)
iso : $(ISOFILE)

$(KERNEL_IMAGE) : $(OBJECTS)
	@echo "[LD] $@"
	@$(LD) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBGCC_PATH)

$(ISOFILE) : $(KERNEL_IMAGE)
	@echo '[GRUB] $@'
	@mkdir -p $(OS_NAME)/boot/grub
	@cp $(ROOTDIR)/docs/grub.cfg $(OS_NAME)/boot/grub/grub.cfg
	@cp $(KERNEL_IMAGE) $(OS_NAME)/boot/
	@$(GRUBDIR)bin/grub-mkrescue -o $(ISOFILE) $(OS_NAME) --product-name=$(OS_NAME)
	@rm -rf $(OS_NAME)

%.o : %.c 
	@echo '[CC] $@'
	@$(CC) $(KCFLAGS) -c -o $@ $<

%.o : %.s
	@echo '[AS] $@'
	@$(AS) $(ASFLAGS) -o $@ $<

%.o : %.asm
	@echo '[NASM] $@'
	@$(NASM) $(NASMFLAGS) -o $@ $<

run : $(ISOFILE)
	@echo '[QEMU] Running OS...'
	@$(QEMU) $(QEMUFLAGS) -serial stdio

rund : $(ISOFILE)
	@echo '[QEMU] Debugging OS...'
	@$(QEMU) $(QEMUFLAGS) $(QEMUDFLAGS)

PHONY: clean
clean:
	@echo 'Cleaning the source directory...'
	@rm -f $(OBJECTS) $(KERNEL_IMAGE) $(ISOFILE)
