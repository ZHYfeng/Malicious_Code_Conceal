TARGET = programme
OBJS = BullMoose_4.o jacobcalc.o jacobcalc2.o laplacalc.o linkup.o main.o multi.o slave1.o slave2.o subblock.o

CC := gcc
CFLAGS := -O3 -g3 -pthread -D_POSIX_C_SOURCE=200112
LDFLAGS := -lm -static

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -rf *.C *.H *.o $(TARGET)

.c.o:
	$(CC) -c $(CFLAGS) $*.c

decs.h: decs.h
jacobcalc.c: decs.h
linkup.c: decs.h
slave1.c: decs.h
jacobcalc2.c: decs.h
main.c: decs.h
slave2.c: decs.h
laplacalc.c: decs.h
multi.c: decs.h
subblock.c: decs.h

BullMoose_4.c: BullMoose_4.h