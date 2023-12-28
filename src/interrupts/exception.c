#include "isr.h"
#include "debug.h"
#include "textmode.h"
#include "printf.h"

static const char* exception_messages[] = {
	"Divide by zero",
	"Debug",
	"Non maskable interrupt",
	"Breakpoint",
	"Overflow",
	"Bound range exceeded",
	"Invalid opcode",
	"Device not available",
	"Double fault",
	"Coprocessor segment overrun",
	"Invalid TSS",
	"Segment not present",
	"Skack-Segment fault",
	"General protection fault",
	"Page fault",
	"Reserved 01",
	"x87 Floating point exception",
	"Alignment check",
	"Machine check",
	"SIMD Floating point exception",
	"Virtualization exception",
	"Control protection exception",
	"Reserved 02",
	"Reserved 03",
	"Reserved 04",
	"Reserved 05",
	"Reserved 06",
	"Reserved 07",
	"Hypervisor injection exception",
	"VMM communication exception",
	"Security exception",
	"Reserved 08"
};

#pragma GCC push_options
#pragma GCC optimize ("O0")

void exception_handler(registers_t regs)
{
	if(regs.ino < IRQ_BASE)
	{
		textmode_chattr(15, 4);
		textmode_clear();

		printf("===================================[WARNING!]===================================\n\n An exception has occurred in the kernel and it is being passed to the handler.\n\nKernel: %s v%s\nException number: #%02xh\nDescription: %s\n\n=================================[HANDLER MSG]=================================\n\n", __KERNEL_NAME, __KERNEL_VERSION, regs.ino, exception_messages[regs.ino]);
	}

	if(isr_handlers[regs.ino] != 0)
	{
		isr_handler_t handler= isr_handlers[regs.ino];
		handler(&regs);
	}
	else
	{
		if(regs.ino < IRQ_BASE)
		{
			printf("Handler is not registered in the kernel. The kernel will be halting...\n\n");
			printf("Registers:\n\tEAX: %08x\tEBX: %08x\n\tECX: %08x\tEDX: %08x\n\tESP: %08x\tEBP: %08x\n", regs.eax, regs.ebx, regs.ecx, regs.edx, regs.esp, regs.ebp);

			__KERNEL_ASM("cli; hlt");
		}
		else if(regs.ino == 0x80)
		{
			printf("SYSCALL Handler is not configured yet...\n");
		}
	}
}

#pragma GCC pop_options