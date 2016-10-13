# Makefile for pnscan

DESTDIR=/usr/local

BINDIR=$(DESTDIR)/bin
MANDIR=$(DESTDIR)/man
MAN1DIR=$(MANDIR)/man1

TAR=tar
GZIP=gzip
MAKE=make
INSTALL=./install-sh


## Solaris 8 with Gcc 3.0
GSO_CC=gcc -Wall -g -O -pthreads
GSO_LIBS= -lnsl -lsocket

## Solaris 8 with Forte C 6.2
SOL_CC=cc -mt -O
SOL_LIBS= -lpthread -lnsl -lsocket

## Linux 2.4 with Gcc 2.96
LNX_CC=clang
LNX_LIBS= -c -g -emit-llvm

default:
	@echo 'Use "make SYSTEM" where SYSTEM may be:'
	@echo '   lnx      (Linux with GCC)'
	@echo '   gso      (Solaris with GCC v3)'
	@echo '   sol      (Solaris with Forte C)'
	@exit 1

lnx linux:
	@$(MAKE) all CC="$(LNX_CC)" LIBS="$(LNX_LIBS)"

gso:
	@$(MAKE) all CC="$(GSO_CC)" LIBS="$(GSO_LIBS)"

sol solaris:
	@$(MAKE) all CC="$(SOL_CC)" LIBS="$(SOL_LIBS)"

all: pnscan

man: pnscan.1 ipsort.1

pnscan.1:
	docbook-to-man pnscan.sgml > pnscan.1

ipsort.1:
	docbook-to-man ipsort.sgml > ipsort.1

pnscan: 
	$(CC) $(LIBS) *.c
	llvm-link pnscan.bc bm.bc version.bc -o pnscan


version:
	(PACKNAME=`basename \`pwd\`` ; echo 'char version[] = "'`echo $$PACKNAME | cut -d- -f2`'";' >version.c)

clean distclean:
	-rm -f *.1 *.o *~ pnscan core \#*
	-rm -Rf tmp

dist:	distclean version
	(PACKNAME=`basename \`pwd\`` ; cd .. ; $(TAR) cf - $$PACKNAME | $(GZIP) -9 >$$PACKNAME.tar.gz)


install: all
	$(INSTALL) -m 755 pnscan $(BINDIR)
	$(INSTALL) -m 755 ipsort $(BINDIR)

install-man: man
	$(INSTALL) -m 644 pnscan.1 $(MAN1DIR)
	$(INSTALL) -m 644 ipsort.1 $(MAN1DIR)


install-distribution: install install-man
