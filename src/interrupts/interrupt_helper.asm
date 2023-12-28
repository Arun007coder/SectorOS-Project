%macro ISR 2
    [GLOBAL isr%1]
    isr%1:
        cli
        push byte 0
        push byte %2
        jmp isr_common
%endmacro

ISR 00, 32
ISR 01, 33
ISR 02, 34
ISR 03, 35
ISR 04, 36
ISR 05, 37
ISR 06, 38
ISR 07, 39
ISR 08, 40
ISR 09, 41
ISR 10, 42
ISR 11, 43
ISR 12, 44
ISR 13, 45
ISR 14, 46
ISR 15, 47


[extern isr_handler]

isr_common:
    pusha
    mov ax, ds
    push eax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp
    call isr_handler
    pop esp

    pop ebx
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa

    add esp, 8
    sti
    iret