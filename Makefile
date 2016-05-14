bin:
# 32 bit so need to -f elf32
	nasm -f elf32 -o start.o src/boot/start.asm
# -m 32
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./src/include -c -o main.o src/main.c -m32
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./src/include -c -o scrn.o src/scrn.c -m32
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./src/include -c -o gdt.o src/gdt.c -m32
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./src/include -c -o idt.o src/idt.c -m32
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./src/include -c -o isrs.o src/isrs.c -m32
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./src/include -c -o irq.o src/irq.c -m32
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./src/include -c -o timer.o src/timer.c -m32
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./src/include -c -o kb.o src/kb.c -m32
# -elf_i386
	ld -T tools/link.ld -o build/kernel.bin start.o main.o scrn.o gdt.o idt.o isrs.o irq.o timer.o kb.o -m elf_i386
	rm *.o
	cp build/kernel.bin ../Desktop/Parallels\ Shared\ Folders/Downloads/os/

clean:
	rm *.o
	rm kernel.bin
	rm kernel.img
