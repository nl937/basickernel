CC = i686-elf-gcc
CFLAGS = -ffreestanding -Wall -Wextra -nostdlib -m32
LDFLAGS = -T linker.ld
AS = nasm
ASFLAGS = -f elf32

qemu: kernel.bin
	qemu-system-i386 -no-reboot -d cpu-reset -d int -hda core.iso -boot d -vga std -vnc :0

kernel.bin: boot.o idt.o interrupts.o gdt.o
	$(CC) boot/boot.o stdlib/*.c drv/*.c console/*.c io/*.c kernel/*.c kernel/gdt.o kernel/interrupts.o kernel/idt.o -o ./iso/boot/kernel.bin $(CFLAGS) $(LDFLAGS)
	grub-mkrescue iso/ -o core.iso

boot.o:
	$(AS) $(ASFLAGS) boot/boot.s -o boot/boot.o

idt.o:
	$(AS) $(ASFLAGS) kernel/idt.s -o kernel/idt.o

interrupts.o:
	$(AS) $(ASFLAGS) kernel/interrupts.s -o kernel/interrupts.o

gdt.o:
	$(AS) $(ASFLAGS) kernel/gdt.s -o kernel/gdt.o

clean:
	rm -rf drv/*.o io/*.o boot/*.o boot/*.bin kernel/*.o *.o iso/kernel.bin