; Multiboot header.
FLAGS    equ  7
MAGIC    equ  0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)
HEADER_ADDR equ 0
LOAD_ADDR equ 0
LOAD_END_ADDR equ 0
BSS_END_ADDR equ 0
ENTRY_ADDR equ 0
MODE_TYPE equ 1
WIDTH    equ 80
HEIGHT   equ 25
DEPTH    equ 0

section .multiboot
align 4
dd MAGIC
dd FLAGS
dd CHECKSUM
dd HEADER_ADDR
dd LOAD_ADDR
dd LOAD_END_ADDR
dd BSS_END_ADDR
dd ENTRY_ADDR
dd MODE_TYPE
dd WIDTH
dd HEIGHT
dd DEPTH

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