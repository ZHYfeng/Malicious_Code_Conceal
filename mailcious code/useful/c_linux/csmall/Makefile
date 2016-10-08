TARGETS = cspatch csmall
DEPS	= $(TARGETS:=.c) $(TARGETS:=.h) Makefile
CFLAGS	=-Wall -O3 -I. -Werror
XCFLAGS	=-pedantic -ffreestanding -fcall-saved-ecx -nostdlib -nostartfiles	\
	-fomit-frame-pointer -mpreferred-stack-boundary=2 -fcall-saved-edx	\
	-malign-functions=0 -malign-jumps=0 -malign-loops=0 -m386
all:	$(TARGETS)

csmall: cspatch $(DEPS)
	gcc $(CFLAGS) $(XCFLAGS) -Wl,-Tcsmall.ld -o $@ $@.c
	./cspatch || rm -f csmall

cspatch:$(DEPS)
	gcc $(CFLAGS) -s -o $@ $@.c

clean:	;-@rm $(TARGETS)

disasm: csmall ;objdump -mi386 -b binary -D --start-address 0 --adjust-vma 0x08048000 csmall|less
