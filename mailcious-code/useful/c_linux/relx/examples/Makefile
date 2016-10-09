AS	= nasm
all: 1 2 3 4 5 6

%.o:	%.asm
	$(AS) -f elf -O2 $< -o $@
%:	%.o
	$(LD) -s -o $@ $<

clean:
	-@rm -f 1 2 3 4 5 6
