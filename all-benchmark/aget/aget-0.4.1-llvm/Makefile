# EnderUNIX Aget Makefile
# http://www.enderunix.bcrg/aget/

TARGET = AGET
OBJS = main.bc Aget.bc Misc.bc Head.bc Signal.bc Download.bc Resume.bc
CFLAGS = -c -g -emit-llvm -std=c99 -D_GNU_SOURCE
LDFLAGS = -pthread
CC = clang
STRIP = strip

all: $(OBJS)
	llvm-link $(OBJS) -o $(TARGET)

$(OBJS):
	$(CC) $(CFLAGS) *.c

strip: $(all)
	$(STRIP) aget
	
install:
	cp -f aget /usr/local/bin/aget
	cp -f aget.1 /usr/share/man/man1/

clean: 
	rm -f AGET *.bc core.* *~

c:
	rm -f *core* *~ *log
