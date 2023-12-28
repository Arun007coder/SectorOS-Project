#if !defined(__REGISTERS_H__)
#define __REGISTERS_H__

#include "system.h"

typedef struct registers_struct
{
    uint32_t ds;
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t ino;
    uint32_t ecode;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t useresp;
    uint32_t ss;
}registers_t;

#endif // __REGISTERS_H__
