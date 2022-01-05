global gdt_final

gdt_final:
    mov eax, [esp+4]
    lgdt [eax]
    ret