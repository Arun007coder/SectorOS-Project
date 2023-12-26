#include "system.h"
#include "textmode.h"
#include "debug.h"

void kernelMain(uint32_t magic, void* ptr)
{
  textmode_init();
  textmode_puts("Hello, World!\n");
  textmode_puts(__KERNEL_NAME" "__KERNEL_VERSION " is booting...\n");
  KERNEL_ASSERT(1 == 2);
  
  while(1); 
}
