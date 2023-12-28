ENTRY(__KERNEL_BOOTSTRAP)

SECTIONS
{
	. = 2M;

	.multiboot2 BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot2)
	}

	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.text)
	}

	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(.initial_stack)
		*(COMMON)
		*(.bss)
	}

	__KERNEL_IMAGE_END = .;
}