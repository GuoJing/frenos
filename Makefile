build:
	nasm -f aout -o start.o start.asm
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o main.o main.c -m32
	ld -T link.ld -o kernel.bin start.o main.o -m elf_i386
	rm *.o
	cp kernel.bin ../Desktop/Parallels\ Shared\ Folders/Downloads/os/
