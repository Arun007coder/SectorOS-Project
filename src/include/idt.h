#if !defined(__IDT_H__)
#define __IDT_H__

#include "system.h"

typedef struct idt_ptr_struct
{
    uint16_t limit;
    uint32_t base;
}__attribute__((packed))idtr_t;

typedef struct idt_entry_struct
{
    uint16_t isr_low;
    uint16_t selector;
    uint8_t reserved;
    uint8_t attributes;
    uint16_t isr_high;
}__attribute__((packed))idt_entry_t;

void idt_init();
void idt_register_isr(uint8_t index, uint32_t isr, uint16_t selector, uint8_t attribute);

#endif // __IDT_H__
