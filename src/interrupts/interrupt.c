#include "isr.h"
#include "printf.h"
#include "pic.h"
#include "errno.h"

isr_handler_t isr_handlers[256];

void isr_register_handler(uint8_t irq, isr_handler_t handler)
{
	isr_handlers[irq] = handler;
	printf("Registered isr handler to IRQ #%02xh\n", irq);
}

static int interrupt_lock = 0;


void disable_interrupts()
{
	asm("cli");
	interrupt_lock++;
}

int enable_interrupt()
{
	if(interrupt_lock == 0)
	{
		ERRNO_SET(ENOERR);
		asm("sti");
		return 0;
	}

	interrupt_lock--;
	ERRNO_SET(ENOACTION);
	return interrupt_lock;
}

#pragma GCC push_options
#pragma GCC optimize ("O0")

void isr_handler(registers_t regs)
{
    if(isr_handlers[regs.ino] != 0)
    {
        isr_handler_t handler = isr_handlers[regs.ino];
        handler(&regs);
    }
    else
    {
        printf("No interrupt handler for interrupt %d\n", regs.ino);
    }
    pic_eoi(regs.ino);
}

#pragma GCC pop_options