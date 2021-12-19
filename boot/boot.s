section .init
[bits 16]
global init
global CODE_SEGMENT
init:
    ;VGA text mode
    ;mov ah, 0x00
    ;mov al, 0x13
    ;int 0x10
    ;Clear screen
    mov ah, 0x06
    mov al, 0x00
    int 0x10
    ;Read disk
    mov [disk], dl
    mov ah, 0x2
    mov al, 20
    mov ch, 0
    mov dh, 0
    mov cl, 2
    mov dl, [disk]
    mov bx, secondstage
    int 0x13
    cli
    ;A20 line
    mov ax, 0x2401
    int 0x15
    ;Protected mode jump
    lgdt [gdt_pointer]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    mov ax, DATA_SEGMENT
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp CODE_SEGMENT:boot

;GDT
gdt_start:
    dq 0x0
gdt_codeseg:
    dw 0xFFFF
    dw 0x0000
    db 0x0000
    db 10011010b
    db 11001111b
    db 0x0000

gdt_dataseg:
    dw 0xFFFF
    dw 0x0000
    db 0x0000
    db 10010010b
    db 11001111b
    db 0x0000

gdt_end:

gdt_pointer:
    dw gdt_end - gdt_start
    dd gdt_start

disk:

CODE_SEGMENT equ gdt_codeseg - gdt_start
DATA_SEGMENT equ gdt_dataseg - gdt_start

times 510-($-$$) db 0           
dw 0xaa55

;Second stage structure
secondstage:
[bits 32]

boot:
    mov esp,kernel_stack_top
    extern kmain
    call kmain
    cli
    hlt

;Call stack setup
section .bss
align 4
kernel_stack_bottom: equ $
	resb 16384 ; 16 KB
kernel_stack_top: