global io_portwrite_b
global io_portread_b
global io_portwrite_w
global io_portread_w
; stack: [esp + 8] the data byte
;        [esp + 4] the I/O port
;        [esp    ] return address
io_portwrite_b:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al
    ret

io_portread_b:
    mov dx, [esp + 4]
    in al, dx
    ret

io_portwrite_w:
    mov ax, [esp + 8]
    mov dx, [esp + 4]
    out dx, ax
    ret

io_portread_w:
    mov dx, [esp + 4]
    in ax, dx
    ret