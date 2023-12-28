#include "gdt.h"
#include "printf.h"
#include "debug.h"
#include "errno.h"

gdt_entry_t gdt_entries[GDT_MAX_ENTRIES];
static gdt_ptr_t ptr;

void gdt_init()
{
    ptr.offset = ((uint32_t)&gdt_entries);
    ptr.size = (sizeof(gdt_entry_t)*GDT_MAX_ENTRIES) - 1;

    // Null descriptor
    gdt_set_gate(0, 0x00000000, 0x00000, 0x00, 0x00);

    // Kernel mode code segment [A(0x9A):{a RW dc E T R0 P}, F(0x0C):{r lm SZ GN}]
    gdt_set_gate(1, 0x00000000, 0xFFFFFFFF, 0x9A, 0x0C);

    // Kernel mode data segment [A(0x92):{a RW dc e T R0 P}, F(0x0C):{r lm SZ GN}]
    gdt_set_gate(2, 0x00000000, 0xFFFFFFFF, 0x92, 0x0C);

    // User mode code segment [A(0xFA):{a RW dc E T R3 P}, F(0x0C):{r lm SZ GN}]
    gdt_set_gate(3, 0x00000000, 0xFFFFFFFF, 0xFA, 0x0C);

    // User mode data segment [A(0xF2):{a RW dc e T R3 P}, F(0x0C):{r lm SZ GN}]
    gdt_set_gate(4, 0x00000000, 0xFFFFFFFF, 0xF2, 0x0C);

    flush_gdt((uint32_t)&ptr);

    printf("GDT successfully configured...\n");
}

void gdt_set_gate(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
    KERNEL_ASSERT(index < GDT_MAX_ENTRIES);

    gdt_entries[index].base_low = (base & 0xFFFF);
    gdt_entries[index].base_middle = (base >> 16) & 0xFF;
    gdt_entries[index].base_high = (base >> 24) & 0xFF;

    gdt_entries[index].limit_low = (limit & 0xFFFF);
    gdt_entries[index].limit_high = (limit >> 16) & 0x0F;

    gdt_entries[index].flags |= flags & 0x0F;

    gdt_entries[index].access = access;

    ERRNO_SET(ENOERR);
}
