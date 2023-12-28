#include "idt.h"
#include "string.h"
#include "isr.h"
#include "printf.h"

static idtr_t ptr;
__attribute__((aligned(0x10)))
static idt_entry_t entries[256];

void idt_register_isr(uint8_t index, uint32_t isr, uint16_t selector, uint8_t attributes)
{
    entries[index].isr_low = isr & 0xFFFF;
    entries[index].isr_high = (isr >> 16) & 0xFFFF;

    entries[index].selector = selector;

    entries[index].reserved = 0;

    entries[index].attributes = attributes;
}

extern void flush_idt(uint32_t ptr);

#define SELECTOR 0x08

void idt_init()
{
    ptr.base = ((uint32_t)&entries);
    ptr.limit = (sizeof(idt_entry_t) * 256) - 1;

	memset(entries, 0, sizeof(idt_entry_t)*256);

	idt_register_isr(0, (uint32_t)exception00, SELECTOR, 0x8E);
    idt_register_isr(1, (uint32_t)exception01, SELECTOR, 0x8E);
    idt_register_isr(2, (uint32_t)exception02, SELECTOR, 0x8E);
    idt_register_isr(3, (uint32_t)exception03, SELECTOR, 0x8E);
    idt_register_isr(4, (uint32_t)exception04, SELECTOR, 0x8E);
    idt_register_isr(5, (uint32_t)exception05, SELECTOR, 0x8E);
    idt_register_isr(6, (uint32_t)exception06, SELECTOR, 0x8E);
    idt_register_isr(7, (uint32_t)exception07, SELECTOR, 0x8E);
    idt_register_isr(8, (uint32_t)exception08, SELECTOR, 0x8E);
    idt_register_isr(9, (uint32_t)exception09, SELECTOR, 0x8E);
    idt_register_isr(10, (uint32_t)exception10, SELECTOR, 0x8E);
    idt_register_isr(11, (uint32_t)exception11, SELECTOR, 0x8E);
    idt_register_isr(12, (uint32_t)exception12, SELECTOR, 0x8E);
    idt_register_isr(13, (uint32_t)exception13, SELECTOR, 0x8E);
    idt_register_isr(14, (uint32_t)exception14, SELECTOR, 0x8E);
    idt_register_isr(15, (uint32_t)exception15, SELECTOR, 0x8E);
    idt_register_isr(16, (uint32_t)exception16, SELECTOR, 0x8E);
    idt_register_isr(17, (uint32_t)exception17, SELECTOR, 0x8E);
    idt_register_isr(18, (uint32_t)exception18, SELECTOR, 0x8E);
    idt_register_isr(19, (uint32_t)exception19, SELECTOR, 0x8E);
    idt_register_isr(20, (uint32_t)exception20, SELECTOR, 0x8E);
    idt_register_isr(21, (uint32_t)exception21, SELECTOR, 0x8E);
    idt_register_isr(22, (uint32_t)exception22, SELECTOR, 0x8E);
    idt_register_isr(23, (uint32_t)exception23, SELECTOR, 0x8E);
    idt_register_isr(24, (uint32_t)exception24, SELECTOR, 0x8E);
    idt_register_isr(25, (uint32_t)exception25, SELECTOR, 0x8E);
    idt_register_isr(26, (uint32_t)exception26, SELECTOR, 0x8E);
    idt_register_isr(27, (uint32_t)exception27, SELECTOR, 0x8E);
    idt_register_isr(28, (uint32_t)exception28, SELECTOR, 0x8E);
    idt_register_isr(29, (uint32_t)exception29, SELECTOR, 0x8E);
    idt_register_isr(30, (uint32_t)exception30, SELECTOR, 0x8E);
    idt_register_isr(31, (uint32_t)exception31, SELECTOR, 0x8E);

    idt_register_isr(32, (uint32_t)isr00, SELECTOR, 0x8E);
    idt_register_isr(33, (uint32_t)isr01, SELECTOR, 0x8E);
    idt_register_isr(34, (uint32_t)isr02, SELECTOR, 0x8E);
    idt_register_isr(35, (uint32_t)isr03, SELECTOR, 0x8E);
    idt_register_isr(36, (uint32_t)isr04, SELECTOR, 0x8E);
    idt_register_isr(37, (uint32_t)isr05, SELECTOR, 0x8E);
    idt_register_isr(38, (uint32_t)isr06, SELECTOR, 0x8E);
    idt_register_isr(39, (uint32_t)isr07, SELECTOR, 0x8E);
    idt_register_isr(40, (uint32_t)isr08, SELECTOR, 0x8E);
    idt_register_isr(41, (uint32_t)isr09, SELECTOR, 0x8E);
    idt_register_isr(42, (uint32_t)isr10, SELECTOR, 0x8E);
    idt_register_isr(43, (uint32_t)isr11, SELECTOR, 0x8E);
    idt_register_isr(44, (uint32_t)isr12, SELECTOR, 0x8E);
    idt_register_isr(45, (uint32_t)isr13, SELECTOR, 0x8E);
    idt_register_isr(46, (uint32_t)isr14, SELECTOR, 0x8E);
    idt_register_isr(47, (uint32_t)isr15, SELECTOR, 0x8E);

    idt_register_isr(128, (uint32_t)exception128, SELECTOR, (0x8E | 0x60));

	flush_idt((uint32_t)&ptr);

	printf("IDT configured successfully...\n");
}