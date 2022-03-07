; Multiboot header.
MBALIGN  equ  1 << 0         
MEMINFO  equ  1 << 1 
FLAGS    equ  MBALIGN | MEMINFO
MAGIC    equ  0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)
section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

section .bss
align 16

;Top of stack (ESP) set to 4MB

section .text
global init
init:
    mov esp, 0x3D0900
    push eax
    push ebx
    extern kmain
    call kmain
    cli
    hlt