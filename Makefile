FONTES := main.c scrn.c gdt.c idt.c isrs.c irq.c timer.c kb.c

build: 
	for i in $(FONTES);do \
		gcc -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I ./include -c $$i; \
	done
	@nasm -f elf -o start.o start.asm
	@ld -T link.ld -o kernel.bin gdt.o start.o main.o scrn.o idt.o isrs.o irq.o timer.o kb.o
	@mkdir -p /tmp/so
	@sudo mount -o loop ../floppy.img /tmp/so
	@sudo cp kernel.bin /tmp/so
	@sudo umount /tmp/so
	@qemu -fda ../floppy.img -boot a
	@rm -f *.o

clean:
	@rm -f *.o kernel.bin *.*~

