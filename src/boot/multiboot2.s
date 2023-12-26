// Multiboot 2 specification from https://gnu.org/software/grub/manual/multiboot2/multiboot.html

.set MULTIBOOT2_MAGIC, 0xE85250D6
.set MULTIBOOT2_ARCH, 0

.section .multiboot2
__MULTIBOOT2_HEADER_START:
  .long MULTIBOOT2_MAGIC
  .long MULTIBOOT2_ARCH
  .long __MULTIBOOT2_HEADER_END - __MULTIBOOT2_HEADER_START
  .long -(MULTIBOOT2_MAGIC+MULTIBOOT2_ARCH+(__MULTIBOOT2_HEADER_END-__MULTIBOOT2_HEADER_START))
  .align 8

__MULTIBOOT2_TAG_ALIGN_MODULE:
  .short 0x06
  .short 0x00
  .long 8
  .align 8

__MULTIBOOT2_TAG_END:
  .short 0
  .short 0
  .long 8
  .align 8

__MULTIBOOT2_HEADER_END:

// MULTIBOOT2 HEADER END


