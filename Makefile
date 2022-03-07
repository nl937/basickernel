CC = i686-elf-gcc
CFLAGS = -nostdlib -ffreestanding -mno-red-zone -fno-exceptions -nostdlib -Wall -Wextra -Werror
LDFLAGS = -T linker.ld
AS = nasm
ASFLAGS = -f elf32

kernel.bin: boot.o io.o idt.o interrupts.o gdt.o
	$(CC) boot/boot.o stdlib/*.c drv/*.c console/*.c io/*.c io/io.o kernel/*.c kernel/gdt.o kernel/interrupts.o kernel/idt.o -o kernel.bin $(CFLAGS) $(LDFLAGS)

boot.o:
	$(AS) $(ASFLAGS) boot/boot.s -o boot/boot.o

io.o:
	$(AS) $(ASFLAGS) io/io.s -o io/io.o

idt.o:
	$(AS) $(ASFLAGS) kernel/idt.s -o kernel/idt.o

interrupts.o:
	$(AS) $(ASFLAGS) kernel/interrupts.s -o kernel/interrupts.o

gdt.o:
	$(AS) $(ASFLAGS) kernel/gdt.s -o kernel/gdt.o

clean:
	rm -rf drv/*.o io/*.o boot/*.o kernel/*.o *.o kernel.bin kernel.img