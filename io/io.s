global io_portwrite
global io_portread
; stack: [esp + 8] the data byte
;        [esp + 4] the I/O port
;        [esp    ] return address
io_portwrite:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al
    ret

io_portread:
    mov dx, [esp + 4]
    in al, dx
    ret