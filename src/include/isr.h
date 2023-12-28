#if !defined(__ISR_H__)
#define __ISR_H__

#include "system.h"
#include "registers.h"

// External interrupt handler functions
extern void exception00();      // 0x00 : Divide by zero [Fault]
extern void exception01();      // 0x01 : Debug [Fault/Trap]
extern void exception02();      // 0x02 : Non maskable interrupt [Interrupt]
extern void exception03();      // 0x03 : Breakpoint [Trap]
extern void exception04();      // 0x04 : Overflow [Trap]
extern void exception05();      // 0x05 : Bound range exceeded [Fault]
extern void exception06();      // 0x06 : Invalid opcode [Fault]
extern void exception07();      // 0x07 : Device not available [Fault]
extern void exception08();      // 0x08 : Double fault [Abort]
extern void exception09();      // 0x09 : Coprocessor segment overrun [Fault]
extern void exception10();      // 0x0A : Invalid TSS [Fault]
extern void exception11();      // 0x0B : Segment not present [Fault]
extern void exception12();      // 0X0C : Stack-Segment fault [Fault]
extern void exception13();      // 0x0D : General protection fault [Fault]
extern void exception14();      // 0x0E : Page fault [Fault]
extern void exception15();      // 0x0F : Reserved
extern void exception16();      // 0x10 : x87 Floating point exception [Fault]
extern void exception17();      // 0x11 : Alignment check [Fault]
extern void exception18();      // 0x12 : Machine check [Abort]
extern void exception19();      // 0x13 : SIMD Floating point exception [Fault]
extern void exception20();      // 0x14 : Virtualization exception [Fault]
extern void exception21();      // 0x15 : Control protextion exception [Fault]
extern void exception22();      // 0x16 : Spare
extern void exception23();      // 0x17 : Spare
extern void exception24();      // 0x18 : Spare
extern void exception25();      // 0x19 : Spare
extern void exception26();      // 0x1A : Spare
extern void exception27();      // 0x1B : Spare
extern void exception28();      // 0x1C : Hypervisor injection exception
extern void exception29();      // 0x1D : VMM communication exception
extern void exception30();      // 0x1E : Security exception
extern void exception31();      // 0x1F : Spare
extern void exception128();     // 0x80 : System Call

// Interrupt requests
extern void isr00();			// 0x20: IRQ 00: Programmable interrupt timer
extern void isr01();			// 0x21: IRQ 01: Keyboard
extern void isr02();     		// 0x22: IRQ 2: Cascade (2)
extern void isr03();     		// 0x23: IRQ 3: COM2 (If Enabled)
extern void isr04();     		// 0x24: IRQ 4: COM1 (If Enabled)
extern void isr05();     		// 0x25: IRQ 5: LPT2 (If Enabled)
extern void isr06();     		// 0x26: IRQ 6: Floppy Disk
extern void isr07();     		// 0x27: IRQ 7: LPT1/Spurious Interrupt
extern void isr08();     		// 0x28: IRQ 8: CMOS Real-Time Clock
extern void isr09();     		// 0x29: IRQ 9: Free for peripherals/legacy SCSI
extern void isr10();    		// 0x2A: IRQ 10: Free for peripherals/SCSI/NIC
extern void isr11();    		// 0x2B: IRQ 11: Free for peripherals/SCSI/NIC
extern void isr12();    		// 0x2C: IRQ 12: PS/2 Mouse
extern void isr13();    		// 0x2D: IRQ 13: FPU/Coprocessor/Inter-processor (Deprecated)
extern void isr14();    		// 0x2E: IRQ 14: Primary ATA Hard Disk
extern void isr15();    		// 0x2F: IRQ 15: Secondary ATA Hard Disk

typedef void (*isr_handler_t)(registers_t* regs);

#define IRQ_BASE 0x20
#define IRQ(n) (IRQ_BASE + n)

extern isr_handler_t isr_handlers[256];

void isr_register_handler(uint8_t irq, isr_handler_t handler);

void disable_interrupts();
int enable_interrupt();

#endif // __ISR_H__
