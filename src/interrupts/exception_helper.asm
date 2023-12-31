%macro EXCE_NOECODE 1
    [GLOBAL exception%1]
    exception%1:
        cli
        push byte 0
        push %1
        jmp exception_common
%endmacro

%macro EXCE_ECODE 1
    [GLOBAL exception%1]
    exception%1:
        cli
        push %1
        jmp exception_common
%endmacro

EXCE_NOECODE 00
EXCE_NOECODE 01
EXCE_NOECODE 02
EXCE_NOECODE 03
EXCE_NOECODE 04
EXCE_NOECODE 05
EXCE_NOECODE 06
EXCE_NOECODE 07
EXCE_ECODE 08
EXCE_NOECODE 09

EXCE_ECODE 10
EXCE_ECODE 11
EXCE_ECODE 12
EXCE_ECODE 13
EXCE_ECODE 14
EXCE_NOECODE 15
EXCE_NOECODE 16
EXCE_NOECODE 17
EXCE_NOECODE 18
EXCE_NOECODE 19
EXCE_NOECODE 20
EXCE_NOECODE 21
EXCE_NOECODE 22
EXCE_NOECODE 23
EXCE_NOECODE 24
EXCE_NOECODE 25
EXCE_NOECODE 26
EXCE_NOECODE 27
EXCE_NOECODE 28
EXCE_NOECODE 29
EXCE_NOECODE 30
EXCE_NOECODE 31
EXCE_NOECODE 128

[extern exception_handler]

exception_common:
    pusha
    mov ax, ds
    push eax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call exception_handler

    pop ebx
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa
    add esp, 0x08

    sti
    iret