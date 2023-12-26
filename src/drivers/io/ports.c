#include "ports.h"

void outb(uint16_t port, uint8_t data)
{
    __KERNEL_ASM("outb %0, %1" :: "a"(data), "Nd"(port));
}

void outw(uint16_t port, uint16_t data)
{
    __KERNEL_ASM("outw %0, %1" :: "a"(data), "Nd"(port));
}

void outl(uint16_t port, uint32_t data)
{
    __KERNEL_ASM("outl %0, %1" :: "a"(data), "Nd"(port));
}

uint8_t inb(uint16_t port)
{
    uint8_t ret = 0;
    __KERNEL_ASM("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

uint16_t inw(uint16_t port)
{
    uint16_t ret = 0;
    __KERNEL_ASM("inw %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
} 

uint32_t inl(uint16_t port)
{
    uint32_t ret = 0;
    __KERNEL_ASM("inl %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}