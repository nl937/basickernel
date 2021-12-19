global idt_final

idt_final:
    mov eax, [esp+4]
    lidt [eax]
    ret