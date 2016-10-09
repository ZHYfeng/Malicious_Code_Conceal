CC	= gcc
CFLAGS	= -mcpu=i386 -ffreestanding -nostdlib -O2 -Wall -Wl,-N,-Tvirus.ld\
	-mpreferred-stack-boundary=2 -malign-functions=0 -malign-jumps=0\
	-malign-loops=0 -fomit-frame-pointer

all: virus

virus:
	$(CC) $(CFLAGS) virus.c -o virus

clean:
	rm -f virus

.PHONY: all clean
