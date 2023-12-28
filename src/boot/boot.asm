section .initial_stack, nobits
align 4
__KERNEL_STACK_BOTTOM:
	resb 104856
__KERNEL_STACK_TOP:


section .text
global __KERNEL_BOOTSTRAP
extern kernelMain
extern kernel_panic

__KERNEL_ERR_MSG:
	db "Reached end of kernel image", 0x00

__KERNEL_BOOTSTRAP:
	mov esp,__KERNEL_STACK_TOP
	push eax
	push ebx
	call kernelMain

__KERNEL_EXECUTION_STOP:
	push __KERNEL_ERR_MSG
	call kernel_panic
  	cli
  	hlt
