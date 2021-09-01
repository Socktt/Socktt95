all:
	nasm -f bin boot.asm -o boot.bin
	nasm -f bin empty_end.asm -o empty_end.bin
	nasm -f elf kernel_entry.asm -o kernel_entry.o
	nasm -f elf isr.asm -o isr.o
	i386-elf-gcc -ffreestanding -m32 -g -c "kernel.c" -o "kernel.o"
	i386-elf-gcc -ffreestanding -m32 -g -c "idt.c" -o "idt.o"
	i386-elf-gcc -ffreestanding -m32 -g -c "isr.c" -o "isrc.o"
	i386-elf-gcc -ffreestanding -m32 -g -c "system.c" -o "system.o"
	i386-elf-ld -o "full_kernel.bin" -Ttext 0x1000 "kernel_entry.o" "kernel.o" "idt.o" "isr.o" "isrc.o" "system.o" --oformat binary
	cat "boot.bin" "full_kernel.bin" "empty_end.bin" > "Socktt95.bin"
	qemu-system-x86_64 Socktt95.bin