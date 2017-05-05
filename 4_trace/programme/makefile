TARGET = programme
OBJS = programme.o

CC := gcc
CFLAGS := 
LDFLAGS := -lm -static

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -rf *.o $(TARGET)

.c.o:
	$(CC) -c $(CFLAGS) $*.c