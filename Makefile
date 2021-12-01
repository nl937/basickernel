CC = i386-elf-gcc
CFLAGS = -nostdlib -ffreestanding -mno-red-zone -fno-exceptions -nostdlib -Wall -Wextra -Werror
LDFLAGS = -T linker.ld
AS = nasm
ASFLAGS = -f elf32

kernel.bin: boot.o io.o
	$(CC) drv/keyboard.c drv/fb.c io/serial.c kernel/kmain.c boot/boot.o io/io.o -o kernel.bin $(CFLAGS) $(LDFLAGS)

boot.o:
	$(AS) $(ASFLAGS) boot/boot.asm -o boot/boot.o

io.o:
	$(AS) $(ASFLAGS) io/io.s -o io/io.o

clean:
	rm -rf drv/*.o io/*.o boot/*.o kernel/*.o *.o kernel.bin