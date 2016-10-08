# By using this file, you agree to the terms and conditions set
# forth in the COPYING file which can be found at the top level
# of this distribution.
#
VERBOSE	= 0
CC	= gcc
LD	= ld
DEFINES	= -DUSE_RDTSC
INCLUDE	= -I.
CFLAGS	= $(INCLUDE) $(DEFINES) -nostdlib -O2 -Wall			\
	-mpreferred-stack-boundary=2 -malign-functions=0		\
	-malign-jumps=0	-malign-loops=0 -mcpu=i386			\
	-fomit-frame-pointer -fno-keep-inline-functions -ffreestanding
LDFLAGS	=-N -Tvirus.ld
SRC	= virus.c infect.c mcmd.c
OBJ	= $(SRC:.c=.o)

all: virus

ifeq ($(VERBOSE),1)
Q 	=
O 	= >/dev/null
else
Q 	= @
O 	=
endif

virus: $(OBJ)
	@echo "	LD	$(OBJ) -> $@" $(O)
	$(Q)$(LD) $(LDFLAGS) $(OBJ) -o virus
	@echo "	SIZE	`size -A $@|awk '/\.text/{print $$2}'`" $(O)

.c.o:
	@echo "	CC	$<" $(O)
	$(Q)$(CC) $(CFLAGS) -c $<

clean:
	@echo "	CLEAN" $(O)
	-$(Q)rm -f virus *.o

.PHONY: all clean
