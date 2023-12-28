#ifndef __SYSTEM_H__

#include "stdint-gcc.h"
#include "stdbool.h"
#include "stddef.h"

extern uint32_t __KERNEL_IMAGE_END;

#define __KERNEL_NAME "Arthur"
#define __KERNEL_VERSION "0.0.2"

#define __KERNEL_ASM(...) asm volatile(__VA_ARGS__)

#endif // !__SYSTEM_H__
