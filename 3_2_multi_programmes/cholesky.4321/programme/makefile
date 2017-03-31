TARGET = programme
OBJS = BullMoose_4.o amal.o assign.o bfac.o bksolve.o block2.o fo.o malloc.o \
       mf.o numLL.o parts.o seg.o solve.o tree.o util.o

CC := gcc
CFLAGS := -O3 -g3 -pthread -D_POSIX_C_SOURCE=200112
LDFLAGS := -lm -static

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -rf *.C *.H *.o $(TARGET)

.c.o:
	$(CC) -c $(CFLAGS) $*.c


matrix.h: matrix.h
amal.c: matrix.h
block2.c: matrix.h
numLL.c: matrix.h
tree.c: matrix.h
assign.c: matrix.h
fo.c: matrix.h
parts.c: matrix.h
util.c: matrix.h
bfac.c: matrix.h
malloc.c: matrix.h
seg.c: matrix.h
bksolve.c: matrix.h
mf.c: matrix.h
solve.c: matrix.h

BullMoose_4.c: BullMoose_4.h