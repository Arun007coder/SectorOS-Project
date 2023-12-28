#include "debug.h"
#include "printf.h"
#include "textmode.h"
#include "errno.h"

//TODO: Add support for register printing
void kernel_panic(char* message)
{
    textmode_chattr(15, 4);
    textmode_clear();

    textmode_puts("\"KERNEL HAS POPPED\"\n\nAn unrecoverable error has been occurred in the kernel. The kernel will be halting...\n\nMessage: ");
    textmode_puts(message);
    textmode_puts("\n");
    int save = get_errno();
    const char* errstr = errno_to_str(save);
    const char* errfile = get_last_errno_file();
    const char* errfunc = get_last_errno_function();
    printf("Last occurred error [errno]: %s[%d] \n\t-at %s:%s()\n", errstr, save, errfile, errfunc);

    __KERNEL_ASM("cli; hlt");
}

void kernel_assert(const char* file, int line, const char* statement, bool state)
{
    if(state == true)
        return;

    textmode_chattr(15, 4);
    textmode_clear();

    int save = get_errno();
    const char * msg = errno_to_str(save);

    const char* errfile = get_last_errno_file();
    const char* errfunc = get_last_errno_function();

    printf("\"TACTICAL NUKE INCOMING...\"\n\nAn assertion has failed in the kernel. Kernel cannot verify its stability. Therefore, kernel will be halting...\n\nKernel: %s\nFile: %s:%d\nStatement: %s\nLast occurred error [errno]: %s[%d] \n\t-at %s:%s()\n", __KERNEL_NAME" v"__KERNEL_VERSION, file, line, statement, msg, save, errfile, errfunc);

    __KERNEL_ASM("cli; hlt");
}