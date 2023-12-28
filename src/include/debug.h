#if !defined(__DEBUG_H__)
#define __DEBUG_H__

#include "system.h"

void kernel_panic(char* message);
void kernel_assert(const char* file, int line, const char* statement, bool state);

#define KERNEL_ASSERT(a) kernel_assert(__FILE__, __LINE__, #a, a)

#define BOCHS_MAGIC_BREAKPOINT __KERNEL_ASM("xchgw %bx, %bx");

#endif // __DEBUG_H__
