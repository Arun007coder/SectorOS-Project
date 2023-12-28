#if !defined(__GDT_H__)
#define __GDT_H__

#include "system.h"

typedef struct gdt_pointer_struct
{
    uint16_t size;
    uint32_t offset;
}__attribute__((packed))gdt_ptr_t;

typedef union gdt_access_union
{
    uint8_t accessed : 1;
    uint8_t RW_bit : 1;
    uint8_t DC_bit : 1;
    uint8_t Executable : 1;
    uint8_t Type : 1;
    uint8_t DPL : 2;
    uint8_t Present : 1;

    uint8_t access;
}gdt_access_t;

typedef union gdt_flags_union
{
    uint8_t reserved : 1;
    uint8_t long_mode : 1;
    uint8_t size : 1;
    uint8_t granularity : 1;

    uint8_t flags;
}gdt_flags_t;

typedef struct gdt_table_entry_struct
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t limit_high : 4;
    uint8_t flags : 4;
    uint8_t base_high;
}__attribute__((packed))gdt_entry_t;

#define GDT_MAX_ENTRIES 6

extern gdt_entry_t gdt_entries[GDT_MAX_ENTRIES];

void gdt_init();
void gdt_set_gate(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);
extern void flush_gdt(uint32_t gdt_ptr);

#endif // __GDT_H__