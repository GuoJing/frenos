build:
# 32 bit so need to -f elf32
	nasm -f elf32 -o start.o start.asm
# -m 32
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o main.o main.c -m32
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o scrn.o scrn.c -m32
# -elf_i386
	ld -T link.ld -o kernel.bin start.o main.o scrn.o -m elf_i386
	rm *.o
	dd if=/dev/zero of=kernel.img bs=1M count=64
	dd status=noxfer conv=notrunc if=kernel.bin of=kernel.img
	cp kernel.bin ../Desktop/Parallels\ Shared\ Folders/Downloads/os/
	cp kernel.img ../Desktop/Parallels\ Shared\ Folders/Downloads/os/
