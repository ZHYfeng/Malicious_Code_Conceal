TARGET = programme
OBJS = BullMoose_4.o lu.o

CC := gcc
CFLAGS := -O3 -g3 -pthread -D_POSIX_C_SOURCE=200112
LDFLAGS := -lm -static

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -rf *.C *.H *.o $(TARGET)

.c.o:
	$(CC) -c $(CFLAGS) $*.c


BullMoose_4.c: BullMoose_4.h