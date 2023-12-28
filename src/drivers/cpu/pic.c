#include "pic.h"
#include "printf.h"
#include "ports.h"

void pic_eoi(uint8_t irq)
{
	if(irq >= 0x28)
		outb(PIC_SLAVE_COMMAND, 0x20);

	outb(PIC_MASTER_COMMAND, 0x20);
}

void pic_init()
{
	outb(PIC_MASTER_COMMAND, 0x11);
    outb(PIC_SLAVE_COMMAND, 0x11);
    outb(PIC_MASTER_DATA, 0x20);
    outb(PIC_SLAVE_DATA, 0x28);
    outb(PIC_MASTER_DATA, 0x04);
    outb(PIC_SLAVE_DATA, 0x02);
    outb(PIC_MASTER_DATA, 0x01);
    outb(PIC_SLAVE_DATA, 0x01);
    outb(PIC_MASTER_DATA, 0x00);
    outb(PIC_SLAVE_DATA, 0x00);
}