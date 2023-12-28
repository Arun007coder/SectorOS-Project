#if !defined(__PIC_H__)
#define __PIC_H__

#include "system.h"

#define PIC_MASTER_COMMAND 0x20
#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_COMMAND 0xA0
#define PIC_SLAVE_DATA 0xA1

void pic_init();
void pic_eoi(uint8_t irq);


#endif // __PIC_H__
