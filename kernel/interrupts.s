extern isr_handler
global isrzero

isr_common:
    pusha
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    call isr_handler
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popa
    add esp, 8
    sti
    iret


%macro isr_noerrorcode 1
    global isr%1
    isr%1:
        cli
        push 0x00
        push %1
        jmp isr_common
%endmacro

%macro isr_errorcode 1
    global isr%1
    isr%1:
        cli
        push %1
        jmp isr_common
%endmacro

isrzero:
    cli
    push 0x00
    push 0x00
    jmp isr_common
