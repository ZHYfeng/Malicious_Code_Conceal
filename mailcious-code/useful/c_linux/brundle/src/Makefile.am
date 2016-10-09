
#
# Brundle Fly - Good-natured Linux ELF virus supporting kernel 2.2 and 2.4
# Copyright 2001 Konrad Rieck <kr@roqe.org>, Konrad Kretschmer <kk@roqe.org>
# In memory to Seth Brundle 
#
# This is the automake Makefile. That holds most dependencies and rules 
# to compile Brundle Fly. 
#
# $Id: Makefile.am,v 1.12 2001/07/11 18:34:48 kr Exp $
#

bin_PROGRAMS = elfstat finetune elf2bin host inject brundle-fly
finetune_SOURCES = finetune.c
elf2bin_SOURCES = elf2bin.c elfio.c elfio.h brundle-fly.h
elfstat_SOURCES = elfstat.c elfio.c elfio.h
inject_SOURCES = inject.c elfio.c brundle-fly.c elfio.h brundle-fly.h
host_SOURCES = host.c
EXTRA_DIST=brundle-fly-proto.c structs.h syscalls.h cnthosts

VFLAGS=@VFLAGS@ -I. -I.. -O1 -fconserve-space -fno-builtin -fomit-frame-pointer -m386 -S

brundle-fly-plain.s: finetune brundle-fly-proto.c structs.h syscalls.h
	$(CC) $(VFLAGS) brundle-fly-proto.c
	./finetune brundle-fly-proto.s brundle-fly-plain.s

brundle-fly.c: elf2bin brundle-fly-plain.s
	$(AS) brundle-fly-plain.s -o brundle-fly-plain.o
	$(LD) brundle-fly-plain.o -o brundle-fly-linked.o
	./elf2bin brundle-fly-linked.o brundle-fly.c

brundle-fly: inject host
	./inject host brundle-fly
	@echo
	@echo "The living virus can be found in the binary \"brundle-fly\"."
	@echo "handle it with care. Execution permissions have been removed"
	@echo

stats: cnthosts inject brundle-fly
	./cnthosts /usr/bin /bin /usr/local/bin /usr/sbin

clean:
	rm -f *.s *.bin brundle-fly.c *~

distclean:
	rm -f *.s *.bin brundle-fly.c *~

beautify:
	indent -kr *.c *.h
	
