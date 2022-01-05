CC = i386-elf-gcc
CFLAGS = -nostdlib -ffreestanding -mno-red-zone -fno-exceptions -nostdlib -Wall -Wextra -Werror
LDFLAGS = -T linker.ld
AS = nasm
ASFLAGS = -f elf32

kernel.bin: boot.o io.o idt.o interrupts.o gdt.o
	$(CC) drv/keyboard.c drv/fb.c console/console.c io/serial.c kernel/kmain.c kernel/interrupts.c kernel/interrupts.o kernel/gdt.o kernel/gdt.c kernel/idt.o kernel/idt.c boot/boot.o io/io.o -o kernel.bin $(CFLAGS) $(LDFLAGS)
	dd if=/dev/zero of=kernel.img bs=512 count=2880
	dd if=kernel.bin of=kernel.img conv=notrunc

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