section .initial_stack, nobits
align 4
__KERNEL_STACK_BOTTOM:
  resb 104856
__KERNEL_STACK_TOP:


section .text
global __KERNEL_BOOTSTRAP
extern kernelMain
__KERNEL_BOOTSTRAP:
  mov esp,__KERNEL_STACK_TOP
  push eax
  push ebx
  call kernelMain

__KERNEL_EXECUTION_STOP:
  cli
  hlt
  jmp __KERNEL_EXECUTION_STOP
