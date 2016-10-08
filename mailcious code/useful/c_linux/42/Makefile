DEFINES=
#-DDEBUG
CFLAGS = -Os -ggdb -Wall -fno-builtin -nostdlib -fomit-frame-pointer

all: test

42: layer1.c layer2.c set_mark
	gcc $(CFLAGS) $(DEFINES) -c layer1.c -o layer1.o
	gcc $(CFLAGS) $(DEFINES) -c layer2.c -o layer2.o
	gcc $(LDFLAGS) layer1.o layer2.o -o 42
	./set_mark 42

set_mark: set_mark.c
	$(CC) $< -o $@

test: 42
	cp /bin/ls .
	-./42
	./ls
	cp /bin/ps .
	./ls
	./ps

clean:
	-@rm -f 42 ls ps set_mark *.o

.PHONY: all clean
