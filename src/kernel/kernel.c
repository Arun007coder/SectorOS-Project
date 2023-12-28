#include "system.h"
#include "textmode.h"
#include "debug.h"
#include "multiboot2.h"
#include "gdt.h"
#include "idt.h"
#include "errno.h"
#include "pic.h"
#include "isr.h"

void kernelMain(struct multiboot_tag *ptr, uint32_t magic)
{
	textmode_init();
	KERNEL_ASSERT(magic == MULTIBOOT2_BOOTLOADER_MAGIC);
	textmode_puts(__KERNEL_NAME " "__KERNEL_VERSION
								" is booting...\n");

	ERRNO_SET(EINVAL);

	gdt_init();
	idt_init();

	pic_init();


	__KERNEL_ASM("sti");

	while(1);
}
